// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2012
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Lock.hpp"

namespace py {

    Leave::Leave ()
        : myState(::PyEval_SaveThread())
    {
    }

    Leave::~Leave ()
    {
        ::PyEval_RestoreThread(myState);
    }

    Enter::Enter ()
        : myState(::PyGILState_Ensure())
    {
    }

    Enter::~Enter ()
    {
        ::PyGILState_Release(myState);
    }

}
