
#ifndef _Vector_Implementation_H_
#define _Vector_Implementation_H_

#include "constant.h"
#include "blas.h"
#include "memory.h"
#include <cassert>
#include <cstdlib>

namespace std {

  template <typename T>
  bool IsPointerAvailable(const T* ptr) { return ptr!=NULL; }

  template <typename T>
  void allocate(T* &dest, const unsigned int N) {
    if(N==0)  return;
    release(dest);
    dest=new T[N];
  }

  template <typename T>
  void release(T* &dest) { safe_delete_array(dest); }

  template <typename T>
  void assign(T* dest, const T* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(src!=NULL);
    T* dPtr=dest+doff, sPtr=const_cast<T*>(src)+soff;
    for(unsigned int i=0;i<ncopy;++i,++dPtr,++sPtr)   *dPtr=*sPtr;
  }

  void assign(double* dest, const double* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(src!=NULL);
    dcopy_(const_cast<long*>(&ncopy),const_cast<double*>(src)+soff,
           const_cast<long*>(&sstep),dest+doff,const_cast<long*>(&dstep));
  }

  void assign(int* dest, const int* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(src!=NULL);
    scopy_(const_cast<long*>(&ncopy),
           reinterpret_cast<float*>(const_cast<int*>(src))+soff,
           const_cast<long*>(&sstep),
           reinterpret_cast<float*>(dest)+doff,const_cast<long*>(&dstep));
  }

  void assign(unsigned int* dest, const unsigned int* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(src!=NULL);
    scopy_(const_cast<long*>(&ncopy),
           reinterpret_cast<float*>(const_cast<unsigned int*>(src))+soff,
           const_cast<long*>(&sstep),reinterpret_cast<float*>(dest)+doff,
           const_cast<long*>(&dstep));
  }

  template <typename T>
  void assign(T* dest, const T& value, const long ncopy,
              const int doff=iZero, const long dstep=lOne) {
    assign(dest,&value,ncopy,iZero,lZero,doff,dstep);
  }

