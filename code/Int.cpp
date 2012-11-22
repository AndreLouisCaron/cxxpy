// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Int.hpp"

namespace {

    py::Handle allocate (long value)
    {
        ::PyObject *const object = ::PyInt_FromLong(value);
        if (object == 0)
        {
        }
        return (py::steal(object));
    }

}

namespace py {

    bool Int::is_a (const Handle& handle, bool exact)
    {
        return (exact? PyInt_CheckExact(handle.data())
                     : PyInt_Check     (handle.data()));
    }

    Int::Int (const Handle& handle)
        : myHandle(check<Int>(handle))
    {
    }

    Int::Int (const Any& any)
        : myHandle(check<Int>(any.handle()))
    {
    }

    Int::Int (int value)
        : myHandle(::allocate(static_cast<long>(value)))
    {
    }

    Int::Int (long value)
        : myHandle(::allocate(value))
    {
    }

    const Handle& Int::handle () const
    {
        return (myHandle);
    }

    void Int::swap (Int& other)
    {
        myHandle.swap(other.myHandle);
    }

    Int::operator Any () const
    {
        return (Any(myHandle));
    }

    Int::operator long () const
    {
        return PyInt_AS_LONG(handle().data());
    }

}
