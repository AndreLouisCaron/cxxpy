#ifndef _py_Interpreter_hpp__
#define _py_Interpreter_hpp__

#include <python.h>
#include "Object.hpp"

namespace py {

    class Interpreter :
        public Object
    {
        /* construction. */
    public:
        Interpreter ();
    };

}

#endif /* _py_Interpreter_hpp__ */
