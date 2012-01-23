// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Map.hpp"
#include "Error.hpp"

namespace {

    ::PyObject * allocate ()
    {
        ::PyObject *const result = ::PyDict_New();
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (result);
    }

}

namespace py {

    bool Map::isa ( const Object& object, bool exact )
    {
        return (exact? PyDict_CheckExact(object.handle())
                     : PyDict_Check     (object.handle()));
    }

    Map::Map ()
        : Object(::allocate(), Object::steal())
    {
    }

    Map::Map ( Handle handle, Transfer transfer )
        : Object(handle, transfer)
    {
    }

    Object Map::get ( const std::string& key ) const
    {
        ::PyObject *const result =
            ::PyDict_GetItemString(handle(), key.c_str());
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (Object(result, Object::steal()));
    }

    Object Map::get ( const Object& key ) const
    {
        ::PyObject *const result = ::PyDict_GetItem(handle(), key.handle());
        if ( result == 0 ) {
            py::Error::translate();
        }
        return (Object(result, Object::steal()));
    }

    Object Map::get ( const std::string& key, const Object& fallback ) const
    {
        ::PyObject *const result = ::PyDict_GetItemString(handle(), key.c_str());
        if ( result == 0 )
        {
            if (::PyErr_ExceptionMatches(::PyExc_KeyError)) {
                return (fallback);
            }
            py::Error::translate();
        }
        return (Object(result, Object::steal()));
    }

    Object Map::get ( const Object& key, const Object& fallback ) const
    {
        ::PyObject *const result = ::PyDict_GetItem(handle(), key.handle());
        if ( result == 0 )
        {
            if (::PyErr_ExceptionMatches(::PyExc_KeyError)) {
                return (fallback);
            }
            py::Error::translate();
        }
        return (Object(result, Object::steal()));
    }

    void Map::put ( const Object& key, const Object& value )
    {
        const int result = ::PyDict_SetItem
            (handle(), key.handle(), value.handle());
        if ( result == -1 ) {
            py::Error::translate();
        }
    }

    void Map::put ( const std::string& key, const Object& value )
    {
        const int result = ::PyDict_SetItemString
            (handle(), key.c_str(), value.handle());
        if ( result == -1 ) {
            py::Error::translate();
        }
    }

    void Map::del ( const Object& key )
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
        return (Map(result, Object::steal()));
    }

}
