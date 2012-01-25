#ifndef _py_List_hpp__
#define _py_List_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Object.hpp"
#include "Tuple.hpp"

namespace py {

    /*!
     * @brief Variable-length list of items (array, vector).
     *
     * @see http://docs.python.org/c-api/list.html
     */
    class List :
        public Object
    {
        /* nested types. */
    public:
        typedef py::ssize_t size_type;

    private:
        class Proxy;

        /* class methods. */
    public:
        static bool isa ( const Object& object, bool exact=false );

        /* construction. */
    public:
        List ();
        explicit List ( const Object& object );
        explicit List ( Handle handle );
        explicit List ( size_type size );

        /* methods. */
    public:
        size_type size () const;

        void append ( const Object& item );

        /* operators. */
    public:
        Object operator[] ( size_type index ) const;
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
        Proxy& operator= ( const Object& object );
        operator py::Object () const;
    };

}

#endif /* _py_List_hpp__ */
