
#ifndef _Referable_Vector_H_
#define _Referable_Vector_H_

#include "refer-table.h"
#include "vector-base.h"

namespace std {

  template <typename T>
  class referableVector : public VectorBase<T> {

    public:

      static const uint IsReferable;

      typedef referableVector<T>      Type;
      typedef VectorBase<T>           ParentType;

      ReferTable<T> rTable;

      referableVector() : ParentType(), rTable() {}

      referableVector(const Type& v) { myError("vector copier is disabled!"); }

      ~referableVector() { clear(); }

      void clear() {
        static_cast<ParentType*>(this)->clear();
        rTable.clear();
      }

      Type& operator=(const Type& v) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(v));
        return *this;
      }

  };

  template <typename T>
  const uint referableVector<T>::IsReferable=1;

}

#endif

