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

    py::Handle allocate ( ::Py_ssize_t size )
    {
        ::PyObject *const object = ::PyList_New(size);
        if ( object == 0 )
        {
        }
        return (py::steal(object));
    }

    void place ( ::PyObject * list, ::Py_ssize_t index, ::PyObject * value )
    {
        Py_INCREF(value);
        PyList_SET_ITEM(list, index, value);
    }

    void store ( ::PyObject * list, ::Py_ssize_t index, ::PyObject * value )
    {
        Py_INCREF(value);
        const int result =
            ::PyList_SetItem(list, index, value);
        if ( result == -1 )
        {
            py::Error::translate();
        }
    }

    py::Handle fetch ( ::PyObject * list, ::Py_ssize_t index )
    {
        ::PyObject *const value = ::PyList_GetItem(list, index);
        if ( value == 0 )
        {
        }
        return (py::share(value));
    }

}

namespace py {

    bool List::is_a (const Handle& handle, bool exact)
    {
        return (exact? PyList_CheckExact(handle)
                     : PyList_Check     (handle));
    }

    List::List (const Handle& handle)
        : myHandle(check<List>(handle))
    {
    }

    List::List (const Any& any)
        : myHandle(check<List>(any.handle()))
    {
    }

    List::List ()
        : myHandle(::allocate(0))
    {
    }

    List::List ( size_type size )
        : myHandle(::allocate(size))
    {
        for ( size_type i = 0; (i < size); ++i ) {
            ::place(handle(), i, py::None().handle());
        }
    }

    const Handle& List::handle () const
    {
        return (myHandle);
    }

    void List::swap (List& other)
    {
        myHandle.swap(other.myHandle);
    }

    List::size_type List::size () const
    {
        return (::PyList_Size(handle()));
    }

    void List::append ( const Any& item )
    {
        const int result = ::PyList_Append(handle(), item.handle());
        if (result < 0) {
            Error::translate();
        }
    }

    List::operator Any () const
    {
        return (Any(myHandle));
    }

    Any List::operator[] ( size_type i ) const
    {
        return (Any(::fetch(handle(), i)));
    }

    List::Proxy List::operator[] ( size_type i )
    {
        return (Proxy(*this, i));
    }

    List::Proxy::Proxy ( List& tuple, size_type index )
        : myList(&tuple), myIndex(index)
    {
    }

    List::Proxy& List::Proxy::operator= ( const Any& object )
    {
        ::store(myList->handle(), myIndex, object.handle());
        return (*this);
    }

    List::Proxy::operator py::Any () const
    {
        return (Any(::fetch(myList->handle(), myIndex)));
    }

}
