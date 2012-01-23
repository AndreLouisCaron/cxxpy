#ifndef _py_Library_hpp__
#define _py_Library_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>

namespace py {

      /*!
       * @brief Python interpreter.
       */
    class Library
    {
        /* construction. */
    public:
        Library ();
        ~Library ();
    };

}

#endif /* _py_Library_hpp__ */
