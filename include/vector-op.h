
#ifndef _Vector_Operation_H_
#define _Vector_Operation_H_

#include "constant.h"
#include "blas.h"
#include <cstdlib>

namespace std {

  template <typename T>
  void assign(T* dest, const T* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    T* dPtr=dest+doff, sPtr=const_cast<T*>(src)+soff;
    for(unsigned int i=0;i<ncopy;++i,++dPtr,++sPtr)   *dPtr=*sPtr;
  }

  void assign(double* dest, const double* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    dcopy_(&ncop,const_cast<double*>(src)+soff,&sstep,dest+doff,&dstep);
  }

  void assign(int* dest, const int* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    scopy_(&ncopy,reinterpret_cast<float*>(const_cast<int*>(src))+soff,&sstep,
                  reinterpret_cast<float*>(dest)+doff,&dstep);
  }

  void assign(unsigned int* dest, const unsigned int* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    scopy_(&ncopy,
           reinterpret_cast<float*>(const_cast<unsigned int*>(src))+soff,
           &sstep,reinterpret_cast<float*>(dest)+doff,&dstep);
  }

  template <typename T>
  void assign(T* dest, const T& value, const long ncopy,
              const int doff=iZero, const long dstep=lOne) {
    assign(dest,&value,ncopy,iZero,lZero,doff,dstep);
  }

  void scale(int* dest, const int factor, const long nscale,
             const int doff=iZero, const long dstep=lOne) {
    int* dPtr=dest+doff;
    for(unsigned int i=0;i<nscale;++i,dPtr+=dstep)  *dest*=factor;
  }

  void scale(unsigned int* dest, const unsigned int factor, const long nscale,
             const int doff=iZero, const long dstep=lOne) {
    unsigned int* dPtr=dest+doff;
    for(unsigned int i=0;i<nscale;++i,dPtr+=dstep)  *dest*=factor;
  }

  void scale(double* dest, const double factor, const long nscale,
             const int doff=iZero, const long dstep=lOne) {
    dscal_(&nscale,const_cast<double*>(&factor),dest+doff,&dstep);
  }

  void scale(int* dest, const int* vfactor,const long nscale,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    int* dPtr=dest+doff, vPtr=const_cast<int*>(vfactor)+vstep;
    for(unsigned int i=0;i<nscale;++i,dPtr+=dstep,vPtr+=vstep) *dPtr*=*vPtr;
  }

  void scale(unsigned int* dest, const unsigned int* vfactor,const long nscale,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    unsigned int* dPtr=dest+doff,vPtr=const_cast<unsigned int*>(vfactor)+vstep;
    for(unsigned int i=0;i<nscale;++i,dPtr+=dstep,vPtr+=vstep) *dPtr*=*vPtr;
  }

