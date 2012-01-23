// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Callable.hpp"
#include "Error.hpp"

namespace {

    ::PyObject * invoke
        ( ::PyObject * callable, ::PyObject * pargs, ::PyObject * nargs )
    {
           // Attempt to invoke callable.
        ::PyObject *const result =
            ::PyEval_CallObjectWithKeywords(
            py::Object::acquire(callable),
            py::Object::acquire(pargs),
            py::Object::acquire(nargs)
            );
          // If an error occured,
        if ( result == 0 )
        {
              // release abandoned references;
            py::Object::release(callable);
            py::Object::release(pargs);
            py::Object::release(nargs);
              // raise equivalent C++ exception.
            py::Error::translate();
        }
          // Caller owns result.
        return (result);
    }

}

namespace py {

    bool Callable::isa ( const Object& object )
    {
        return (::PyCallable_Check(object.handle()) != 0);
    }

    Callable::Callable ( const Object& object )
        : Object(object.handle())
    {
    }

    Callable::Callable ( Handle handle )
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
