// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Module.hpp"
#include "Bytes.hpp"
#include "Error.hpp"
#include "Callable.hpp"
#include "Tuple.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

    std::string readfile ( const std::string& path )
    {
        std::ifstream file(path.c_str());
        if ( !file.is_open() ) {
            throw (std::invalid_argument("path"));
        }
        std::ostringstream data;
        data << file.rdbuf();
        return (data.str());
    }

}

namespace py {

    Module Module::load ( const std::string& name, const std::string& path )
    {
          // Read the module source code.
        const std::string data = ::readfile(path);
        const std::string mode = "exec";
          // Compile the module source code to a code object.
        const Callable compile(module("__builtin__").symbol("compile"));
        Tuple arguments(3);
        arguments[0] = Bytes(data);
        arguments[1] = Bytes(path);
        arguments[2] = Bytes(mode);
        Any code = compile(arguments);
          // Build a module out of the code object.
        ::PyObject *const result = ::PyImport_ExecCodeModule(
            const_cast<char*>(name.c_str()), code.handle());
        if ( result == 0 ) {
            Error::translate();
        }
          // Return the module reference.
        return (Module(share(result)));
    }

    Module::Module (const Handle& handle)
        : myHandle(handle)
    {
    }

    Module::Module ( const Any& object )
        : myHandle(object.handle())
    {
    }

    const Handle& Module::handle () const
    {
        return (myHandle);
    }

    void Module::swap(Module& other)
    {
        std::swap(myHandle, other.myHandle);
    }

    const Map Module::symbols () const
    {
        ::PyObject *const result = ::PyModule_GetDict(handle());
        if ( result == 0 ) {
            // Documentation says it can never fail...
        }
        return (Map(share(result)));
    }

    Any Module::symbol ( const std::string& name ) const
    {
        return (symbols().get(name));
    }

    Module Module::reload ()
    {
        return (Module(share(::PyImport_ReloadModule(handle()))));
    }

    Module::operator Any () const
    {
        return (Any(myHandle));
    }

    Module::Lock::Lock ()
    {
        ::_PyImport_AcquireLock();
    }

    Module::Lock::~Lock ()
    {
        ::_PyImport_ReleaseLock();
    }

    Map modules ()
    {
        ::PyObject *const result = ::PyImport_GetModuleDict();
        if ( result == 0 ) {
            Error::translate();
        }
        return (Map(share(result)));
    }

    Module module ( const std::string& name )
    {
        return (Module(modules().get(name)));
    }

    Module import ( const std::string& module )
    {
        ::PyObject *const result = ::PyImport_ImportModule(module.c_str());
        if ( result == 0 ) {
            Error::translate();
        }
        return (Module(steal(result)));
    }

    const Map builtins ()
    {
        return (Map(share(::PyEval_GetBuiltins())));
    }

    const Map globals ()
    {
        return (Map(share(::PyEval_GetGlobals())));
    }

    const Map locals ()
    {
        return (Map(share(::PyEval_GetLocals())));
    }

}
