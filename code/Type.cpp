// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Type.hpp"

namespace py {

    bool Type::is_a ( const Handle& handle )
    {
        return (PyType_Check(handle) != 0);
    }

    Type::Type (const Handle& handle)
        : myHandle(handle)
    {
    }

    Type::Type ( const Any& object )
        : myHandle(object.handle())
    {
    }

    const Handle& Type::handle () const
    {
        return (myHandle);
    }

    void Type::swap(Type& other)
    {
        myHandle.swap(other.myHandle);
    }

    bool Type::subtypeof ( const Type& other ) const
    {
        return (::PyType_IsSubtype(
                    (::PyTypeObject*)handle().data(),
                    (::PyTypeObject*)other.handle().data()) != 0);
    }

    Type::operator Any () const
    {
        return (Any(myHandle));
    }

}
