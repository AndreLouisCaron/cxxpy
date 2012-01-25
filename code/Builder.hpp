#ifndef _py_Builder_hpp__
#define _py_Builder_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file pyxx/Builder.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Simple class builder.
 */

#include "Bytes.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "Module.hpp"
#include "Tuple.hpp"
#include <python.h>
#include <vector>

namespace py {

    class ModuleBuilder :
        public Module
    {
        /* construction. */
    public:
        ModuleBuilder ( const Bytes& name );
     };

    class Method
    {
        /* nested types. */
    public:
        typedef ::PyObject*(*NoArgsCall)(::PyObject*);
        typedef ::PyObject*(*VarArgCall)(::PyObject*,::PyObject*);
        typedef ::PyObject*(*KwdArgCall)(::PyObject*,::PyObject*,::PyObject*);

        /* data. */
    private:
        Bytes myName;
        ::PyMethodDef myData;

        /* construction. */
    public:
        Method ( const Bytes& name, NoArgsCall call );
        Method ( const Bytes& name, VarArgCall call );
        Method ( const Bytes& name, KwdArgCall call );

        Method ( const Method& method );

        /* methods. */
    public:
        ::PyMethodDef& data ();
        const ::PyMethodDef& data () const;
        void name ( const Bytes& name );
        const Bytes& name () const;
    };

    class ClassBuilder :
        public Object
    {
        /* construction. */
    public:
        ClassBuilder ( const Bytes& name, const Map& symbols );

        /* methods. */
    public:
        Map symbols () const;

        void add ( Method definition );

        /* operators. */
    public:
        Object operator() () const;
        Object operator() ( const Tuple& args ) const;
        Object operator() ( const Tuple& args, const Map& kwds ) const;
    };

    /*!
     * @see http://docs.python.org/c-api/typeobj.html
     */
    class TypeBuilder
    {
        /* nested types. */
    public:
        typedef int(*Ctor)(::PyObject*,::PyObject*,::PyObject*);

        /* class methods. */
    public:
        static void * get_baton ( Object object );
        static void set_baton ( Object object, void * baton );

        /* data. */
    private:
        ::PyTypeObject myData;
        const Bytes myName;
        std::vector<Method> myMethods;

        /* construction. */
    public:
        TypeBuilder ( const Bytes& name );
        ~TypeBuilder ();

        /* methods. */
    public:
        void init ( Ctor ctor );
        void iterable( Method::NoArgsCall iter, Method::NoArgsCall next );
        void add ( const Method& method );
        void finish ();

        /* operators. */
    public:
        Object operator() ();
    };

      /*!
       * @brief
       */
    template<Object(*Function)(Object)>
    class noargs
    {
        static ::PyObject * backend ( ::PyObject * self )
        {
            return (Function(
                Object(Object::acquire(self))).release());
        }
    public:
        operator Method::VarArgCall () const
        {
            return (&noargs<Function>::backend);
        }
    };

      /*!
       * @brief
       */
    template<Object(*Function)(Object,Tuple)>
    class vararg
    {
        static ::PyObject * backend ( ::PyObject * self, ::PyObject * args )
        {
            return (Function(
                Object(Object::acquire(self)),
                Tuple (Object::acquire(args))).release());
        }
    public:
        operator Method::VarArgCall () const
        {
            return (&vararg<Function>::backend);
        }
    };

      /*!
       * @brief
       */
    template<Object(*Function)(Object,Tuple,Map)>
    class kwdarg
    {
        static ::PyObject * backend
            ( ::PyObject * self, ::PyObject * args, ::PyObject * kwds )
        {
            return (Function(
                Object(Object::acquire(self)),
                Tuple (Object::acquire(args)),
                Map   (Object::acquire(kwds))).release());
        }
    public:
        operator Method::VarArgCall () const
        {
            return (&vararg<Function>::backend);
        }
    };

      /*!
       * @brief
       */
    template<int(*Function)(Object,Tuple,Map)>
    class ctor
    {
        static int backend
            ( ::PyObject * self, ::PyObject * args, ::PyObject * kwds )
        {
            return (Function(
                Object(Object::acquire(self)),
                Tuple (Object::acquire(args)),
                Map   (Object::acquire(kwds))));
        }
    public:
        operator TypeBuilder::Ctor () const
        {
            return (&ctor<Function>::backend);
        }
    };


}

#endif /* _py_Builder_hpp__ */
