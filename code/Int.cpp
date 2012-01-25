// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Int.hpp"

namespace {

    ::PyObject * allocate ( long value )
    {
        ::PyObject *const object = ::PyInt_FromLong(value);
        if ( object == 0 )
        {
        }
        return (object);
    }

}

namespace py {

    bool Int::isa ( Handle handle, bool exact )
    {
        return (exact? PyInt_CheckExact(handle)
                     : PyInt_Check     (handle));
    }

    bool Int::isa ( const Object& object, bool exact )
    {
        return (exact? PyInt_CheckExact(object.handle())
                     : PyInt_Check     (object.handle()));
    }

    Int::Int ( int value )
        : Object(::allocate(static_cast<long>(value)))
    {
    }

    Int::Int ( long value )
        : Object(::allocate(value))
    {
    }

    Int::Int ( Handle handle )
        : Object(check<Int>(handle), Object::share())
    {
    }

    Int::Int ( const Object& object )
        : Object(check<Int>(object.handle()))
    {
    }

    Int::operator long () const
    {
        return PyInt_AS_LONG(handle());
    }

}
