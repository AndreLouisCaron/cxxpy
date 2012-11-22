#ifndef _py_Type_hpp__
#define _py_Type_hpp__

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
       * @brief Run-time type information.
       */
    class Type :
        public Object
    {
        /* class methods. */
    public:
        static bool Type::isa ( const Object& object );

        /* construction. */
    public:
        Type (const Handle& handle);
        explicit Type ( const Object& object );

        /* methods. */
    public:
        bool subtypeof ( const Type& other ) const;
    };

}

#endif /* _py_Type_hpp__ */
