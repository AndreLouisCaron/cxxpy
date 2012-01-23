// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Tuple.hpp"
#include "None.hpp"
#include "Error.hpp"
#include <iostream>

namespace {

    ::PyObject * allocate ( ::Py_ssize_t size )
    {
        ::PyObject *const object = ::PyTuple_New(size);
        if ( object == 0 )
        {
        }
        return (object);
    }

    void place ( ::PyObject * tuple, ::Py_ssize_t index, ::PyObject * value )
    {
        PyTuple_SET_ITEM(tuple, index, py::Object::acquire(value));
    }

    void store ( ::PyObject * tuple, ::Py_ssize_t index, ::PyObject * value )
    {
        const int result =
            ::PyTuple_SetItem(tuple, index, py::Object::acquire(value));
        if ( result == -1 )
        {
            py::Error::translate();
        }
    }

    ::PyObject * fetch ( ::PyObject * tuple, ::Py_ssize_t index )
    {
        ::PyObject *const value = ::PyTuple_GetItem(tuple, index);
        if ( value == 0 )
        {
        }
        return (py::Object::acquire(value));
    }

}

namespace py {

    bool Tuple::isa ( const Object& object, bool exact )
    {
        return (exact? PyTuple_CheckExact(object.handle())
                     : PyTuple_Check     (object.handle()));
    }

    Tuple::Tuple ( const Object& object )
        : Object(object.handle())
    {
    }

    Tuple::Tuple ( Handle handle )
        : Object(handle)
    {
    }

    Tuple::Tuple ( size_type size )
        : Object(::allocate(size), Object::steal())
    {
        for ( size_type i = 0; (i < size); ++i ) {
            ::place(handle(), i, py::None().handle());
        }
    }

    Tuple::size_type Tuple::size () const
    {
        return (::PyTuple_Size(handle()));
    }

    Object Tuple::operator[] ( size_type i ) const
    {
        return (Object(::fetch(handle(), i)));
    }

    Tuple::Proxy Tuple::operator[] ( size_type i )
    {
        return (Proxy(*this, i));
    }

    Tuple::Proxy::Proxy ( Tuple& tuple, size_type index )
        : myTuple(&tuple), myIndex(index)
    {
    }

    Tuple::Proxy& Tuple::Proxy::operator= ( const Object& object )
    {
        ::store(myTuple->handle(), myIndex, object.handle());
        return (*this);
    }

    Tuple::Proxy::operator py::Object () const
    {
        return (Object(::fetch(myTuple->handle(), myIndex)));
    }

}
