// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Bytes.hpp"
#include "Error.hpp"
#include "String.hpp"

#include <cstring>

namespace {

    py::Handle allocate (const char * data)
    {
        ::PyObject *const object = ::PyString_FromString(data);
        if (object == 0)
        {
        }
        return (py::steal(object));
    }

    py::Handle allocate (const void * data, ::Py_ssize_t size)
    {
        ::PyObject *const object = ::PyString_FromStringAndSize
            (static_cast<const char*>(data), size);
        if (object == 0)
        {
        }
        return (py::steal(object));
    }

}

namespace py {

    bool Bytes::is_a (const Handle& handle, bool exact)
    {
        return (exact? PyString_CheckExact(handle.data())
                     : PyString_Check     (handle.data()));
    }

    Bytes::Bytes (const Handle& handle)
        : myHandle(check<Bytes>(handle))
    {
    }

    Bytes::Bytes (const Any& any)
        : myHandle(check<Bytes>(any.handle()))
    {
    }

    Bytes::Bytes (const char * data)
        : myHandle(::allocate(data))
    {
    }

    Bytes::Bytes (const void * data, size_type size)
        : myHandle(::allocate(data, size))
    {
    }

    Bytes::Bytes (const std::string& data)
        : myHandle(::allocate(data.c_str(), data.size()))
    {
    }

    const Handle& Bytes::handle () const
    {
        return (myHandle);
    }

    void Bytes::swap (Bytes& other)
    {
        myHandle.swap(other.myHandle);
    }

    Bytes::size_type Bytes::size () const
    {
        return (::PyString_Size(handle().data()));
    }

    const Bytes::char_type * Bytes::data () const
    {
        const char *const result = ::PyString_AsString(handle().data());
        if (result == 0) {
            Error::translate();
        }
        return (result);
    }

    const String Bytes::decode (const std::string& encoding) const
    {
        ::PyObject *const object = ::PyString_Decode
            (data(), size(), encoding.c_str(), "strict");
        if (object == 0)
        {
        }
        return (String(steal(object)));
    }

    Bytes& Bytes::operator= (const Bytes& rhs)
    {
        Bytes(rhs).swap(*this); return (*this);
    }

    Bytes::operator Any () const
    {
        return (Any(myHandle));
    }

    Bytes::operator std::string () const
    {
        return (std::string(data(), size()));
    }

    std::ostream& operator<< (std::ostream& stream, const Bytes& string)
    {
        return (stream.write(string.data(), string.size()));
    }

    bool operator== (const Bytes& lhs, const Bytes& rhs)
    {
        return (std::strcmp(lhs.data(), rhs.data()) == 0);
    }

    bool operator== (const Bytes& lhs, const char * rhs)
    {
        return (std::strcmp(lhs.data(), rhs) == 0);
    }

    bool operator== (const char * lhs, const Bytes& rhs)
    {
        return (std::strcmp(lhs, rhs.data()) == 0);
    }

}
