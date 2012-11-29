// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "String.hpp"
#include "Bytes.hpp"

namespace {

    py::Handle allocate ( const wchar_t * data, ::Py_ssize_t size )
    {
        ::PyObject *const object = ::PyUnicode_FromWideChar(data, size);
        if (object == 0)
        {
        }
        return (py::steal(object));
    }

}

namespace py {

    bool String::is_a ( const Handle& handle, bool exact )
    {
        return (exact? PyUnicode_CheckExact(handle)
                     : PyUnicode_Check     (handle));
    }

    String::String (const Any& any)
        : myHandle(check<String>(any.handle()))
    {
    }

    String::String (const Handle& handle)
        : myHandle(check<String>(handle))
    {
    }

    String::String ( const wchar_t * data )
        : myHandle(::allocate(data, ::wcslen(data)))
    {
    }

    String::String ( const wchar_t * data, size_type size )
        : myHandle(::allocate(data, size))
    {
    }

    String::String ( const std::wstring& data )
        : myHandle(::allocate(data.c_str(), data.size()))
    {
    }

    const Handle& String::handle () const
    {
        return (myHandle);
    }

    void String::swap (String& other)
    {
        myHandle.swap(other.myHandle);
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
        return (Bytes(steal(object)));
    }

    String::operator Any () const
    {
        return (Any(myHandle));
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
