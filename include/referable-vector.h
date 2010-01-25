
#ifndef _Referable_Vector_H_
#define _Referable_Vector_H_

#include "vector-base.h"
#include "pool.h"

namespace std {
  template <typename T>
  class referableVector : public VectorBase<T> {
    protected:
      Pool<void*> rObjSet;
    public:
      static const bool IsReferable;
      static const unsigned int MaxRefObj;
      typedef referableVector<T>  Type;
      typedef VectorBase<T> ParentType;
      referableVector() : ParentType(), rObjSet() {
        rObjSet.allocate(MaxRefObj);
      }
      referableVector(const Type& RV) {
        myError("Cannot create from referable vector");
      }
      Type& operator=(const Type& RV) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(RV));
        return *this;
      }
      template <typename inputT>
      Type& operator=(const inputT& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }
      ~referableVector() { rObjSet.clear(); }
      void clear();
      Pool<void*>& RefList();
      const Pool<void*>& RefList() const;
      void swap(Type& RV);
  };
  template <typename T>
  const bool referableVector<T>::IsReferable=true;
  template <typename T>
  const unsigned int referableVector<T>::MaxRefObj=20;
}

#endif

