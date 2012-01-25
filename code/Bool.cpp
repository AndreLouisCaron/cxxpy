// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Bool.hpp"

namespace {

    ::PyObject * allocate ( bool value )
    {
        ::PyObject *const object = ::PyBool_FromLong(value?1:0);
        if ( object == 0 )
        {
        }
        return (object);
    }

}

namespace py {

    bool Bool::isa ( Handle handle )
    {
        return (PyBool_Check(handle));
    }

    bool Bool::isa ( const Object& object )
    {
        return (isa(object.handle()));
    }

    Bool::Bool ( bool value )
        : Object(::allocate(value), Object::steal())
    {
    }

    Bool::Bool ( Handle handle )
        : Object(check<Bool>(handle), Object::share())
    {
    }

    Bool::Bool ( const Object& object )
        : Object(check<Bool>(object.handle()), Object::share())
    {
    }

    Bool True ()
    {
        return (Bool(Py_True));
    }

    Bool False ()
    {
        return (Bool(Py_False));
    }

}
