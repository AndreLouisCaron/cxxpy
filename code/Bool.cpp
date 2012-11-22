// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Bool.hpp"

namespace {

    py::Handle allocate ( bool value )
    {
        ::PyObject *const object = ::PyBool_FromLong(value?1:0);
        if ( object == 0 )
        {
        }
        return (py::steal(object));
    }

}

namespace py {

    bool Bool::is_a (const Handle& handle)
    {
        return (PyBool_Check(handle.data()));
    }

    Bool::Bool (const Handle& handle)
        : myHandle(check<Bool>(handle))
    {
    }

    Bool::Bool (const Any& any)
        : myHandle(check<Bool>(any.handle()))
    {
    }

    Bool::Bool (bool value)
        : myHandle(::allocate(value))
    {
    }

    const Handle& Bool::handle () const
    {
        return (myHandle);
    }

    void Bool::swap(Bool& other)
    {
        myHandle.swap(other.myHandle);
    }

    Bool::operator Any () const
    {
        return (Any(myHandle));
    }

    Bool True ()
    {
        return (Bool(share(Py_True)));
    }

    Bool False ()
    {
        return (Bool(share(Py_False)));
    }

}
