#ifndef _py_Handle_hpp__
#define _py_Handle_hpp__

// Copyright(c) 2011-2012, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include <exception>
#include <iosfwd>

namespace py {

    typedef Py_ssize_t ssize_t;

    class null_reference
        : public std::exception
    {
    public:
        virtual const char * what () const throw();
    };

    class bad_cast
        : public std::exception
    {
    public:
        virtual const char * what () const throw();
    };

    class Handle
    {
        /* nested types. */
    public:
        typedef ::PyObject * Data;
        typedef void(*Free)(::PyObject*);

        /* data. */
    private:
        Data myData;
        Free myFree;

        /* construction. */
    public:
        Handle ();
        Handle (const Handle& rhs);
        explicit Handle (Data data, Free free);
        ~Handle();

        /* methods. */
    public:
        Data data () const;
        void free ();
        Data drop ();

        void swap (Handle& rhs);

        /* operators. */
    public:
        Handle& operator= (const Handle& rhs);

        operator Data () const;

        operator bool () const;
        bool operator! () const;
    };

    bool operator== (const Handle& lhs, const Handle& rhs);
    bool operator!= (const Handle& lhs, const Handle& rhs);

    std::ostream& operator<< (std::ostream& stream, const Handle& handle);
    std::wostream& operator<< (std::wostream& stream, const Handle& handle);

    /*!
     * @brief Wraps a Python object, doesn't manipulate the reference count.
     * @param object The Python object to wrap.
     * @return A handle that doesn't manage @a object's lifetime.
     * @exception null_reference @a object was a null pointer.
     *
     * @pre @a object is not a null pointer.
     *
     * @see steal
     * @see share
     */
    Handle proxy (::PyObject * object);

    /*!
     * @brief Wraps a Python object, stealing a reference to it.
     * @param object The Python object to wrap.
     * @return A handle that doesn't manage @a object's lifetime.
     * @exception null_reference @a object was a null pointer.
     *
     * @pre @a object is not a null pointer.
     *
     * @see proxy
     * @see share
     */
    Handle steal (::PyObject * object);

    /*!
     * @brief Wraps a Python object, incremeting the reference count.
     * @param object The Python object to wrap.
     * @return A handle that doesn't manage @a object's lifetime.
     * @exception null_reference @a object was a null pointer.
     *
     * @pre @a object is not a null pointer.
     *
     * @see steal
     * @see proxy
     */
    Handle share (::PyObject * object);

}

#endif /* _py_Handle_hpp__ */
