
/**
 * @file referable-vector.h
 * @brief the vector structure which could be referred to
 *
 * This file defines a class with vector-like structure which could be
 * referred to. This is the base class for varVector and fixVector classes.
 * This class is used to differentiate with refVector.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Referable_Vector_H_
#define _Referable_Vector_H_

#include "refer-table.h"
#include "vector-base.h"

namespace std {

  /**
   * @brief the vector structure which could be referred to
   *
   * This is a child of VectorBase class. Considering the feature
   * that this kind of object could be referred to, a refer() method
   * is defined to provide common interface.
   *
   * \a T
   *    The type of data in this kind of vector.
   */
  template <typename T>
  class referableVector : public VectorBase<T> {

    public:

      /**
       * @brief the flag indicating if this object could be referred to
       *
       * This flag is used to judge the feature of an object. It would be
       * common feature of all child classes.
       */
      static const uint IsReferable;

      /**
       * @brief the alias for vector which could be referred to
       */
      typedef referableVector<T>      Type;
      /**
       * @brief the alias for the parent VectorBase class
       */
      typedef VectorBase<T>           ParentType;

      /**
       * @brief the table storing the reference information
       */
      ReferTable<T> rTable;

      /**
       * @brief default initiator
       *
       * Just initiate the parent class and the table with null parameter
       */
      referableVector() : ParentType(), rTable() {}

      /**
       * @brief initiate from another referableVector object
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] v
       *        The input referableVector object
       */
      referableVector(const Type& v) { myError("vector copier is disabled!"); }

      /**
       * @brief destructor
       *
       * It is implemented with the clear() method.
       */
      ~referableVector() { clear(); }

      /**
       * @brief clear the internal data
       *
       * It is implemented with the clear() method of the parent class. The table to record the reference
       * information is also cleared.
       */
      void clear() {
        static_cast<ParentType*>(this)->clear();
        rTable.clear();
      }

      /**
       * @brief copier from another referableVector object
       *
       * It is implemented the copier of the parent class.
       *
       * @param [in] v
       *        The input referableVector object
       *
       * @return the reference to the present object
       */
      Type& operator=(const Type& v) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(v));
        return *this;
      }

  };

  /**
   * @brief the flag indicating that this object could be referred to
   *
   * This flag is set as one to indicate that the vector could be referred to.
   *
   * \a T
   *    The type of data in the vector
   */
  template <typename T>
  const uint referableVector<T>::IsReferable=1;

}

#endif

