#ifndef _py_Iterator_hpp__
#define _py_Iterator_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file pyxx/Iterator.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Iterator interface.
 */

#include "Any.hpp"
#include <python.h>

namespace py {

    class Tuple;
    class List;

      /*!
       * @brief Python iterator interface.
       *
       * Python iterators should be used in a @c while loop.  To iterate over
       * a sequence of byte strings, use the following idiom:
       *
       * @code
       *  Iterator iterator = ...;
       *  while (iterator.next())
       *  {
       *     const Bytes item(iterator.item());
       *     // process string...
       *  }
       * @endcode
       */
    class Iterator :
        public Object
    {
    friend class Any;

        /* class methods. */
    public:
        static bool is_a ( const Handle& handle );

        /* data. */
    private:
        Any myItem;

        /* construction. */
    private:
          /*!
           * @brief Cast an existing object to an iterator instance.
           * @param handle Handle to an iterator instance.
           */
        explicit Iterator ( const Handle& handle );

    public:
          /*!
           * @brief Empty iterator.  Must be assigned to before use.
           */
        Iterator ();

          /*!
           * @brief Cast an existing object to an iterator instance.
           * @param iterator Object wrapping an iterator instance.
           */
        explicit Iterator ( const Any& iterator );

          /*!
           * @brief Get an iterator to process @a iterable.
           */
        Iterator ( const List& iterable );

          /*!
           * @brief Get an iterator to process @a iterable.
           */
        Iterator ( const Tuple& iterable );

        /* methods. */
    public:
          /*!
           * @brief Advance to the next item in the sequence.
           * @return @c true if @c item() can be called safely, @c false if we
           *  reached the end of the sequence.
           */
        bool next ();

          /*!
           * @brief Fetch the item at the current position in the sequence.
           * @return The current item.
           *
           * @pre The last call @c next() returned @c true.
           *
           * It is safe to call this method multiple times.  It will repeatedly
           * return the same object until @c next() is called again.
           */
        Any item () const;
    };

}

#endif /* _py_Iterator_hpp__ */