  void scale(double* dest, const double* vfactor, const long nscale,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,&nscale,&lZero,const_cast<double*>(vfactor)+voff,
           &vstep,dest+dstep,&dstep);
  }

  void shift(int* dest, const int factor, const int* vfactor,const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    int *dPtr=dest+doff, *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<nshift;++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr+=factor*(*vPtr);
  }

  void shift(unsigned int* dest, const unsigned int factor,
             const unsigned int* vfactor, const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    unsigned int *dPtr=dest+doff;
    unsigned int *vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<nshift;++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr+=factor*(*vPtr);
  }

  void shift(double* dest, const double factor, const double* vfactor,
             const long nshift, const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    daxpy_(&nscale,const_cast<double*>(&factor),
           const_cast<double*>(vfactor)+voff,&vstep,dest+doff,&dstep);
  }

  void shift(int* dest, const int* vfactor, const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,iOne,vfactor,nshift,voff,vstep,doff,dstep);
  }

  void shift(unsigned int* dest, const unsigned int* vfactor,const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,uOne,vfactor,nshift,voff,vstep,doff,dstep);
  }

  void shift(double* dest, const double* vfactor, const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,dOne,vfactor,nshift,voff,vstep,doff,dstep);
  }

  void shift(int* dest, const int factor, const long nshift,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,&iOne,nshift,iZero,lZero,doff,dstep);
  }

  void shift(unsigned int* dest, const unsigned int factor, const long nshift,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,&uOne,nshift,iZero,lZero,doff,dstep);
  }

  void shift(double* dest, const double factor, const long nshift,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,&dOne,nshift,iZero,lZero,doff,dstep);
  }

  void shift(int* dest, const int* vfactor, const int factor,
             const long nshift, const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,vfactor,nshift,voff,vstep,doff,dstep);
  }

  void shift(unsigned int* dest, const unsigned int* vfactor,
             const unsigned int factor, const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,vfactor,nshift,voff,vstep,doff,dstep);
  }

  void shift(double* dest, const double* vfactor, const double factor,
             const long nshift, const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,vfactor,nshift,voff,vstep,doff,dstep);
  }

  void scaleshift(int* dest, const int dfactor, const int factor,
                  const int* sfactor, const int* vfactor,
                  const long nscaleshift,
                  const int soff=iZero, const long sstep=lOne,
                  const int voff=iZero, const long vstep=lOne,
                  const int doff=iZero, const long dstep=lOne) {
    int *dPtr=dest+doff;
    int *sPtr=const_cast<int*>(sfactor)+soff;
    int *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<nscaleshift;++i,dPtr+=dstep,sPtr+=sstep,vPtr+=vstep){
      *dPtr*=dfactor;
      *dPtr+=factor*(*sPtr)*(*vPtr);
    }
  }

  void scaleshift(unsigned int* dest, const unsigned int dfactor,
                  const unsigned int factor, const unsigned int* sfactor,
                  const unsigned int* vfactor, const long nscaleshift,
                  const int soff=iZero, const long sstep=lOne,
                  const int voff=iZero, const long vstep=lOne,
                  const int doff=iZero, const long dstep=lOne) {
    unsigned int *dPtr=dest+doff;
    unsigned int *sPtr=const_cast<unsigned int*>(sfactor)+soff;
    unsigned int *vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<nscaleshift;++i,dPtr+=dstep,sPtr+=sstep,vPtr+=vstep){
      *dPtr*=dfactor;
      *dPtr+=factor*(*sPtr)*(*vPtr);
    }
  }

  void scaleshift(double* dest, const double dfactor, const double factor,
                  const double* sfactor, const double* vfactor,
                  const long nscaleshift,
                  const int soff=iZero, const long sstep=lOne,
                  const int voff=iZero, const long vstep=lOne,
                  const int doff=iZero, const long dstep=lOne) {
    static char flag[]="L";
    dsbmv_(flag,&nscaleshift,&lZero,const_cast<double*>(&factor),
           const_cast<double*>(sfactor)+soff,&sstep,
           const_cast<double*>(vfactor)+voff,&vstep,
           const_cast<double*>(&dfactor),dest+doff,&dstep);
  }

  void scaleshift(int* dest, const int dfactor, const int factor,
                  const int* vfactor, const long nscaleshift,
                  const int voff=iZero, const long vstep=lOne,
                  const int doff=iZero, const long dstep=lOne) {
    scale(dest,dfactor,nscaleshift,doff,dstep);
    shift(dest,factor,vfactor,nscaleshift,voff,vstep,doff,dstep);
  }

  void scaleshift(unsigned int* dest, const unsigned int dfactor,
                  const unsigned int factor, const unsigned int* vfactor,
                  const long nscaleshift,
                  const int voff=iZero, const long vstep=lOne,
                  const int doff=iZero, const long dstep=lOne) {
    scale(dest,dfactor,nscaleshift,doff,dstep);
    shift(dest,factor,vfactor,nscaleshift,voff,vstep,doff,dstep);
  }

  void scaleshift(double* dest, const double dfactor, const double factor,
                  const double* vfactor, const long nscaleshift,
                  const int voff=iZero, const long vstep=lOne,
                  const int doff=iZero, const long dstep=lOne) {
    scale(dest,dfactor,nscaleshift,doff,dstep);
    shift(dest,factor,vfactor,nscaleshift,voff,vstep,doff,dstep);
  }

  void shift(int* dest, const int factor, const int* sfactor,
             const int* vfactor, const long nshift,
             const int soff=iZero, const long sstep=lOne,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    scaleshift(dest,iOne,factor,sfactor,vfactor,nshift,soff,sstep,voff,vstep,
               doff,dstep);
  }

  void shift(unsigned int* dest, const unsigned int factor,
             const unsigned int* sfactor, const unsigned int* vfactor,
             const long nshift,
             const int soff=iZero, const long sstep=lOne,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    scaleshift(dest,uOne,factor,sfactor,vfactor,nshift,soff,sstep,voff,vstep,
               doff,dstep);
  }

  void shift(double* dest, const double factor, const double* sfactor,
             const double* vfactor, const long nshift,
             const int soff=iZero, const long sstep=lOne,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    scaleshift(dest,dOne,factor,sfactor,vfactor,nshift,soff,sstep,voff,vstep,
               doff,dstep);
  }

  template <typename T>
  void exchange(T* srcA, T* srcB, const long nexchange,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    T tmT, *aPtr=srcA+aoff, *bPtr=srcB+boff;
    for(unsigned int i=0;i<nexchange;++i,aPtr+=astep,bPtr+=bstep) {
      tmT=*aPtr;  *aPtr=*bPtr;  *bPtr=tmT;
    }
  }

  void exchange(int* srcA, int* srcB, const long nexchange,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    sswap_(&nexchange,reinterpret_cast<float*>(srcA)+aoff,&astep,
                      reinterpret_cast<float*>(srcB)+boff,&bstep);
  }

  void exchange(unsigned int* srcA, unsigned int* srcB, const long nexchange,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    sswap_(&nexchange,reinterpret_cast<float*>(srcA)+aoff,&astep,
                      reinterpret_cast<float*>(srcB)+boff,&bstep);
  }

  void exchange(double* srcA, double* srcB, const long nexchange,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    dswap_(&nexchange,srcA+aoff,&astep,srcB+boff,&bstep);
  }

  int dot(const int* srcA, const int* srcB,const long ndot,
          const int aoff=iZero, const long astep=lOne,
          const int boff=iZero, const long bstep=lOne) {
    int *aPtr=const_cast<int*>(srcA)+aoff, *bPtr=const_cast<int*>(srcB)+boff;
    int s=0;
    for(unsigned int i=0;i<ndot;++i,aPtr+=astep,bPtr+=bstep)
      s+=(*aPtr)*(*bPtr);
    return s;
  }

  unsigned int dot(const unsigned int* srcA, const unsigned int* srcB,
                   const long ndot,
                   const int aoff=iZero, const long astep=lOne,
                   const int boff=iZero, const long bstep=lOne) {
    unsigned int *aPtr=const_cast<int*>(srcA)+aoff;
    unsigned int *bPtr=const_cast<int*>(srcB)+boff;
    unsigned int s=0;
    for(unsigned int i=0;i<ndot;++i,aPtr+=astep,bPtr+=bstep)
      s+=(*aPtr)*(*bPtr);
    return s;
  }

  double dot(const double* srcA, const double* srcB, const long ndot,
             const int aoff=iZero, const long astep=lOne,
             const int boff=iZero, const long bstep=lOne) {
    return ddot_(&ndot,const_cast<double*>(srcA)+aoff,&astep,
                       const_cast<double*>(srcB)+boff,&bstep);
  }

  int normSQ(const int* src, const long nnormsq,
             const int off=iZero, const long step=lOne) {
    return dot(src,src,nnormsq,off,step,off,step);
  }

  unsigned int normSQ(const unsigned int* src, const long nnormsq,
                      const int off=iZero, const long step=lOne) {
    return dot(src,src,nnormsq,off,step,off,step);
  }

  double normSQ(const double* src, const long nnormsq,
                const int off=iZero, const long step=lOne) {
    return dot(src,src,nnormsq,off,step,off,step);
  }

  double norm(const double* src, const long nnorm,
              const int off=iZero, const long step=lOne) {
    return dnrm2_(&nnorm,const_cast<double*>(src)+off,&step)
  }

  int asum(const int* src, const long nasum,
           const int off=iZero, const long step=lOne) {
    int *Ptr=const_cast<int*>(src)+off;
    int s=0;
    for(unsigned int i=0;i<nasum;++i,Ptr+=step) s+=abs(*Ptr);
    return s;
  }

  unsigned int asum(const unsigned int* src, const long nasum,
                    const int off=iZero, const long step=lOne) {
    unsigned int *Ptr=const_ccast<int*>(src)+off;
    unsigned int s=0;
    for(unsigned int i=0;i<nasum;++i,Ptr+=step) s+=*Ptr;
    return s;
  }

  double asum(const double* src, const long nasum,
              const int off=iZero, const long step=lOne) {
    return dasum_(&nasum,const_cast<double*>(src)+off,&step);
  }

}

#endif

