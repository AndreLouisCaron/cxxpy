#ifndef _py_None_hpp__
#define _py_None_hpp__

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
       * @brief Placeholder for "nothing", "nil", "null", etc.
       *
       * @see http://docs.python.org/c-api/none.html
       */
    class None
    {
        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        None ();

        /* methods. */
    public:
        const Handle& handle () const;

        /* operators. */
    public:
        operator Any () const;
    };

}

#endif /* _py_None_hpp__ */
