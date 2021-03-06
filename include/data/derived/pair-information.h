
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
    PairStorage(const Type& P) { Error("Cannot create Pair Storage"); }
    Type& operator=(const Type& P) {
      Error("Cannot copy Pair Storage");
      return *this;
    }
    ~PairStorage() { release(*this); }

    void refresh() { ++(*(gstatus)); }
    void refresh(const unsigned int I) {
      unsigned int n=this->property[MatrixDimension];
      for(unsigned int i=0;i<n;++i) {
        if(i==I)  return;
        this->operator()(i,I).status=status()-1;
      }
    }
    void refreshItem(const unsigned int I, const unsigned int J) {
      this->operator()(I,J).status=*(gstatus)-1;
    }
    void updateItem(const unsigned int I, const unsigned int J, const T& C) {
      PairItem<T> &rI=this->operator()(I,J);
      rI()=C;
      rI.status=*gstatus;
    }
    unsigned int& status() { return *gstatus; }
    const unsigned int& status() const { return *gstatus; }

  };

  template <typename T>
  bool IsAvailable(const PairStorage<T>& P) {
    return IsAvailable(static_cast<const Matrix<PairItem<T> >&>(P));
  }

  template <typename T>
  bool IsUptodate(const PairStorage<T>& P,
                  const unsigned int I, const unsigned int J) {
    return P(I,J).status==P.status();
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
    copy(static_cast<Matrix<PairItem<T> >&>(P),
         static_cast<const Matrix<PairItem<T> >&>(cP));
  }

  template <typename T>
  void ecopy(PairStorage<T>& P, const PairStorage<T>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    assert(P.property[MatrixDimension]==cP.property[MatrixDimension]);
    *(P.gstatus)=*(cP.gstatus);
    long n=sizeof(PairItem<T>)/sizeof(float);
    n*=cP.property[MatrixNumberElement];
    scopy_(&n,reinterpret_cast<float*>(const_cast<PairItem<double>*>(cP.data)),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(P.data),
           const_cast<long*>(&lOne));
  }

  template <typename T>
  void allocate(PairStorage<T>& P, const unsigned int nunit) {
    release(P);
    P.gstatus=new unsigned int;
    *(P.gstatus)=1;
    allocate(static_cast<Matrix<PairItem<T> >&>(P),
             TriangleMatrix,nunit,COrder,NoTranspose,UpperTriangle,true,false);
  }

  template <typename T>
  void allocate(PairStorage<T>& P, const int nunit) {
    allocate(P,static_cast<unsigned int>(nunit));
  }

  template <typename T>
  void refer(PairStorage<T>& P, const PairStorage<T>& rP) {
    assert(IsAvailable(rP));
    release(P);
    P.gstatus=rP.gstatus;
    refer(static_cast<Matrix<PairItem<T> >&>(P),
          static_cast<const Matrix<PairItem<T> >&>(rP));
  }

}

#endif
