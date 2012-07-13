#ifndef _py_Lock_hpp__
#define _py_Lock_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2012
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include <iosfwd>
#include <string>

namespace py {

    /*!
     * @brief Release the interpreter lock when entering C from Python.
     *
     * An instance of this class must be alive when calling into a C extension
     * that intends to perform I/O or a long running CPU-bound operation.
     *
     * @see http://docs.python.org/c-api/init.html
     */
    class Leave
    {
        /* nested types. */
    public:
        typedef ::PyThreadState * State;

        /* data. */
    private:
        State myState;

        /* construction. */
    public:
        Leave ();

    private:
        Leave (const Leave&);

    public:
        ~Leave ();

    private:
        Leave& operator= (const Leave& rhs);
    };

    /*!
     * @brief Acquire the interpreter lock when entering Python from C.
     *
     * An instance of this class must be alive when calling into the Python
     * interpreter from a non-Python thread.
     *
     * @see http://docs.python.org/c-api/init.html
     */
    class Enter
    {
        /* nested types. */
    public:
        typedef ::PyGILState_STATE State;

        /* data. */
    private:
        State myState;

        /* construction. */
    public:
        Enter ();

    private:
        Enter (const Enter&);

    public:
        ~Enter ();

    private:
        Enter& operator= (const Enter& rhs);
    };

}

#endif /* _py_Enter_hpp__ */
