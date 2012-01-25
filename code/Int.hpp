#ifndef _py_Int_hpp__
#define _py_Int_hpp__

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
       * @brief Fixed-length integer type.
       *
       * @see http://docs.python.org/c-api/int.html
       */
    class Int :
        public Object
    {
        /* class methods. */
    public:
        static bool isa ( Handle handle, bool exact=false );
        static bool isa ( const Object& object, bool exact=false );

        /* construction. */
    public:
        Int ( int value=0 );
        Int ( long value );

        explicit Int ( Handle handle );
        explicit Int ( const Object& object );

        /* operators. */
    public:
        operator long () const;
    };

}

#endif /* _py_Int_hpp__ */
