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

namespace {

    ::PyObject * getiterator ( ::PyObject * iterable )
    {
        ::PyObject *const result = ::PyObject_GetIter(iterable);
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (result);
    }

}

namespace py {

    bool Iterator::isa ( const Handle& handle )
    {
        return (PyIter_Check(handle) != 0);
    }

    bool Iterator::isa ( const Object& object )
    {
        return (PyIter_Check(object.handle()) != 0);
    }

    Iterator::Iterator ()
    {
    }

    Iterator::Iterator ( const Handle& handle )
        : Object(handle)
    {
    }

    Iterator::Iterator ( const Any& iterator )
        : Object(iterator.cast<Iterator>())
    {
    }

    Iterator::Iterator ( const List& list )
        : Object(acquire(::getiterator(list.handle())))
    {
    }

    Iterator::Iterator ( const Tuple& iterable )
        : Object(acquire(::getiterator(iterable.handle())))
    {
    }

    bool Iterator::next ()
    {
        ::PyObject *const result = ::PyIter_Next(handle());
        if ( result == 0 )
        {
            // Means "end of sequence".  Could it also be an error?
        }
        return (myItem = Any(acquire(result)));
    }

    Any Iterator::item () const
    {
        return (myItem);
    }

}