  void scale(int* dest, const int factor, const long nscale,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    int *dPtr=dest+doff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);++i,dPtr+=dstep)
      *dPtr*=factor;
  }

  void scale(unsigned int* dest, const unsigned int factor, const long nscale,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    unsigned int* dPtr=dest+doff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);++i,dPtr+=dstep)
      *dPtr*=factor;
  }

  void scale(double* dest, const double factor, const long nscale,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    dscal_(const_cast<long*>(&nscale),const_cast<double*>(&factor),
           dest+doff,const_cast<long*>(&dstep));
  }

  void scale(int* dest, const int* vfactor,const long nscale,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    int* dPtr=dest+doff, *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr*=*vPtr;
  }

  void scale(unsigned int* dest, const unsigned int* vfactor,const long nscale,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    unsigned int* dPtr=dest+doff,*vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr*=*vPtr;
  }

  void scale(double* dest, const double* vfactor, const long nscale,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,const_cast<long*>(&nscale),&lZero,
           const_cast<double*>(vfactor)+voff,
           const_cast<long*>(&vstep),dest+doff,const_cast<long*>(&dstep));
  }

  void shift(int* dest, const int factor, const int* vfactor,const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    int *dPtr=dest+doff, *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nshift);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr+=factor*(*vPtr);
  }

  void shift(unsigned int* dest, const unsigned int factor,
             const unsigned int* vfactor, const long nshift,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    unsigned int *dPtr=dest+doff;
    unsigned int *vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nshift);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr+=factor*(*vPtr);
  }

  void shift(double* dest, const double factor, const double* vfactor,
             const long nshift, const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    daxpy_(const_cast<long*>(&nshift),const_cast<double*>(&factor),
           const_cast<double*>(vfactor)+voff,const_cast<long*>(&vstep),
           dest+doff,const_cast<long*>(&dstep));
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

  void scaleshift(int* dest, const int dfactor, const int factor,
                  const int* sfactor, const int* vfactor,
                  const long nscaleshift,
                  const int soff=iZero, const long sstep=lOne,
                  const int voff=iZero, const long vstep=lOne,
                  const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(sfactor!=NULL);
    assert(vfactor!=NULL);
    int *dPtr=dest+doff;
    int *sPtr=const_cast<int*>(sfactor)+soff;
    int *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscaleshift);
                     ++i,dPtr+=dstep,sPtr+=sstep,vPtr+=vstep){
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
    assert(dest!=NULL);
    assert(sfactor!=NULL);
    assert(vfactor!=NULL);
    unsigned int *dPtr=dest+doff;
    unsigned int *sPtr=const_cast<unsigned int*>(sfactor)+soff;
    unsigned int *vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscaleshift);
                         ++i,dPtr+=dstep,sPtr+=sstep,vPtr+=vstep){
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
    assert(dest!=NULL);
    assert(sfactor!=NULL);
    assert(vfactor!=NULL);
    static char flag[]="L";
    dsbmv_(flag,const_cast<long*>(&nscaleshift),&lZero,
           const_cast<double*>(&factor), const_cast<double*>(sfactor)+soff,
           const_cast<long*>(&sstep), const_cast<double*>(vfactor)+voff,
           const_cast<long*>(&vstep),const_cast<double*>(&dfactor),dest+doff,
           const_cast<long*>(&dstep));
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
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    T tmT, *aPtr=srcA+aoff, *bPtr=srcB+boff;
    for(unsigned int i=0;i<nexchange;++i,aPtr+=astep,bPtr+=bstep) {
      tmT=*aPtr;  *aPtr=*bPtr;  *bPtr=tmT;
    }
  }

  void exchange(int* srcA, int* srcB, const long nexchange,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    sswap_(const_cast<long*>(&nexchange),
           reinterpret_cast<float*>(srcA)+aoff,const_cast<long*>(&astep),
           reinterpret_cast<float*>(srcB)+boff,const_cast<long*>(&bstep));
  }

  void exchange(unsigned int* srcA, unsigned int* srcB, const long nexchange,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    sswap_(const_cast<long*>(&nexchange),
           reinterpret_cast<float*>(srcA)+aoff,const_cast<long*>(&astep),
           reinterpret_cast<float*>(srcB)+boff,const_cast<long*>(&bstep));
  }

  void exchange(double* srcA, double* srcB, const long nexchange,
                const int aoff=iZero, const long astep=lOne,
                const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    dswap_(const_cast<long*>(&nexchange),srcA+aoff,
           const_cast<long*>(&astep),srcB+boff,const_cast<long*>(&bstep));
  }

  int dot(const int* srcA, const int* srcB,const long ndot,
          const int aoff=iZero, const long astep=lOne,
          const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    int *aPtr=const_cast<int*>(srcA)+aoff, *bPtr=const_cast<int*>(srcB)+boff;
    int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(ndot);
                     ++i,aPtr+=astep,bPtr+=bstep)
      s+=(*aPtr)*(*bPtr);
    return s;
  }

  unsigned int dot(const unsigned int* srcA, const unsigned int* srcB,
                   const long ndot,
                   const int aoff=iZero, const long astep=lOne,
                   const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    unsigned int *aPtr=const_cast<unsigned int*>(srcA)+aoff;
    unsigned int *bPtr=const_cast<unsigned int*>(srcB)+boff;
    unsigned int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(ndot);
                     ++i,aPtr+=astep,bPtr+=bstep)
      s+=(*aPtr)*(*bPtr);
    return s;
  }

  double dot(const double* srcA, const double* srcB, const long ndot,
             const int aoff=iZero, const long astep=lOne,
             const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    return ddot_(const_cast<long*>(&ndot),const_cast<double*>(srcA)+aoff,
                 const_cast<long*>(&astep),const_cast<double*>(srcB)+boff,
                 const_cast<long*>(&bstep));
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
    assert(src!=NULL);
    return dnrm2_(const_cast<long*>(&nnorm),const_cast<double*>(src)+off,
                  const_cast<long*>(&step));
  }

  int asum(const int* src, const long nasum,
           const int off=iZero, const long step=lOne) {
    assert(src!=NULL);
    int *Ptr=const_cast<int*>(src)+off;
    int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(nasum);++i,Ptr+=step)
      s+=abs(*Ptr);
    return s;
  }

  unsigned int asum(const unsigned int* src, const long nasum,
                    const int off=iZero, const long step=lOne) {
    assert(src!=NULL);
    unsigned int *Ptr=const_cast<unsigned int*>(src)+off;
    unsigned int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(nasum);++i,Ptr+=step)
      s+=*Ptr;
    return s;
  }

  double asum(const double* src, const long nasum,
              const int off=iZero, const long step=lOne) {
    assert(src!=NULL);
    return dasum_(const_cast<long*>(&nasum),const_cast<double*>(src)+off,
                  const_cast<long*>(&step));
  }

}

#endif

