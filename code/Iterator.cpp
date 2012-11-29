// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file pyxx/Iterator.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Iterator interface.
 */

#include "Iterator.hpp"
#include "Error.hpp"
#include "List.hpp"
#include "None.hpp"

namespace {

    py::Handle getiterator ( ::PyObject * iterable )
    {
        ::PyObject *const result = ::PyObject_GetIter(iterable);
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (py::share(result));
    }

}

namespace py {

    bool Iterator::is_a ( const Handle& handle )
    {
        return (PyIter_Check(handle.data()) != 0);
    }

    Iterator::Iterator ()
    {
    }

    Iterator::Iterator ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Iterator::Iterator ( const Any& object )
        : myHandle(check<Iterator>(object.handle()))
    {
    }

    Iterator::Iterator ( const List& list )
        : myHandle(::getiterator(list.handle()))
    {
    }

    Iterator::Iterator ( const Tuple& iterable )
        : myHandle(::getiterator(iterable.handle()))
    {
    }

    const Handle& Iterator::handle () const
    {
        return (myHandle);
    }

    void Iterator::swap(Iterator& other)
    {
        myHandle.swap(other.myHandle);
    }

    bool Iterator::next ()
    {
        ::PyObject *const result = ::PyIter_Next(myHandle);
        if ( result == 0 ) {
            // Means "end of sequence".  Could it also be an error?
            return false;
        }
        myItem = Any(share(result));
        return (myItem.handle() != None());
    }

    Any Iterator::item () const
    {
        return (myItem);
    }

    Iterator::operator Any () const
    {
        return (Any(myHandle));
    }

}
