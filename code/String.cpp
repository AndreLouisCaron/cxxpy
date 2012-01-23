// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "String.hpp"
#include "Bytes.hpp"

namespace {

    ::PyObject * allocate ( const wchar_t * data, ::Py_ssize_t size )
    {
        ::PyObject *const object = ::PyUnicode_FromWideChar(data, size);
        if ( object == 0 )
        {
        }
        return (object);
    }

}

namespace py {

    bool String::isa ( const Object& object, bool exact )
    {
        return (exact? PyUnicode_CheckExact(object.handle())
                     : PyUnicode_Check     (object.handle()));
    }

    String::String ( const Object& object )
        : Object(object)
    {
    }

    String::String ( Handle handle, Transfer transfer )
        : Object(handle, transfer)
    {
    }

    String::String ( const wchar_t * data )
        : Object(::allocate(data, ::wcslen(data)), Object::steal())
    {
    }

    String::String ( const wchar_t * data, size_type size )
        : Object(::allocate(data, size), Object::steal())
    {
    }

    String::String ( const std::wstring& data )
        : Object(::allocate(data.c_str(), data.size()), Object::steal())
    {
    }

    String::size_type String::size () const
    {
        return (::PyUnicode_GetSize(handle()));
    }

    const String::char_type * String::data () const
    {
        return (::PyUnicode_AsUnicode(handle()));
    }

    const Bytes String::encode ( const std::string& encoding ) const
    {
        ::PyObject *const object = ::PyUnicode_Encode
            (data(), size(), encoding.c_str(), "strict");
        if ( object == 0 )
        {
        }
        return (Bytes(object, steal()));
    }

    String::operator std::wstring () const
    {
        return (std::wstring(data(), size()));
    }

    std::wostream& operator<< ( std::wostream& stream, const String& string )
    {
        return (stream.write(string.data(), string.size()));
    }

}
