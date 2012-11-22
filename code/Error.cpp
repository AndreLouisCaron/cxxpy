// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Error.hpp"

#define TRANSLATE(X) \
    if (::PyErr_ExceptionMatches(PyExc_##X)) { throw (X()); }

namespace {

    py::Handle content ()
    {
        // Get exception information.
        ::PyObject * type = 0;
        ::PyObject * value = 0;
        ::PyObject * traceback = 0;
        ::PyErr_Fetch(&type, &value, &traceback);
        // Caller owns results.
        Py_DECREF(type);
        Py_DECREF(traceback);
        return (py::steal(value));
    }


}

namespace py {

    void Error::translate ()
    {
        TRANSLATE(ArithmeticError);
        TRANSLATE(AssertionError);
        TRANSLATE(AttributeError);
        TRANSLATE(BufferError);
        TRANSLATE(EnvironmentError);
        TRANSLATE(EOFError);
        TRANSLATE(FloatingPointError);
        TRANSLATE(GeneratorExit);
        TRANSLATE(ImportError);
        TRANSLATE(IndexError);
        TRANSLATE(IndentationError);
        TRANSLATE(IOError);
        TRANSLATE(KeyError);
        TRANSLATE(KeyboardInterrupt);
        TRANSLATE(MemoryError);
        TRANSLATE(NameError);
        TRANSLATE(NotImplementedError);
        TRANSLATE(LookupError);
        TRANSLATE(OSError);
        TRANSLATE(OverflowError);
        TRANSLATE(ReferenceError);
        TRANSLATE(RuntimeError);
        TRANSLATE(StopIteration);
        TRANSLATE(SyntaxError);
        TRANSLATE(SystemError);
        TRANSLATE(SystemExit);
        TRANSLATE(TabError);
        TRANSLATE(TypeError);
        TRANSLATE(UnboundLocalError);
        TRANSLATE(UnicodeError);
        TRANSLATE(UnicodeEncodeError);
        TRANSLATE(UnicodeDecodeError);
        TRANSLATE(UnicodeTranslateError);
        TRANSLATE(ValueError);
        //TRANSLATE(VMSError);
        TRANSLATE(WindowsError);
        TRANSLATE(ZeroDivisionError);
        TRANSLATE(StandardError);
    }

    Error::Error ()
    {
    }

    SystemError::SystemError ()
        : myMessage(::content())
    {
    }

    const Bytes& SystemError::message () const
    {
        return (myMessage);
    }

}
