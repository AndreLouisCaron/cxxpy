// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Tuple.hpp"
#include "None.hpp"
#include "Error.hpp"

namespace {

    py::Handle allocate ( ::Py_ssize_t size )
    {
        ::PyObject *const object = ::PyTuple_New(size);
        if ( object == 0 )
        {
        }
        return (py::steal(object));
    }

    void place ( ::PyObject * tuple, ::Py_ssize_t index, ::PyObject * value )
    {
        Py_INCREF(value);
        PyTuple_SET_ITEM(tuple, index, value);
    }

    void store ( ::PyObject * tuple, ::Py_ssize_t index, ::PyObject * value )
    {
        Py_INCREF(value);
        const int result = ::PyTuple_SetItem(tuple, index, value);
        if ( result == -1 )
        {
            py::Error::translate();
        }
    }

    py::Handle fetch ( ::PyObject * tuple, ::Py_ssize_t index )
    {
        ::PyObject *const value = ::PyTuple_GetItem(tuple, index);
        if ( value == 0 )
        {
        }
        return (py::steal(value));
    }

}

namespace py {

    bool Tuple::is_a (const Handle& handle, bool exact)
    {
        return (exact? PyTuple_CheckExact(handle)
                     : PyTuple_Check     (handle));
    }

    Tuple::Tuple (const Handle& handle)
        : myHandle(check<Tuple>(handle))
    {
    }

    Tuple::Tuple (const Any& any)
        : myHandle(check<Tuple>(any.handle()))
    {
    }

    Tuple::Tuple ( size_type size )
        : myHandle(::allocate(size))
    {
        for ( size_type i = 0; (i < size); ++i ) {
            ::place(handle(), i, Py_None);
        }
    }

    const Handle& Tuple::handle () const
    {
        return (myHandle);
    }

    void Tuple::swap (Tuple& other)
    {
        myHandle.swap(other.myHandle);
    }

    Tuple::size_type Tuple::size () const
    {
        return (::PyTuple_Size(handle()));
    }

    Tuple::operator Any () const
    {
        return (Any(myHandle));
    }

    Any Tuple::operator[] ( size_type i ) const
    {
        return (Any(::fetch(handle(), i)));
    }

    Tuple::Proxy Tuple::operator[] ( size_type i )
    {
        return (Proxy(*this, i));
    }

    Tuple::Proxy::Proxy ( Tuple& tuple, size_type index )
        : myTuple(&tuple), myIndex(index)
    {
    }

    Tuple::Proxy& Tuple::Proxy::operator= (const Any& object)
    {
        ::store(myTuple->handle(), myIndex, object.handle());
        return (*this);
    }

    Tuple::Proxy::operator Any () const
    {
        return (Any(::fetch(myTuple->handle(), myIndex)));
    }

}
