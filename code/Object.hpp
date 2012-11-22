#ifndef _py_Object_hpp__
#define _py_Object_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include <typeinfo>

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
        ~Object ();

        /* methods. */
    public:
        const Handle& handle () const;

        const Type type () const;
        const size_t size () const;

        const Map dir () const;

        Handle release ();

    protected:
        void swap (Object& rhs);

        /* operators. */
    private:
        // Prohibited.  Leads to errors in class hierarchy (allows
        // copy from an unrelated object also derived from Object).
        Object& operator= (const Object&);

    public:
        operator bool () const;
        bool operator! () const;
    };

    template<typename T>
    bool is_a (const Handle& handle)
    {
        return (!handle || T::is_a(handle));
    }

    template<typename T>
    Handle check (const Handle& handle)
    {
        if (!handle) {
            return (handle);
        }
        if (!is_a<T>(handle)) {
            throw (std::bad_cast());
        }
        return (handle);
    }

}

#endif /* _py_Object_hpp__ */
