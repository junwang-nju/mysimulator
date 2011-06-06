
#ifndef _Vector_Cross_Product_H_
#define _Vector_Cross_Product_H_

#include "vector/interface.h"

namespace mysimulator {

  void cross(Vector<long double>& v,
             const Vector<long double>& va, const Vector<long double>& vb,
             const unsigned int off=uZero, const unsigned int step=uOne,
             const unsigned int aoff=uZero,const unsigned int astep=uOne,
             const unsigned int boff=uZero,const unsigned int bstep=uOne) {
    assert(off+step+step<v.size);
    assert(aoff+astep+astep<va.size);
    assert(boff+bstep+bstep<vb.size);
    long double *p0=v()+off,*p1=p0+step,*p2=p1+step;
    long double *ap0=const_cast<long double*>(va())+aoff;
    long double *ap1=ap0+astep,*ap2=ap1+astep;
    long double *bp0=const_cast<long double*>(vb())+boff;
    long double *bp1=bp0+bstep,*bp2=bp1+bstep;
    (*p0)=(*ap1)*(*bp2)-(*ap2)*(*bp1);
    (*p1)=(*ap2)*(*bp0)-(*ap0)*(*bp2);
    (*p2)=(*ap0)*(*bp1)-(*ap1)*(*bp0);
  }

  void cross(Vector<double>& v,
             const Vector<double>& va, const Vector<double>& vb,
             const unsigned int off=uZero, const unsigned int step=uOne,
             const unsigned int aoff=uZero,const unsigned int astep=uOne,
             const unsigned int boff=uZero,const unsigned int bstep=uOne) {
    assert(off+step+step<v.size);
    assert(aoff+astep+astep<va.size);
    assert(boff+bstep+bstep<vb.size);
    double *p0=v()+off,*p1=p0+step,*p2=p1+step;
    double *ap0=const_cast<double*>(va())+aoff,*ap1=ap0+astep,*ap2=ap1+astep;
    double *bp0=const_cast<double*>(vb())+boff,*bp1=bp0+bstep,*bp2=bp1+bstep;
    (*p0)=(*ap1)*(*bp2)-(*ap2)*(*bp1);
    (*p1)=(*ap2)*(*bp0)-(*ap0)*(*bp2);
    (*p2)=(*ap0)*(*bp1)-(*ap1)*(*bp0);
  }

  void cross(Vector<float>& v,
             const Vector<float>& va, const Vector<float>& vb,
             const unsigned int off=uZero, const unsigned int step=uOne,
             const unsigned int aoff=uZero,const unsigned int astep=uOne,
             const unsigned int boff=uZero,const unsigned int bstep=uOne) {
    assert(off+step+step<v.size);
    assert(aoff+astep+astep<va.size);
    assert(boff+bstep+bstep<vb.size);
    float *p0=v()+off,*p1=p0+step,*p2=p1+step;
    float *ap0=const_cast<float*>(va())+aoff,*ap1=ap0+astep,*ap2=ap1+astep;
    float *bp0=const_cast<float*>(vb())+boff,*bp1=bp0+bstep,*bp2=bp1+bstep;
    (*p0)=(*ap1)*(*bp2)-(*ap2)*(*bp1);
    (*p1)=(*ap2)*(*bp0)-(*ap0)*(*bp2);
    (*p2)=(*ap0)*(*bp1)-(*ap1)*(*bp0);
  }

}

#endif

