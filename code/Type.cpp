// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Type.hpp"

namespace py {

    bool Type::isa ( const Object& object )
    {
        return (PyType_Check(object.handle()) != 0);
    }

    Type::Type (const Handle& handle)
        : Object(handle)
    {
    }

    Type::Type ( const Object& object )
        : Object(object.handle())
    {
    }

    bool Type::subtypeof ( const Type& other ) const
    {
        return (::PyType_IsSubtype(
                    (::PyTypeObject*)handle().data(),
                    (::PyTypeObject*)other.handle().data()) != 0);
    }

}
