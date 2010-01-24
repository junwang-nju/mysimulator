
#include "vector-op.h"
#include "vector-impl.h"
#include <cassert>

namespace std {

  double dot(const VectorBase<double>& va, const VectorBase<double>& vb) {
    long n=(va.size()<vb.size()?va.size():vb.size());
    return dot(va,vb,n);
  }

  double dot(const VectorBase<double>& va,const VectorBase<double>& vb,
             long ndot, int aoff, long astep, int boff, long bstep) {
    assert(static_cast<unsigned int>(aoff+astep*ndot)<=va.size());
    assert(static_cast<unsigned int>(boff+bstep*ndot)<=vb.size());
    return vector_dot(va.data(),vb.data(),ndot,aoff,astep,boff,bstep);
  }

  double normSQ(const VectorBase<double>& v) { return dot(v,v); }

  double normSQ(const VectorBase<double>& v, long nnsq, int off, long step) {
    return dot(v,v,nnsq,off,step,off,step);
  }

  double norm(const VectorBase<double>& v) { return norm(v,v.size()); }

  double norm(const VectorBase<double>& v, long nnm, int off, long step) {
    assert(static_cast<unsigned int>(off+step*nnm)<=v.size());
    return vector_norm(v.data(),nnm,off,step);
  }

  double sumABS(const VectorBase<double>& v) { return sumABS(v,v.size()); }

  double sumABS(const VectorBase<double>& v, long nas, int off, long step) {
    assert(static_cast<unsigned int>(off+step*nas)<=v.size());
    return vector_asum(v.data(),nas,off,step);
  }

  void crossProd(const VectorBase<double>& va, const VectorBase<double>& vb,
                 VectorBase<double>& v, int aoff, long astep, int boff,
                 long bstep, int off, long step) {
    assert(static_cast<unsigned int>(aoff+astep*3)<=va.size());
    assert(static_cast<unsigned int>(boff+bstep*3)<=vb.size());
    assert(static_cast<unsigned int>(off+step*3)<=v.size());
    double *p=v.data()+off;
    double *pa=const_cast<double*>(va.data())+aoff;
    double *pb=const_cast<double*>(vb.data())+boff;
    long dastep=astep+astep, dbstep=bstep+bstep, dstep=step+step;
    p[0]    = pa[astep] *pb[dbstep] -pa[dastep] *pb[bstep];
    p[step] = pa[dastep]*pb[0]      -pa[0]      *pb[dbstep];
    p[dstep]= pa[0]     *pb[bstep]  -pa[astep]  *pb[0];
  }

}