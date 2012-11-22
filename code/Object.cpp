// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Object.hpp"
#include "Type.hpp"
#include "Map.hpp"

namespace py {

    Object::Object ()
        : myHandle()
    {
    }

    Object::Object (const Handle& handle)
        : myHandle(handle)
    {
    }

    Object::Object (const Object& other)
        : myHandle(other.handle())
    {
    }

    Object::~Object ()
    {
    }

    const Handle& Object::handle () const
    {
        return (myHandle);
    }

    const Type Object::type () const
    {
        ::PyObject *const result = ::PyObject_Type(handle());
        if ( result == 0 )
        {
        }
        return (Type(steal(result)));
    }

    const size_t Object::size () const
    {
        const size_t result = ::PyObject_Length(handle());
        if ( result == -1 )
        {
        }
        return (result);
    }

    const Map Object::dir () const
    {
        ::PyObject *const result = ::PyObject_Dir(handle());
        if ( result == 0 )
        {
        }
        return (Map(steal(result)));
    }

    void Object::swap (Object& rhs)
    {
        std::swap(myHandle, rhs.myHandle);
    }

    Handle Object::release ()
    {
        const Handle handle = myHandle;
        myHandle.free();
        return (handle);
    }

    Object::operator bool () const
    {
        const int result = ::PyObject_IsTrue(handle());
        if ( result == -1 )
        {
        }
        return (result != 0);
    }

    bool Object::operator! () const
    {
        const int result = ::PyObject_Not(handle());
        if ( result == -1 )
        {
        }
        return (result != 0);
    }

}
