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

#include "Object.hpp"
#include <python.h>

namespace py {

    class Any :
        public Object
    {
        /* construction. */
    public:
        explicit Any ( const Handle& handle );

        Any ();
        Any ( const Object& object );

        /* methods. */
    public:
        template<typename T> T cast () const;

        /* operators. */
    public:
        Any& operator= ( const Any& object );
    };

    template<typename T>
    T Any::cast () const
    {
        return (T(check<T>(handle())));
    }

    template<typename T>
    T cast ( const Any& object )
    {
        return (object.cast<T>());
    }

}

#endif /* _py_Any_hpp__ */
