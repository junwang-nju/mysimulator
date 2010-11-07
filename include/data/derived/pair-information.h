
#ifndef _Pair_Information_H_
#define _Pair_Information_H_

#include "data/derived/pair-information-item.h"
#include "data/basic/matrix.h"

namespace std {

  template <typename T>
  struct PairStorage : public Matrix<PairItem<T> > {
    typedef PairStorage<T>  Type;
    typedef Matrix<PairItem<T> >  ParentType;
    
    unsigned int *gstatus;

    PairStorage() : ParentType(), gstatus(NULL) {}
    PairStorage(const Type& P) { myError("Cannot create Pair Storage"); }
    Type& operator=(const Type& P) {
      myError("Cannot copy Pair Storage");
      return *this;
    }
    ~PairStorage() { release(*this); }

  };

  template <typename T>
  bool IsAvailable(const PairStorage<T>& P) {
    return IsAvailable(static_cast<const Matrix<PairItem<T> >&>(P));
  }

  template <typename T>
  void release(PairStorage<T>& P) {
    if(P.state==Allocated)  safe_delete(P.gstatus);
    else P.gstatus=NULL;
    release(static_cast<Matrix<PairItem<T> >&>(P));
  }

  template <typename T>
  void copy(PairStorage<T>& P, const PairStorage<T>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    *(P.gstatus)=*(cP.gstatus);
    copy(static_cast<Matrix<PairItem<T> >&>(P),,
         static_cast<const Matrix<PairItem<T> >&>(cP));
  }

  template <typename T>
  void allocate(PairStorage<T>& P, const unsigned int nunit) {
    release(P);
    P.gstatus=new unsigned int;
    *(p.gstatus)=1;
    allocate(static_cast<Matrix<PairItem<T> >&>(P),
             TriangleMatrix,nunit,COrder,NoTranspose,UpperTriangle,true,false);
    for(unsigned int i=0;i<P.property[MatrixNumberElement];++i)
      allocate(*(P.data+i));
    allocate(*(P.ptrOther));
  }

}

#endif
