
#ifndef _Vector_Implementation_CC_
#define _Vector_Implementation_CC_

#include "constant.h"
#include "blas.h"
#include "error-proc.h"
#include <cassert>
#include <cstring>

namespace std {

  template <typename vType>
  bool isVector() {
    return (strcmp(vType::TypeTag,"varVector")==0)||
           (strcmp(vType::TypeTag,"fixVector")==0);
  }

  template <typename T>
  void vector_assign(T* v, const T* iv, long ncopy,
                     int offset=iZero,int ioffset=iZero,
                     long step=lOne, long istep=lOne) {
    T* optr=v+offset;
    T* iptr=const_cast<T*>(iv)+ioffset;
    for(int i=0;i<ncopy;++i) {
      *optr=*iptr;
      optr+=step;
      iptr+=istep;
    }
  }
  
  void vector_assign(double* v, const double* iv, long ncopy,
                     int offset=iZero, int ioffset=iZero,
                     long step=lOne, long istep=lOne) {
    dcopy_(&ncopy,const_cast<double*>(iv)+ioffset,&istep,v+offset,&step);
  }
  
  template <typename T, typename ScaleT>
  void vector_scale(T* v, const ScaleT& s, long nscale,
                    int offset=iZero, int soffset=iZero,
                    long step=lOne, long sstep=lOne) {
    myError("Scale for generic type is not available!");
  }
  
  void vector_scale(double* v, const double& d, long nscale,
                    int offset=iZero, int soffset=iZero,
                    long step=lOne, long sstep=lZero) {
    assert((soffset==iZero)&&(sstep==lZero));
    dscal_(&nscale,const_cast<double*>(&d),v+offset,&step);
  }
  
  void vector_scale(double* v, const double* sv, long nscale,
                    int offset=iZero, int soffset=iZero,
                    long step=lOne, long sstep=lOne) {
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,&nscale,&lZero,
           const_cast<double*>(sv)+soffset,&sstep,v+offset,&step);
  }
  
  template <typename T, typename ScaleT>
  void vector_shift(T* v, const ScaleT& s, const T* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lOne, long sfstep=lOne) {
    myError("Shift for generic type is not available!");
  }

  void vector_shift(double* v, const double& s, const double* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lZero, long sfstep=lOne) {
    assert((soffset==iZero)&&(sstep==lZero));
    daxpy_(&nshift,const_cast<double*>(&s),const_cast<double*>(sfv)+sfoffset,
           &sfstep,v+offset,&step);
  }
  
  template <typename T>
  void vector_scaleshift(T* v, const T& s, const T& sf, const T* sfv,
                         const T* sv, long nscaleshift, int offset=iZero,
                         int sfoffset=iZero, int soffset=iZero,
                         long step=lOne, long sfstep=lOne, long sstep=lOne) {
    myError("Scaled Shift for generic type is not available!");
  }
  
  void vector_scaleshift(double* v, const double& s, const double& sf,
                         const double* sfv, const double* sv, long nscaleshift,
                         int offset=iZero, int sfoffset=iZero,
                         int soffset=iZero, long step=lOne,
                         long sfstep=lOne, long sstep=lOne) {
    static char flag[]="L";
    dsbmv_(flag,&nscaleshift,&lZero,const_cast<double*>(&sf),
           const_cast<double*>(sfv)+sfoffset,&sfstep,
           const_cast<double*>(sv)+soffset,&sstep,const_cast<double*>(&s),
           v+offset,&step);
  }

  template <typename T>
  void vector_swap(T* va, T* vb, long nswap,
                   int aoffset=iZero, long astep=lOne,
                   int boffset=iZero, long bstep=lOne) {
    T tmT, *pa, *pb;
    pa=va+aoffset;
    pb=vb+boffset;
    for(int i=0;i<nswap;++i) {
      tmT=*pa;    *pa=*pb;    *pb=tmT;
      pa+=astep;
      pb+=bstep;
    }
  }

  void vector_swap(double* va, double* vb, long nswap,
                   int aoffset=iZero, int boffset=iZero,
                   long astep=lOne, long bstep=lOne) {
    dswap_(&nswap,va+aoffset,&astep,vb+boffset,&bstep);
  }

}

#endif
