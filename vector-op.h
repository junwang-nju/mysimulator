
/**
 * @file vector-op.h
 * @brief Operations for vectors
 *
 * This file contains a series of operations for vectors (mainly with
 * \c double type data). This is similar as the file vector-impl.h to
 * provide interfaces between background library and classes in our
 * package.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Vector_Operation_H_
#define _Vector_Operation_H_

#include "var-vector.h"
#include "fix-vector.h"
#include <iostream>

namespace std {

  double dot(const double* va, const double* vb, long ndot,
             int aoffset=iZero, long astep=lOne,
             int boffset=iZero, long bstep=lOne) {
    return ddot_(&ndot,const_cast<double*>(va)+aoffset,&astep,
                       const_cast<double*>(vb)+boffset,&bstep);
  }

  double dot(const VectorBase<double>& va, const VectorBase<double>& vb,
             long ndot,
             int aoffset=iZero, long astep=lOne,
             int boffset=iZero, long bstep=lOne) {
    assert(static_cast<uint>(aoffset+astep*ndot)<=va.size());
    assert(static_cast<uint>(boffset+bstep*ndot)<=vb.size());
    return dot(va.data(),vb.data(),ndot,aoffset,astep,boffset,bstep);
  }

  double dot(const VectorBase<double>& va, const VectorBase<double>& vb) {
    long n=(va.size()<vb.size()?va.size():vb.size());
    return dot(va,vb,n);
  }

  double normSQ(const VectorBase<double>& v) { return dot(v,v); }

  double norm(const double* v, long nnorm, int offset=iZero, long step=lOne) {
    return dnrm2_(&nnorm,const_cast<double*>(v)+offset,&step);
  }

  double norm(const VectorBase<double>& v, long nnorm,
              int offset=iZero, long step=lOne) {
    assert(static_cast<uint>(offset+step*nnorm)<=v.size());
    return norm(v.data(),nnorm,offset,step);
  }

  double norm(const VectorBase<double>& v) { return norm(v,v.size()); }

  double sumABS(const double* v, long nsum, int offset=iZero, long step=lOne) {
    return dasum_(&nsum,const_cast<double*>(v)+offset,&step);
  }

  double sumABS(const VectorBase<double>& v, long nsum,
                int offset=iZero, long step=lOne) {
    assert(static_cast<uint>(offset+step*nsum)<=v.size());
    return sumABS(v.data(),nsum,offset,step);
  }

  double sumABS(const VectorBase<double>& v) { return sumABS(v,v.size()); }

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

  void cross_prod(const VectorBase<double>& va,
                  const VectorBase<double>& vb,
                  VectorBase<double>& v,
                  int aoffset=iZero, long astep=lOne,
                  int boffset=iZero, long bstep=lOne,
                  int offset=iZero, long step=lOne) {
    assert(static_cast<uint>(aoffset+astep*3)<=va.size());
    assert(static_cast<uint>(boffset+bstep*3)<=vb.size());
    assert(static_cast<uint>(offset+step*3)<=v.size());
    cross_prod(va.data(),vb.data(),v.data(),
               aoffset,astep,boffset,bstep,offset,step);
  }

}

#endif

