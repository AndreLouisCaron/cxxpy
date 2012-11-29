#ifndef _py_Object_hpp__
#define _py_Object_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Any.hpp"
#include "Handle.hpp"

namespace py {

    class Map;
    class Type;

      /*!
       * @brief Base class for all python variables.
       */
    class Object
    {
        /* data. */
    protected:
        Handle myHandle;

        /* construction. */
    public:
        Object ();
        Object (const Handle& handle);
        Object (const Object& other);
        Object (const Any& object);
        ~Object ();

        /* methods. */
    public:
        const Handle& handle () const;
        void swap(Object& other);

        const Type type () const;
        const size_t size () const;

        const Map dir () const;

        Handle release ();

        /* operators. */
    public:
        operator Any () const;

        operator bool () const;
        bool operator! () const;
    };

}

#endif /* _py_Object_hpp__ */
