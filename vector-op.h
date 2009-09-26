
#ifndef _Vector_Operation_H_
#define _Vector_Operation_H_

#include "var-vector.h"
#include "fix-vector.h"

namespace std {

  double dot(const double* va, const double* vb, long ndot,
             int aoffset=iZero, long astep=lOne,
             int boffset=iZero, long bstep=lOne) {
    return ddot_(&ndot,const_cast<double*>(va)+aoffset,&astep,
                       const_cast<double*>(vb)+boffset,&bstep);
  }

  template <typename vTypeA, typename vTypeB>
  double dot(const vTypeA& va, const vTypeB& vb, long ndot,
             int aoffset=iZero, long astep=lOne,
             int boffset=iZero, long bstep=lOne) {
    assert(isVector<vTypeA>()&&isVector<vTypeB>());
    assert(static_cast<uint>(aoffset+astep*ndot)<=va.size());
    assert(static_cast<uint>(boffset+bstep*ndot)<=vb.size());
    return dot(va.data(),vb.data(),ndot,aoffset,astep,boffset,bstep);
  }

  template <typename vTypeA, typename vTypeB>
  double dot(const vTypeA& va, const vTypeB& vb) {
    assert(isVector<vTypeA>()&&isVector<vTypeB>());
    long n=(va.size()<vb.size()?va.size():vb.size());
    return dot(va,vb,n);
  }

  template <typename vType>
  double normSQ(const vType& v) { assert(isVector<vType>()); return dot(v,v); }

  double norm(const double* v, long nnorm, int offset=iZero, long step=lOne) {
    return dnrm2_(&nnorm,const_cast<double*>(v)+offset,&step);
  }

  template <typename vType>
  double norm(const vType& v, long nnorm, int offset=iZero, long step=lOne) {
    assert(isVector<vType>());
    assert(static_cast<uint>(offset+step*nnorm)<=v.size());
    return norm(v.data(),nnorm,offset,step);
  }

  template <typename vType>
  double norm(const vType& v) {
    assert(isVector<vType>());
    long n=v.size();
    return norm(v,n);
  }

  double sumABS(const double* v, long nsum, int offset=iZero, long step=lOne) {
    return dasum_(&nsum,const_cast<double*>(v)+offset,&step);
  }

  template <typename vType>
  double sumABS(const vType& v, long nsum, int offset=iZero, long step=lOne) {
    assert(isVector<vType>());
    assert(static_cast<uint>(offset+step*nsum)<=v.size());
    return sumABS(v.data(),nsum,offset,step);
  }

  template <typename vType>
  double sumABS(const vType& v) {
    assert(isVector<vType>());
    long n=v.size();
    return sumABS(v,n);
  }

  void cross_prod(const double* va, const double* vb, double* v,
                  int aoffset=iZero, long astep=lOne,
                  int boffset=iZero, long bstep=lOne,
                  int offset=iZero, long step=lOne) {
    double *p=v+offset;
    double *pa=const_cast<double*>(va)+aoffset;
    double *pb=const_cast<double*>(vb)+boffset;
    p[0]        =pa[astep]      *pb[bstep+bstep]
                -pa[astep+astep]*pb[step];
    p[step]     =pa[astep+astep]*pb[0]
                -pa[0]          *pb[bstep+bstep];
    p[step+step]=pa[0]          *pb[bstep]
                -pa[astep]      *pb[0];
  }

  template <typename vTypeA, typename vTypeB, typename vType>
  vType& cross_prod(const vTypeA& va, const vTypeB& vb, vType& v,
                    int aoffset=iZero, long astep=lOne,
                    int boffset=iZero, long bstep=lOne,
                    int offset=iZero, long step=lOne) {
    assert(isVector<vTypeA>()&&isVector<vTypeB>()&&isVector<vType>());
    assert(static_cast<uint>(aoffset+astep*3)<=va.size());
    assert(static_cast<uint>(boffset+bstep*3)<=vb.size());
    assert(static_cast<uint>(offset+step*3)<=v.size());
    cross_prod(va.data(),vb.data(),v.data(),
               aoffset,astep,boffset,bstep,offset,step);
    return v;
  }

}

#endif

