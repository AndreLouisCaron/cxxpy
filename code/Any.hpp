#ifndef _py_Any_hpp__
#define _py_Any_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file pyxx/Any.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Variant type, can contain "any" python object.
 */

#include <python.h>
#include <exception>
#include "Handle.hpp"

namespace py {

    class Any
    {
        /* data. */
    protected:
        Handle myHandle;

        /* construction. */
    public:
        Any ();
        explicit Any ( const Handle& handle );

        /* methods. */
    public:
        const Handle& handle () const;
        void swap(Any& other);

        Handle release ();

        template<typename T> bool is_a () const;

        template<typename T> T cast () const;

        /* operators. */
    public:
        Any& operator= ( const Any& object );
    };

    bool operator== (const Any& lhs, const Any& rhs);
    bool operator== (const Any& lhs, const Handle& rhs);
    bool operator== (const Handle& lhs, const Any& rhs);

    bool operator!= (const Any& lhs, const Any& rhs);
    bool operator!= (const Any& lhs, const Handle& rhs);
    bool operator!= (const Handle& lhs, const Any& rhs);

    template<typename T>
    bool Any::is_a () const
    {
        return (T::is_a(*this));
    }

    template<typename T>
    T Any::cast () const
    {
        return (T(check<T>(handle())));
    }

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
            throw (bad_cast());
        }
        return (handle);
    }

    template<typename T>
    T cast ( const Any& object )
    {
        return (object.cast<T>());
    }

}

#endif /* _py_Any_hpp__ */
