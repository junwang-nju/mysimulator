
#ifndef _Dual_Vector_H_
#define _Dual_Vector_H_

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  struct DualVector : public Vector<Vector<T> > {
    typedef DualVector<T>   Type;
    typedef Vector<Vector<T> >  ParentType;
    
    DualVector() : ParentType() {}
    DualVector(const Type& V) { myError("Cannot create dual-vector"); }
    Type& operator=(const Type& V) {
      myError("Cannot copy dual-vector");
      return *this;
    }
    ~DualVector() { release(*this); }
  };

  template <typename T>
  void allocate(DualVector<T>& V, const unsigned int* sz, const unsigned int n){
    allocate(V,n);
    for(unsigned int i=0;i<n;++i)
      if(sz[i]>0) allocate(V[i],sz[i]);
  }

  template <typename T>
  void allocate(DualVector<T>& V, const Vector<unsigned int>& sz) {
    allocate(V,sz.data,sz.size);
  }
}

#endif
