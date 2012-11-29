#ifndef _py_Callable_hpp__
#define _py_Callable_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Tuple.hpp"
#include "Map.hpp"

namespace py {

    /*!
     * @brief Function, bound method, function object, etc.
     */
    class Callable
    {
        /* class methods. */
    public:
        static bool is_a (const Handle& handle);

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Callable (const Handle& handle);
        Callable (const Any& object);

        /* methods. */
    public:
        const Handle& handle () const;
        void swap(Callable& other);

        /* operators. */
    public:
        operator Any () const;

        Any operator() (const Tuple& pargs) const;
        Any operator() (const Tuple& pargs, const Map& nargs) const;
        Any operator() (const Map& nargs) const;
    };

}

#endif /* _py_Callable_hpp__ */
