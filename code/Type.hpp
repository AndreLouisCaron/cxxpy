#ifndef _py_Type_hpp__
#define _py_Type_hpp__

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
       * @brief Run-time type information.
       */
    class Type
    {
        /* class methods. */
    public:
        static bool Type::is_a ( const Handle& handle );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Type (const Handle& handle);
        Type ( const Any& object );

        /* methods. */
    public:
        const Handle& handle () const;
        void swap(Type& other);

        bool subtypeof ( const Type& other ) const;

        /* operators. */
    public:
        operator Any () const;
    };

}

#endif /* _py_Type_hpp__ */
