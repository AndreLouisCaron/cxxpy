#ifndef _py_String_hpp__
#define _py_String_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Object.hpp"
#include <string>

namespace py {

    class Bytes;

    /*!
     * @brief Decoded string (Unicode string).
     *
     * @see http://docs.python.org/c-api/unicode.html
     */
    class String :
        public Object
    {
        /* nested types. */
    public:
        typedef py::ssize_t size_type;
        typedef ::Py_UNICODE char_type;

        /* class methods. */
    public:
        /*!
         * @brief Checks if @a object is a string (or derived type).
         * @param exact Set to true to reject derived types.
         */
        static bool isa ( const Object& object, bool exact=false );

        /* construction. */
    public:
        /*!
         * @brief Cast a generic object to a string.
         * @pre @code String::isa(object) == true @endcode
         */
        explicit String ( const Object& object );
        String ( Handle handle, Transfer transfer=share() );
        explicit String ( const wchar_t * data );
        explicit String ( const wchar_t * data, size_type size );
        explicit String ( const std::wstring& data );

        /* methods. */
    public:
        /*!
         * @brief Obtain the length of the string, in code points.
         * @warning This does not necessarily equal the number of "characters"
         *  in the string.  Surrogate pairs are not counted as a single
         *  character.
         */
        size_type size () const;

        /*!
         * @brief Obtain a pointer to the code points in the string.
         */
        const char_type * data () const;

        /*!
         * @brief Encode string to series of bytes.
         */
        const Bytes encode ( const std::string& encoding ) const;

        /* operators. */
    public:
        /*!
         * @brief Obtain standard string for compatibility with other code.
         */
        operator std::wstring () const;
    };

    /*!
     * @brief Output to standard stream.
     */
    std::wostream& operator<< ( std::wostream& stream, const String& string );

}

#endif /* _py_String_hpp__ */
