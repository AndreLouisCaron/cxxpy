// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "List.hpp"
#include "None.hpp"
#include "Error.hpp"

namespace {

    ::PyObject * allocate ( ::Py_ssize_t size )
    {
        ::PyObject *const object = ::PyList_New(size);
        if ( object == 0 )
        {
        }
        return (object);
    }

    void place ( ::PyObject * list, ::Py_ssize_t index, ::PyObject * value )
    {
        PyList_SET_ITEM(list, index, py::Object::acquire(value));
    }

    void store ( ::PyObject * list, ::Py_ssize_t index, ::PyObject * value )
    {
        const int result =
            ::PyList_SetItem(list, index, py::Object::acquire(value));
        if ( result == -1 )
        {
            py::Error::translate();
        }
    }

    ::PyObject * fetch ( ::PyObject * list, ::Py_ssize_t index )
    {
        ::PyObject *const value = ::PyList_GetItem(list, index);
        if ( value == 0 )
        {
        }
        return (py::Object::acquire(value));
    }

}

namespace py {

    bool List::isa ( const Object& object, bool exact )
    {
        return (exact? PyList_CheckExact(object.handle())
                     : PyList_Check     (object.handle()));
    }

    List::List ()
        : Object(::allocate(0))
    {
    }

    List::List ( const Object& object )
        : Object(object.handle())
    {
    }

    List::List ( Handle handle )
        : Object(handle)
    {
    }

    List::List ( size_type size )
        : Object(::allocate(size))
    {
        for ( size_type i = 0; (i < size); ++i ) {
            ::place(handle(), i, py::None().handle());
        }
    }

    List::size_type List::size () const
    {
        return (::PyList_Size(handle()));
    }

    Object List::operator[] ( size_type i ) const
    {
        return (Object(::fetch(handle(), i)));
    }

    List::Proxy List::operator[] ( size_type i )
    {
        return (Proxy(*this, i));
    }

    List::Proxy::Proxy ( List& tuple, size_type index )
        : myList(&tuple), myIndex(index)
    {
    }

    List::Proxy& List::Proxy::operator= ( const Object& object )
    {
        ::store(myList->handle(), myIndex, object.handle());
        return (*this);
    }

    List::Proxy::operator py::Object () const
    {
        return (Object(::fetch(myList->handle(), myIndex)));
    }

}
