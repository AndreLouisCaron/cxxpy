// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file pyxx/Any.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Variant type, can contain "any" python object.
 */

#include "Any.hpp"

namespace py {

    Any::Any ( const Handle& handle )
        : Object(handle)
    {
    }

    Any::Any ()
        : Object()
    {
    }

    Any::Any ( const Object& object )
        : Object(object)
    {
    }

    Any& Any::operator= ( const Any& object )
    {
        myHandle = object.handle();
        return (*this);
    }

    bool operator== (const Any& lhs, const Any& rhs)
    {
        return (lhs.handle() == rhs.handle());
    }

    bool operator== (const Any& lhs, const Handle& rhs)
    {
        return (lhs.handle() == rhs);
    }

    bool operator== (const Handle& lhs, const Any& rhs)
    {
        return (lhs == rhs.handle());
    }

    bool operator!= (const Any& lhs, const Any& rhs)
    {
        return (lhs.handle() != rhs.handle());
    }

    bool operator!= (const Any& lhs, const Handle& rhs)
    {
        return (lhs.handle() != rhs);
    }

    bool operator!= (const Handle& lhs, const Any& rhs)
    {
        return (lhs != rhs.handle());
    }

}
