// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "None.hpp"

namespace py {

    None::None ()
        : myHandle(share(Py_None))
    {
    }

    const Handle& None::handle () const
    {
        return (myHandle);
    }

    None::operator Any () const
    {
        return (Any(myHandle));
    }

}
