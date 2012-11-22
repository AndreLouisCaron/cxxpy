// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Map.hpp"
#include "Error.hpp"

namespace {

    py::Handle allocate ()
    {
        ::PyObject *const result = ::PyDict_New();
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (py::steal(result));
    }

}

namespace py {

    bool Map::is_a (const Handle& handle, bool exact)
    {
        return (exact? PyDict_CheckExact(handle)
                     : PyDict_Check     (handle));
    }

    Map::Map (const Handle& handle)
        : myHandle(check<Map>(handle))
    {
    }

    Map::Map (const Any& any)
        : myHandle(check<Map>(any.handle()))
    {
    }

    Map::Map ()
        : myHandle(::allocate())
    {
    }

    Map::Map (const Map& rhs)
        : myHandle(rhs.handle())
    {
    }

    const Handle& Map::handle () const
    {
        return (myHandle);
    }

    void Map::swap (Map& other)
    {
        myHandle.swap(other.myHandle);
    }

    Any Map::get ( const std::string& key ) const
    {
        ::PyObject *const result =
            ::PyDict_GetItemString(handle(), key.c_str());
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (Any(share(result)));
    }

    Any Map::get ( const Any& key ) const
    {
        ::PyObject *const result = ::PyDict_GetItem(handle(), key.handle());
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (Any(share(result)));
    }

    Any Map::get ( const std::string& key, const Any& fallback ) const
    {
        ::PyObject *const result =
            ::PyDict_GetItemString(handle(), key.c_str());
        if ( result == 0 )
        {
            if (::PyErr_ExceptionMatches(::PyExc_KeyError)) {
                return (fallback);
            }
            py::Error::translate();
        }
        return (Any(share(result)));
    }

    Any Map::get ( const Any& key, const Any& fallback ) const
    {
        ::PyObject *const result = ::PyDict_GetItem(handle(), key.handle());
        if ( result == 0 )
        {
            if (::PyErr_ExceptionMatches(::PyExc_KeyError)) {
                return (fallback);
            }
            py::Error::translate();
        }
        return (Any(share(result)));
    }

    void Map::put ( const Any& key, const Any& value )
    {
        const int result = ::PyDict_SetItem
            (handle(), key.handle(), value.handle());
        if ( result == -1 ) {
            py::Error::translate();
        }
    }

    void Map::put ( const std::string& key, const Any& value )
    {
        const int result = ::PyDict_SetItemString
            (handle(), key.c_str(), value.handle());
        if ( result == -1 ) {
            py::Error::translate();
        }
    }

    void Map::put ( const std::string& key, const std::string& value )
    {
        put(key, Any(Bytes(value)));
    }

    void Map::del ( const Any& key )
    {
        const int result = ::PyDict_DelItem(handle(), key.handle());
        if ( result == -1 ) {
            py::Error::translate();
        }
    }

    void Map::del ( const std::string& key )
    {
        const int result = ::PyDict_DelItemString(handle(), key.c_str());
        if ( result == -1 ) {
            py::Error::translate();
        }
    }

    void Map::clear ()
    {
        ::PyDict_Clear(handle());
    }

    Map Map::clone () const
    {
        ::PyObject *const result = ::PyDict_Copy(handle());
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (Map(steal(result)));
    }

    Map::operator Any () const
    {
        return (Any(myHandle));
    }

}
