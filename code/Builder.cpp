// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file pyxx/Builder.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Simple class builder.
 */

#include "Builder.hpp"
#include "Error.hpp"
#include <cstring>

namespace {

    ::PyObject * getclasssymbols ( ::PyObject * klass )
    {
        return (((::PyClassObject*)klass)->cl_dict);
    }

    ::PyMethodDef NO_MODULE_METHODS[] = { {0} };

    struct BASIC_OBJECT
    {
        // fields required by runtime.
        PyObject_HEAD;

        // application data, pointer to real object.
        void * baton;
    };

    ::PyMethodDef * rawmethods ( const std::vector<py::Method>& methods )
    {
        ::PyMethodDef *const results = new ::PyMethodDef[methods.size()+1];
        for ( std::size_t i = 0; (i < methods.size()); ++i ) {
            results[i] = methods[i].data();
        }
        std::memset(results+methods.size(), 0, sizeof(::PyMethodDef));
        return (results);
    }

}

namespace py {

    ModuleBuilder::ModuleBuilder ( const Bytes& name )
        : Module(acquire(::Py_InitModule(name.data(), NO_MODULE_METHODS)))
    {
    }

    Method::Method ( const Bytes& name, NoArgsCall call )
        : myName(name)
    {
        std::memset(&myData, 0, sizeof(myData));
        myData.ml_name = myName.data();
        myData.ml_meth = reinterpret_cast<VarArgCall>(call);
        myData.ml_flags = METH_NOARGS;
    }

    Method::Method ( const Bytes& name, VarArgCall call )
        : myName(name)
    {
        std::memset(&myData, 0, sizeof(myData));
        myData.ml_name = myName.data();
        myData.ml_meth = reinterpret_cast<VarArgCall>(call);
        myData.ml_flags = METH_VARARGS;
    }

    Method::Method ( const Bytes& name, KwdArgCall call )
        : myName(name)
    {
        std::memset(&myData, 0, sizeof(myData));
        myData.ml_name = myName.data();
        myData.ml_meth = reinterpret_cast<VarArgCall>(call);
        myData.ml_flags = METH_KEYWORDS;
    }

    Method::Method ( const Method& method )
        : myName(method.myName)
    {
        std::memset(&myData, 0, sizeof(myData));
        myData.ml_name = myName.data();
        myData.ml_meth = method.myData.ml_meth;
        myData.ml_flags = method.myData.ml_flags;
    }

    ::PyMethodDef& Method::data ()
    {
        return (myData);
    }

    const ::PyMethodDef& Method::data () const
    {
        return (myData);
    }

    void Method::name ( const Bytes& name )
    {
        myName = name, myData.ml_name = myName.data();
    }

    const Bytes& Method::name () const
    {
        return (myName);
    }

    ClassBuilder::ClassBuilder ( const Bytes& name, const Map& symbols )
        : Object(acquire(::PyClass_New(0, symbols.handle(), name.handle())))
    {
    }

    Map ClassBuilder::symbols () const
    {
        return (Map(acquire(::getclasssymbols(handle()))));
    }

    void ClassBuilder::add ( Method definition )
    {
          // Create code object for function.
        const Object function(Object::acquire(
            ::PyCFunction_New(&definition.data(), 0)));
          // Create a class method with the function.
        const Object method(Object::acquire(
            ::PyMethod_New(function.handle(), 0, handle())));
          // Register method in class dictionary.
        symbols().put(definition.name(), method);
    }

    Object ClassBuilder::operator() () const
    {
        ::PyObject *const result = ::PyInstance_New(handle(), 0, 0);
        if ( result == 0 ) {
            Error::translate();
        }
        return (Object(acquire(result)));
    }

    Object ClassBuilder::operator() ( const Tuple& args ) const
    {
        ::PyObject *const result = ::PyInstance_New(handle(), args.handle(), 0);
        if ( result == 0 ) {
            Error::translate();
        }
        return (Object(acquire(result)));
    }

    Object ClassBuilder::operator() ( const Tuple& args, const Map& kwds ) const
    {
        ::PyObject *const result =
            ::PyInstance_New(handle(), args.handle(), kwds.handle());
        if ( result == 0 ) {
            Error::translate();
        }
        return (Object(acquire(result)));
    }

    TypeBuilder::TypeBuilder ( const Bytes& name )
        : myName(name)
    {
          // need to use C-style initialization for weird macro.
        ::PyTypeObject data = {
            PyObject_HEAD_INIT(0) 0
        };
          // set required fields.
        data.tp_name = myName.data();
        data.tp_basicsize = sizeof(::BASIC_OBJECT);
        data.tp_flags = Py_TPFLAGS_DEFAULT;
        data.tp_new = &::PyType_GenericNew;
          // copy initialized structure to member.
        std::memcpy(&myData, &data, sizeof(data));
    }

    TypeBuilder::~TypeBuilder ()
    {
        if ( myData.tp_methods ) {
            delete [] myData.tp_methods; myData.tp_methods = 0;
        }
    }

    void TypeBuilder::init ( TypeBuilder::Ctor ctor )
    {
        myData.tp_init = ctor;
    }

    void TypeBuilder::add ( const Method& method )
    {
        myMethods.push_back(method);
    }

    void TypeBuilder::finish ()
    {
          // Compile methods.
        if ( !myMethods.empty() ) {
            myData.tp_methods = ::rawmethods(myMethods);
        }
        
          // Register type.
        const int result = ::PyType_Ready(const_cast<::PyTypeObject*>(&myData));
        if ( result == -1 ) {
            Error::translate();
        }
    }

    Object TypeBuilder::operator() ()
    {
          // Allocate.
        ::PyObject *const result = ::_PyObject_New(&myData);
        if ( result == 0 ) {
            Error::translate();
        }
        Object object(result);
        
          // Initialize.
        if ( myData.tp_init )
        {
            if ( myData.tp_init(object.handle(), 0, 0) != 0 )
            {
            }
        }
        
          // Finish.
        return (object);
    }

}
