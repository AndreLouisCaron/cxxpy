#ifndef _py_Bytes_hpp__
#define _py_Bytes_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Any.hpp"
#include <iosfwd>
#include <string>

namespace py {

    class Any;
    class String;

    /*!
     * @brief Encoded string (byte string).
     *
     * @see http://docs.python.org/c-api/string.html
     */
    class Bytes
    {
        /* nested types. */
    public:
        typedef py::ssize_t size_type;
        typedef char char_type;

        /* class methods. */
    public:
        static bool is_a (const Handle& handle, bool exact=false);

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Bytes (const Handle& handle);
        Bytes (const Any& any);

        Bytes (const char * data);
        Bytes (const void * data, size_type size);
        Bytes (const std::string& data);

        /* methods. */
    public:
        const Handle& handle () const;

        void swap (Bytes& other);

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
        const String decode (const std::string& encoding) const;

        /* operators. */
    public:
        Bytes& operator= (const Bytes& rhs);

        operator Any () const;

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
    std::ostream& operator<< (std::ostream& stream, const Bytes& string);

    /*!
     * @brief Compare two strings for equality.
     */
    bool operator== (const Bytes& lhs, const Bytes& rhs);
    bool operator== (const Bytes& lhs, const char * rhs);
    bool operator== (const char * lhs, const Bytes& rhs);

}

#endif /* _py_Bytes_hpp__ */
