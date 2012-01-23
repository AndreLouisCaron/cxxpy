#include "Interpreter.hpp"

namespace {

#if 0
    ::PyObject * acquire ()
    {
        static ::PyTypeObject type =
        {
            PyVarObject_HEAD_INIT(0, 0)
            "private.Interpreter",
            sizeof(PyObject),
        };
        ::PyObject *const self =
            PyObject_New(PyObject, &type);
        if ( self == 0 )
        {
        }
        return (self);
    }
#endif

}

namespace py {

#if 0
    Interpreter::Interpreter ()
        : Object(::acquire())
    {
    }
#endif

}
