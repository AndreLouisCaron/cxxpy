#ifndef _py_Tuple_hpp__
#define _py_Tuple_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Any.hpp"

namespace py {

    /*!
     * @brief Container of fixed length.
     *
     * @see http://docs.python.org/c-api/tuple.html
     */
    class Tuple
    {
        /* nested types. */
    public:
        typedef py::ssize_t size_type;

    private:
        class Proxy;

        /* class methods. */
    public:
        static bool is_a (const Handle& object, bool exact=false);

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Tuple (const Handle& handle);
        Tuple (const Any& any);

        Tuple (size_type size);

        /* methods. */
    public:
        const Handle& handle () const;
        void swap (Tuple& other);

        size_type size () const;

        /* operators. */
    public:
        operator Any () const;
        Any operator[] ( size_type index ) const;
        Proxy operator[] ( size_type index );
    };

    class Tuple::Proxy
    {
        /* data. */
    private:
        Tuple* myTuple;
        size_type myIndex;

        /* construction. */
    public:
        Proxy ( Tuple& tuple, size_type index );

        /* operators. */
    public:
        Proxy& operator= ( const Any& object );
        operator Any () const;
    };

}

#endif /* _py_Tuple_hpp__ */
