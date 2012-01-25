#ifndef _py_Bool_hpp__
#define _py_Bool_hpp__

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
       * @brief Native boolean type.
       *
       * @see http://docs.python.org/c-api/bool.html
       */
    class Bool :
        public Object
    {
        /* class methods. */
    public:
        static bool isa ( Handle handle );
        static bool isa ( const Object& object );

        /* construction. */
    public:
        Bool ( bool value=false );

        explicit Bool ( Handle handle );
        explicit Bool ( const Object& object );
    };

    Bool True ();
    Bool False ();

}

#endif /* _py_Bool_hpp__ */
