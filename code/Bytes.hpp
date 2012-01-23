#ifndef _py_Bytes_hpp__
#define _py_Bytes_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Object.hpp"
#include <iosfwd>
#include <string>

namespace py {

    class String;

      /*!
       * @brief Encoded string (byte string).
       */
    class Bytes :
        public Object
    {
        /* nested types. */
    public:
        typedef py::ssize_t size_type;
        typedef char char_type;

        /* class methods. */
    public:
        static bool isa ( const Object& object, bool exact=false );

        /* construction. */
    public:
        explicit Bytes ( const Object& object );
        explicit Bytes ( Handle handle, Transfer transfer=share() );
        Bytes ( const char * data );
        Bytes ( const void * data, size_type size );
        Bytes ( const std::string& data );

        /* methods. */
    public:
          /*!
           * @brief Obtain the length of the string, in bytes.
           */
        size_type size () const;

          /*!
           * @brief Obtain a pointer to the bytes in the string.
           */
        const char_type * data () const;

          /*!
           * @brief Decodes series of bytes to string.
           */
        const String decode ( const std::string& encoding ) const;

        /* operators. */
    public:
        Bytes& operator= ( const Bytes& rhs );

          /*!
           * @brief Obtain standard string for compatibility with other code.
           * @warning There is @b absolutely no guarantee that the returned
           *  contents may safely be interpreted as ASCII text.  Beware!
           */
        operator std::string () const;
    };

      /*!
       * @brief Output to standard stream.
       */
    std::ostream& operator<< ( std::ostream& stream, const Bytes& string );

      /*!
       * @brief Compare two strings for equality.
       */
    bool operator== ( const Bytes& lhs, const Bytes& rhs );
    bool operator== ( const Bytes& lhs, const char * rhs );
    bool operator== ( const char * lhs, const Bytes& rhs );

}

#endif /* _py_Bytes_hpp__ */
