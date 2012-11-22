#ifndef _py_List_hpp__
#define _py_List_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Any.hpp"
#include "Tuple.hpp"

namespace py {

    /*!
     * @brief Variable-length list of items (array, vector).
     *
     * @see http://docs.python.org/c-api/list.html
     */
    class List
    {
        /* nested types. */
    public:
        typedef py::ssize_t size_type;

    private:
        class Proxy;

        /* class methods. */
    public:
        static bool is_a (const Handle& handle, bool exact=false);

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit List (const Handle& handle);
        List (const Any& any);

        List ();
        explicit List ( size_type size );

        /* methods. */
    public:
        const Handle& handle () const;

        void swap (List& other);

        size_type size () const;

        void append ( const Any& item );

        /* operators. */
    public:
        operator Any () const;

        Any operator[] ( size_type index ) const;
        Proxy operator[] ( size_type index );
    };

    class List::Proxy
    {
        /* data. */
    private:
        List* myList;
        size_type myIndex;

        /* construction. */
    public:
        Proxy ( List& tuple, size_type index );

        /* operators. */
    public:
        Proxy& operator= ( const Any& object );
        operator py::Any () const;
    };

}

#endif /* _py_List_hpp__ */
