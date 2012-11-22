#ifndef _py_Map_hpp__
#define _py_Map_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include <string>
#include "Any.hpp"

namespace py {

      /*!
       * @brief Key-value mapping (dictionary).
       */
    class Map
    {
        /* class methods. */
    public:
        static bool is_a (const Handle& handle, bool exact=false);

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Map (const Handle& handle);
        Map (const Any& any);

        Map ();
        Map (const Map& rhs);

        /* methods. */
    public:
        const Handle& handle () const;
        void swap (Map& other);

        Any get ( const std::string& key ) const;
        Any get ( const Any& key ) const;
        Any get ( const std::string& key, const Any& fallback ) const;
        Any get ( const Any& key, const Any& fallback ) const;
        void put ( const std::string& key, const std::string& value );
        void put ( const std::string& key, const Any& value );
        void put ( const Any& key, const Any& value );
        void del ( const Any& key );
        void del ( const std::string& key );

        void clear ();

        Map clone () const;

        /* operators. */
    public:
        operator Any () const;
    };

}

#endif /* _py_Map_hpp__ */
