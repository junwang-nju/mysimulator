
/**
 * @file refer-table.h
 * @brief The data structure storing reference relationship
 *
 * To record the reference and referred objects, a specific object is
 * initiated to record these information. This object is used in
 * the classes related to reference. To avoid variation of the size
 * of the list, we assume the maximal size of reference objects in
 * reference table. This kind of implementation is not couple with STL,
 * which makes it more compatible for various compilers.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Reference_Table_H_
#define _Reference_Table_H_

#include "type.h"
#include "memory.h"
#include "error-proc.h"

namespace std {

  /**
   * @brief declaration of refer vector
   *
   * This is just a declaration before ReferTable<T>.
   */
  template <typename T>   class refVector;

  /**
   * @brief the reference table
   *
   * This class is used to store the information about related refVector
   * objects. The pointers of related refVector objects are stored in the
   * array. The array has the maximal capacity. This object would be used
   * in referable classes.
   *
   * \a T
   *    The type of data related to reference table.
   */
  template <typename T>
  class ReferTable {

    public:

      /**
       * @brief the maximal capacity of the table
       */
      static const uint MaxRefInstance;

      /**
       * @brief the count for the available refVector objects in table
       */
      uint refcount;

      /**
       * @brief internal table recording refVector information
       *
       * This is an array to the pointers of refVector objects
       */
      refVector<T>** refinst;

      /**
       * @brief default initiator
       *
       * Set the count as zero. The internal table is allocated with
       * the maximal number.
       */
      ReferTable() : refcount(0) { refinst=new refVector<T>*[MaxRefInstance]; }

      /**
       * @brief destructor
       *
       * Just clear the data with clear() method, and delete the internal
       * table.
       */
      ~ReferTable() { clear(); safe_delete(refinst); }

      /**
       * @brief copier from another reference table
       *
       * This is prohibited by popping up an error.
       *
       * @param [in] rt
       *        The input reference table.
       *
       * @return the reference to the present object.
       */
      ReferTable<T>& operator=(const ReferTable<T>& rt) {
        myError("copier for ReferTable is prohibited!");
        return *this;
      }

      /**
       * @brief clear the table
       *
       * Clear the elements of reference table one by one, and nullify
       * the count.
       */
      void clear() {
        uint n=refcount;
        for(uint i=0;i<n;++i) refinst[i]->clear();
        refcount=0;
      }

      /**
       * @brief the number of the available references in table
       *
       * Just gives out the internal count.
       *
       * @return the internal count for the table
       */
      const uint& count() const { return refcount; }

      /**
       * @brief increase the internal count
       *
       * Just add one to the count.
       */
      void inc() { ++refcount; }

      /**
       * @brief decrease the internal count
       *
       * Just minus one from the count
       */
      void dec() { --refcount; }

      /**
       * @brief swap with another reference table
       *
       * Just swap all the internal variables to realize the swap of 
       * storage.
       *
       * @param [in,out] rTable
       *        The reference table to be swapped
       *
       * @return the reference to the present object.
       */
      ReferTable<T>& swap(ReferTable<T>& rTable) {
        uint n;
        n=refcount; refcount=rTable.refcount; rTable.refcount=n;
        refVector<T>** p;
        p=refinst;  refinst=rTable.refinst;   rTable.refinst=p;
        return *this;
      }

  };

  /**
   * @brief the maximal number of reference instance in table.
   *
   * This number is set as 50. The maximum size of the table controls
   * the available capacity. This avoids the unlimited growth of the
   * table.
   *
   * \a T
   *    The type of data related to reference table.
   */
  template <typename T>
  const uint ReferTable<T>::MaxRefInstance=50;

  /**
   * @brief swap two reference tables
   *
   * It is implemented with the ReferTable<T>::swap() method. This method
   * makes the interface unique.
   *
   * \a T
   *    The type of data related to reference table.
   *
   * @param [in,out] rt1
   *        One reference table to be swapped.
   *
   * @param [in,out] rt2
   *        Another reference table to be swapped.
   */
  template <typename T>
  void swap(ReferTable<T>& rt1, ReferTable<T>& rt2) { rt1.swap(rt2); }

}

#endif

