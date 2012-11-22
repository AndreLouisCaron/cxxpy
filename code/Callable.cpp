// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Callable.hpp"
#include "Error.hpp"

namespace {

    py::Handle invoke
        ( ::PyObject * callable, ::PyObject * pargs, ::PyObject * nargs )
    {
        // Increase reference for call.
        Py_XINCREF(callable);
        Py_XINCREF(pargs);
        Py_XINCREF(nargs);
        // Attempt to invoke callable.
        ::PyObject *const result =
              ::PyEval_CallObjectWithKeywords(callable, pargs, nargs);
        // If an error occured,
        if ( result == 0 )
        {
            // release abandoned references;
            Py_XDECREF(callable);
            Py_XDECREF(pargs);
            Py_XDECREF(nargs);
            // raise equivalent C++ exception.
            py::Error::translate();
        }
        // Caller owns result.
        return (py::steal(result));
    }

}

namespace py {

    bool Callable::isa (const Object& object)
    {
        return (::PyCallable_Check(object.handle()) != 0);
    }

    Callable::Callable (const Object& object)
        : Object(object.handle())
    {
    }

    Callable::Callable (const Handle& handle)
        : Object(handle)
    {
    }

    Object Callable::operator() ( const Tuple& pargs ) const
    {
        return (Object(::invoke(handle(), pargs.handle(), 0)));
    }

    Object Callable::operator() ( const Tuple& pargs, const Map& nargs ) const
    {
        return (Object(::invoke(handle(), pargs.handle(), nargs.handle())));
    }

    Object Callable::operator() ( const Map& nargs ) const
    {
        return (Object(::invoke(handle(), 0, nargs.handle())));
    }

}
