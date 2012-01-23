// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Object.hpp"
#include "Type.hpp"
#include "Map.hpp"

#include <algorithm>

namespace {

    ::PyObject * noop ( ::PyObject * object ) { return (object); }

}

namespace py {

    Object::Handle Object::acquire ( Handle object )
    {
        Py_XINCREF(object);
        return (object);
    }

    Object::Handle Object::release ( Handle object )
    {
        Py_XDECREF(object);
        return (0);
    }

    Object::Transfer Object::steal ()
    {
        return (&::noop);
    }

    Object::Transfer Object::share ()
    {
        return (&Object::acquire);
    }

    Object::Object ()
        : myHandle(0)
    {
    }

    Object::Object ( Handle handle, Transfer transfer )
        : myHandle(transfer(handle))
    {
    }

    Object::Object ( const Object& other )
        : myHandle(acquire(other.handle()))
    {
    }

    Object::~Object ()
    {
        myHandle = release(myHandle);
    }

    Object::Handle Object::handle () const
    {
        return (myHandle);
    }

    const Type Object::type () const
    {
        ::PyObject *const result = ::PyObject_Type(handle());
        if ( result == 0 )
        {
        }
        return (Type(result, Object::steal()));
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
        return (Map(result, Object::steal()));
    }

    void Object::swap ( Object& rhs )
    {
        std::swap(myHandle, rhs.myHandle);
    }

    Object::Handle Object::release ()
    {
        Handle handle = myHandle;
        myHandle = 0;
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
