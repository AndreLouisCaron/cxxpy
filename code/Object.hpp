#ifndef _py_Object_hpp__
#define _py_Object_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>

namespace py {

    typedef Py_ssize_t ssize_t;

    class Map;
    class Type;

      /*!
       * @brief Base class for all python variables.
       */
    class Object
    {
        /* nested types. */
    public:
        typedef ::PyObject* Handle;

        /* class methods. */
    public:
        static Handle acquire ( Handle object );
        static Handle release ( Handle object );

        typedef Handle(*Transfer)(Handle);
        static Transfer steal ();
        static Transfer share ();

        /* data. */
    protected:
        Handle myHandle;

        /* construction. */
    public:
        Object ();
        explicit Object ( Handle handle, Transfer transfer=share() );
        Object ( const Object& other );
        ~Object ();

        /* methods. */
    public:
        Handle handle () const;

        const Type type () const;
        const size_t size () const;

        const Map dir () const;

        Handle release ();

    protected:
        void swap ( Object& rhs );

        /* operators. */
    private:
            // Prohibited.  Leads to errors in class hierarchy (allows
            // copy from an unrelated object also derived from Object).
        Object& operator= ( const Object& );

    public:
        operator bool () const;
        bool operator! () const;
    };

    template<typename T>
    bool isa ( const Object::Handle& handle )
    {
        return (T::isa(handle));
    }

    template<typename T>
    Object::Handle check ( const Object::Handle& handle )
    {
        if ( !isa<T>(handle) ) {
            throw (std::bad_cast());
        }
        return (handle);
    }

}

#endif /* _py_Object_hpp__ */
