
#include "vector-impl.h"
#include "blas.h"
#include "constant.h"

namespace std {

  template <typename T>
  void vector_assign(T* v, const T* iv, long ncopy, int voff,  long vstep,
                                                    int off, long step) {
    T* vPtr=v+off;
    T* ivPtr=const_cast<T*>(iv)+voff;
    for(int i=0;i<ncopy;++i,vPtr+=step,ivPtr+=vstep)
      *vPtr=*ivPtr;
  }

  void vector_assign(double* v, const double* iv, long ncopy,
                     int voff, long vstep, int off, long step) {
    dcopy_(&ncopy,const_cast<double*>(iv)+voff,&vstep,v+off,&step);
  }

  void vector_scale(double* v,const double& d, long nsc, int off, long step) {
    dscal_(&nsc,const_cast<double*>(&d),v+off,&step);
  }

  void vector_scale(double* v,const double* iv, long nsc, int voff, long vstep,
                                                          int off, long step) {
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,&nsc,&lZero,const_cast<double*>(iv)+voff,&vstep,
           v+off,&step);
  }

  void vector_shift(double* v, const double& d, const double* iv, long nsf,
                    int voff, long vstep, int off, long step) {
    daxpy_(&nsf,const_cast<double*>(&d),const_cast<double*>(iv)+voff,&vstep,
           v+off,&step);
  }

  void vector_scaleshift(double* v, const double& s, const double& sf,
                         const double* sfv, const double* iv, long nss,
                         int sfoff, long sfstep, int voff, long vstep,
                         int off, long step) {
    static char flag[]="L";
    dsbmv_(flag,&nss,&lZero,const_cast<double*>(&sf),
           const_cast<double*>(sfv)+sfoff,&sfstep,
           const_cast<double*>(iv)+voff,&vstep,const_cast<double*>(&s),
           v+off,&step);
  }

  template <typename T>
  void vector_exchange(T* va, T* vb, long nex, int aoff, long astep,
                                               int boff, long bstep) {
    T tmT, *aPtr, *bPtr;
    aPtr=va+aoff;
    bPtr=vb+boff;
    for(int i=0;i<nex;++i,aPtr+=astep,bPtr+=bstep) {
      tmT=*aPtr;  *aPtr=*bPtr;  *bPtr=tmT;
    }
  }

  void vector_exchange(double* va, double* vb, long nex, int aoff, long astep,
                                                         int boff, long bstep){
    dswap_(&nex,va+aoff,&astep,vb+boff,&bstep);
  }

  double vector_dot(const double* va, const double* vb, long ndot,
                    int aoff, long astep, int boff, long bstep) {
    return ddot_(&ndot,const_cast<double*>(va)+aoff,&astep,
                       const_cast<double*>(vb)+boff,&bstep);
  }

  double vector_norm(const double* v, long nnm, int off, long step) {
    return dnrm2_(&nnm,const_cast<double*>(v)+off,&step);
  }

  double vector_asum(const double* v, long nas, int off, long step) {
    return dasum_(&nas,const_cast<double*>(v)+off,&step);
  }

}

