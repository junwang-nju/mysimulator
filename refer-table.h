
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

  template <typename T>
  class ReferTable {

    public:

      static const uint MaxRefInstance;

      uint refcount;

      refVector<T>** refinst;

      ReferTable() : refcount(0) { refinst=new refVector<T>*[MaxRefInstance]; }

      ~ReferTable() { clear(); safe_delete(refinst); }

      ReferTable<T>& operator=(const ReferTable<T>& rt) {
        myError("copier for ReferTable is prohibited!");
        return *this;
      }

      void clear() {
        uint n=refcount;
        for(uint i=0;i<n;++i) refinst[i]->clear();
        refcount=0;
      }

      const uint& count() const { return refcount; }

      void inc() { ++refcount; }

      void dec() { --refcount; }

      ReferTable<T>& swap(ReferTable<T>& rTable) {
        uint n;
        n=refcount; refcount=rTable.refcount; rTable.refcount=n;
        refVector<T>** p;
        p=refinst;  refinst=rTable.refinst;   rTable.refinst=p;
        return *this;
      }

  };

  template <typename T>
  const uint ReferTable<T>::MaxRefInstance=50;

  template <typename T>
  void swap(ReferTable<T>& rt1, ReferTable<T>& rt2) { rt1.swap(rt2); }

}

#endif

