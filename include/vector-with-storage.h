
#ifndef _Vector_With_Storage_H_
#define _Vector_With_Storage_H_

#include "vector-base.h"
#include "pool.h"

namespace std {
  template <typename T>
  class VectorWStorage : public VectorBase<T> {
    protected:
      Pool<void*> rObjSet;
    public:
      static const unsigned int MaxRefObj;
      typedef VectorWStorage<T>   Type;
      typedef VectorBase<T> ParentType;
      VectorWStorage() : ParentType(), rObjSet() {
        rObjSet.allocate(MaxRefObj);
      }
      VectorWStorage(const Type& RV) {
        myError("Cannot create from vector with storage");
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
      ~VectorWStorage() { rObjSet.clear(); }
      void clear();
      Pool<void*>& RefList();
      const Pool<void*>& RefList() const;
      void swap(Type& RV);
  };
  template <typename T>
  const unsigned int VectorWStorage<T>::MaxRefObj=20;
}

#endif

