
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
    allocate(static_cast<Vector<Vector<T> >&>(V),n);
    for(unsigned int i=0;i<n;++i)
      if(sz[i]>0) allocate(V[i],sz[i]);
  }

  template <typename T>
  void allocate(DualVector<T>& V, const Vector<unsigned int>& sz) {
    allocate(V,sz.data,sz.size);
  }

  template <typename T>
  void imprint(Vector<Vector<T> >& V, const Vector<Vector<T> >& cV) {
    assert(IsAvailable(cV));
    allocate(V,cV.size);
    for(unsigned int i=0;i<V.size;++i)
      if(cV[i].size>0)  allocate(V[i],cV[i].size);
  }

}

#endif
