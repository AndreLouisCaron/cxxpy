#ifndef _py_Bool_hpp__
#define _py_Bool_hpp__

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
       * @brief Native boolean type.
       *
       * @see http://docs.python.org/c-api/bool.html
       */
    class Bool
    {
        /* class methods. */
    public:
        static bool is_a (const Handle& handle);

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Bool (const Handle& handle);
        Bool (const Any& any);

        Bool (bool value=false);

        /* methods. */
    public:
        const Handle& handle () const;
        void swap(Bool& other);

        /* operators. */
    public:
        operator Any () const;
    };

    Bool True ();
    Bool False ();

}

#endif /* _py_Bool_hpp__ */
