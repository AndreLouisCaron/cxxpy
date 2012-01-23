=====================================================
  `cxxpy`: Simple API for consuming Python from C++
=====================================================
:authors:
   André Caron
:contact: andre.l.caron@gmail.com

Description
===========

This library provides a simple API for consuming Python_ code bases from C++.
The intent of this library is to be a small, lightweight wrapper on the
`Python C API`_, easing the embedding of Python into C++ applications.

Differences with `Boost.Python`_
--------------------------------

If Boost_ is so great, why not use `Boost.Python`_?  Well, Boost_ is a huge
library which is not installed by default on many systems (most notably
Microsoft Windows) and it takes a short eternity to compile programs that use
it.  Moreover, `Boost.Python`_ is mostly designed for exporting C++ classes to
use them from Python_ with embedding added on as an afterthought.

This library is by no means intended as a replacement, or even a substitute of
`Boost.Python`.  If you want to write Python_ bindings for your C++ classes,
please use `Boost.Python`_ (or SWIG_).  If you just want a quick way to consume
Python_ software libraries from C++ without heavy dependencies, then use this
library.

.. _Python: http://www.python.org
.. _`Python C API`: http://docs.python.org/c-api/
.. _`Boost.Python`: http://wiki.python.org/moin/boost.python/GettingStarted
.. _Boost: http://www.boost.org/
.. _SWIG: http://www.swig.org/

Requirements
============

#. CPython.  Only works with the reference implementation, not Jython_,
   IronPython_ or other variants which don't have an interface for C.  Make sure
   to install a version that is compatible with your C++ compiler toolchain.  If
   you don't have a 64-bit compiler, you can't use 64-bit Python.
#. A C++ compiler toolchain:

   * Microsoft Visual Studio (for Microsoft Windows).  The code base has not
     been tested on versions prior to 2008.  Should work on both the Express
     and Professional versions.
   * GCC (for UNIX-like systems)

#. CMake_
#. Git_ (unless you download the sources as an archive)
#. Doxygen_ (to build the API documentation)

.. _Jython: http://www.jython.org/
.. _IronPython: http://ironpython.net/
.. _CMake: http://www.cmake.org/
.. _Git: http://git-scm.com/
.. _Doxygen: http://www.stack.nl/~dimitri/doxygen/

Compiling
=========

#. Open up a terminal (command prompt).
#. Get the source code.

   ::

      git clone git://github.com/AndreLouisCaron:cxxpy.git
      cd cxxpy

#. Have CMake_ generate build scripts.

   ::

      mkdir work
      cd work
      cmake -G "NMake Makefiles" ..

#. Build using your favorite toolchain.

   ::

      nmake

#. Enjoy!
