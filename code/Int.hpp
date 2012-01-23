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
       */
    class Int :
        public Object
    {
        /* construction. */
    public:
        Int ( long value=0 );
    };

}

#endif /* _py_Int_hpp__ */
