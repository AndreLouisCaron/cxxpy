#ifndef _py_Tuple_hpp__
#define _py_Tuple_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Object.hpp"

namespace py {

      /*!
       * @brief Container of fixed length.
       */
    class Tuple :
        public Object
    {
        /* nested types. */
    public:
        typedef py::ssize_t size_type;

    private:
        class Proxy;

        /* class methods. */
    public:
        static bool isa ( const Object& object, bool exact=false );

        /* construction. */
    public:
        explicit Tuple ( const Object& object );
        explicit Tuple ( Handle handle );
        Tuple ( size_type size );

        /* methods. */
    public:
        size_type size () const;

        /* operators. */
    public:
        Object operator[] ( size_type index ) const;
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
        Proxy& operator= ( const Object& object );
        operator py::Object () const;
    };

}

#endif /* _py_Tuple_hpp__ */
