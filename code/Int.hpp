#ifndef _py_Int_hpp__
#define _py_Int_hpp__

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
       * @brief Fixed-length integer type.
       *
       * @see http://docs.python.org/c-api/int.html
       */
    class Int
    {
        /* class methods. */
    public:
        static bool is_a (const Handle& handle, bool exact=false);

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Int (const Handle& handle);
        Int (const Any& any);

        Int (int value=0);
        Int (long value);

        /* methods. */
    public:
        const Handle& handle () const;
        void swap (Int& other);

        /* operators. */
    public:
        operator Any () const;
        operator long () const;
    };

}

#endif /* _py_Int_hpp__ */
