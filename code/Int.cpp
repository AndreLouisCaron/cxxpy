// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Int.hpp"

namespace {

    ::PyObject * allocate ( long value )
    {
        ::PyObject *const object = ::PyInt_FromLong(value);
        if ( object == 0 )
        {
        }
        return (object);
    }

}

namespace py {

    Int::Int ( long value )
        : Object(::allocate(value))
    {
    }

}
