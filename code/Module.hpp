#ifndef _py_Module_hpp__
#define _py_Module_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include <string>
#include "Any.hpp"
#include "Map.hpp"

namespace py {

      /*!
       * @brief Python code module (".py" file).
       */
    class Module
    {
        /* nested types. */
    public:
        class Lock;

        /* class methods. */
    public:
        static Module load ( const std::string& name, const std::string& path );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Module (const Handle& handle);
        explicit Module (const Any& object);

        /* methods. */
    public:
        const Handle& handle () const;
        void swap(Module& module);

        const Map symbols () const;
        Any symbol (const std::string& name) const;

        Module reload ();

        /* operators. */
    public:
        operator Any () const;
    };

    class Module::Lock
    {
        /* construction. */
    public:
        Lock ();
        ~Lock ();
    };

    Map modules ();
    Module module ( const std::string& name );

    Module import ( const std::string& module );

    const Map builtins ();
    const Map globals ();
    const Map locals ();

}

#endif /* _py_Module_hpp__ */
