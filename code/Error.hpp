#ifndef _py_Error_hpp__
#define _py_Error_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <python.h>
#include "Object.hpp"
#include "Bytes.hpp"

namespace py {

      /*!
       * @brief Base class for exceptions.
       */
    class Error
    {
        /* class methods. */
    public:
        static void translate ();

        /* construction. */
    protected:
        Error ();
    };

    class ArithmeticError : public Error {};
    class AssertionError : public Error {};
    class AttributeError : public Error {};
    class BufferError : public Error {};
    class EnvironmentError : public Error {};
    class EOFError : public Error {};
    class FloatingPointError : public Error {};
    class GeneratorExit : public Error {};
    class ImportError : public Error {};
    class IndexError : public Error {};
    class IndentationError : public Error {};
    class IOError : public Error {};
    class KeyError : public Error {};
    class KeyboardInterrupt : public Error {};
    class MemoryError : public Error {};
    class NameError : public Error {};
    class NotImplementedError : public Error {};
    class LookupError : public Error {};
    class OSError : public Error {};
    class OverflowError : public Error {};
    class ReferenceError : public Error {};
    class RuntimeError : public Error {};
    class StandardError : public Error {};
    class StopIteration : public Error {};
    class SyntaxError : public Error {};
    class SystemError : public Error
    {
        /* data. */
    private:
        const py::Bytes myMessage;

        /* construction. */
    public:
        SystemError ();

        /* methods. */
    public:
        const py::Bytes& message () const;
    };
    class SystemExit : public Error {};
    class TabError : public Error {};
    class TypeError : public Error {};
    class UnboundLocalError : public Error {};
    class UnicodeError : public Error {};
    class UnicodeEncodeError : public Error {};
    class UnicodeDecodeError : public Error {};
    class UnicodeTranslateError : public Error {};
    class ValueError : public Error {};
    class VMSError : public Error {};
    class WindowsError : public Error {};
    class ZeroDivisionError : public Error {};

}

#endif /* _py_Error_hpp__ */
