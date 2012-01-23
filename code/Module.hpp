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
#include "Object.hpp"
#include "Map.hpp"

namespace py {

      /*!
       * @brief Python code module (".py" file).
       */
    class Module :
        public Object
    {
        /* nested types. */
    public:
        class Lock;

        /* class methods. */
    public:
        static Module load ( const std::string& name, const std::string& path );

        /* construction. */
    public:
        explicit Module ( Handle handle );
        explicit Module ( const Object& object );

        /* methods. */
    public:
        const Map symbols () const;
        Object symbol ( const std::string& name ) const;

        Module reload ();
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
