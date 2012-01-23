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
#include "Object.hpp"

namespace py {

      /*!
       * @brief Key-value mapping (dictionary).
       */
    class Map :
        public Object
    {
        /* class methods. */
    public:
        static bool isa ( const Object& object, bool exact=false );

        /* construction. */
    public:
        Map ();
        Map ( Handle handle, Transfer transfer=share() );

        /* methods. */
    public:
        Object get ( const std::string& key ) const;
        Object get ( const Object& key ) const;
        Object get ( const std::string& key, const Object& fallback ) const;
        Object get ( const Object& key, const Object& fallback ) const;
        void put ( const Object& key, const Object& value );
        void put ( const std::string& key, const Object& value );
        void del ( const Object& key );
        void del ( const std::string& key );

        void clear ();

        Map clone () const;

        /* operators. */
    public:
    };

}

#endif /* _py_Map_hpp__ */
