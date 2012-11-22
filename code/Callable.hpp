#ifndef _py_Callable_hpp__
#define _py_Callable_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Object.hpp"
#include "Tuple.hpp"
#include "Map.hpp"

namespace py {

    /*!
     * @brief Function, bound method, function object, etc.
     */
    class Callable :
        public Object
    {
        /* class methods. */
    public:
        static bool isa (const Object& object);

        /* construction. */
    public:
        explicit Callable (const Object& object);
        explicit Callable (const Handle& handle);

        /* operators. */
    public:
        Object operator() (const Tuple& pargs) const;
        Object operator() (const Tuple& pargs, const Map& nargs) const;
        Object operator() (const Map& nargs) const;
    };

}

#endif /* _py_Callable_hpp__ */
