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
        Object code = compile(arguments);
          // Build a module out of the code object.
        ::PyObject *const result = ::PyImport_ExecCodeModule(
            const_cast<char*>(name.c_str()), code.handle());
        if ( result == 0 ) {
            Error::translate();
        }
          // Return the module reference.
        return (Module(Object::acquire(result)));
    }

    Module::Module ( Handle handle )
        : Object(handle)
    {
    }

    Module::Module ( const Object& object )
        : Object(object.handle())
    {
    }

    const Map Module::symbols () const
    {
        ::PyObject *const result = ::PyModule_GetDict(handle());
        if ( result == 0 ) {
            // Documentation says it can never fail...
        }
        return (Map(result, share()));
    }

    Object Module::symbol ( const std::string& name ) const
    {
        return (symbols().get(name));
    }

    Module Module::reload ()
    {
        return (Module(::PyImport_ReloadModule(handle())));
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
        return (Map(result));
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
        return (Module(result));
    }

    const Map builtins ()
    {
        return (Map(::PyEval_GetBuiltins()));
    }

    const Map globals ()
    {
        return (Map(::PyEval_GetGlobals()));
    }

    const Map locals ()
    {
        return (Map(::PyEval_GetLocals()));
    }

}
