// Copyright(c) 2011-2012, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Handle.hpp"
#include <algorithm>
#include <iostream>

namespace {

    void abandon (::PyObject * object)
    {
        // No-op.
    }

    void release (::PyObject * object)
    {
        Py_XDECREF(object);
    }

}

namespace py {

    const char * null_reference::what () const throw()
    {
        return ("null reference to Python object");
    }

    const char * bad_cast::what () const throw()
    {
        return ("run-time type of Python object does not match expected type");
    }

    Handle::Handle ()
        : myData(0)
        , myFree(&::abandon)
    {
    }

    Handle::Handle (const Handle& rhs)
        : myData(rhs.myData)
        , myFree(&::abandon)
    {
        if (myData) {
            Py_INCREF(myData), myFree = &::release;
        }
    }

    Handle::Handle (Data data, Free free)
        : myData(data)
        , myFree(free)
    {
    }

    Handle::~Handle()
    {
        myFree(myData), myData = 0, myFree = &::abandon;
    }

    Handle::Data Handle::data () const
    {
        return (myData);
    }

    void Handle::free ()
    {
        myFree(myData), myData = 0, myFree = &::abandon;
    }

    Handle::Data Handle::drop ()
    {
        const Data data = myData;
        myData = 0, myFree = &::abandon;
        return (data);
    }

    void Handle::swap (Handle& rhs)
    {
        std::swap(myData, rhs.myData);
        std::swap(myFree, rhs.myFree);
    }

    Handle& Handle::operator= (const Handle& rhs)
    {
        Handle(rhs).swap(*this); return (*this);
    }

    Handle::operator Data () const
    {
        return (myData);
    }

    Handle::operator bool () const
    {
        return (myData != 0);
    }

    bool Handle::operator! () const
    {
        return (myData == 0);
    }

    bool operator== (const Handle& lhs, const Handle& rhs)
    {
        return (lhs.data() == rhs.data());
    }

    bool operator!= (const Handle& lhs, const Handle& rhs)
    {
        return (lhs.data() != rhs.data());
    }

    std::ostream& operator<< (std::ostream& stream, const Handle& handle)
    {
        return (stream << "0x" << handle.data());
    }

    std::wostream& operator<< (std::wostream& stream, const Handle& handle)
    {
        return (stream << L"0x" << handle.data());
    }

    Handle proxy (::PyObject * object)
    {
        return (Handle(object, &::abandon));
    }

    Handle steal (::PyObject * object)
    {
        if (object == 0) {
            throw (null_reference());
        }
        return (Handle(object, &::release));
    }

    Handle share (::PyObject * object)
    {
        if (object == 0) {
            throw (null_reference());
        }
        Py_INCREF(object);
        return (Handle(object, &::release));
    }

}
