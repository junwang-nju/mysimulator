
#ifndef _Vector_Implementation_H_
#define _Vector_Implementation_H_

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
                     int voff, long vstep, int off, long step);

  void vector_scale(double* v,const double& value,long nsc,int off,long step);

  void vector_scale(double* v,const double* iv, long nsc, int voff, long vstep,
                                                          int off, long step);

  void vector_shift(double* v, const double& d, const double* iv, long nsf,
                    int voff, long vstep, int off, long step);

  void vector_scaleshift(double* v, const double& s, const double& sf,
                         const double* sfv, const double* iv, long nss,
                         int sfoff, long sfstep, int voff, long vstep,
                         int off, long step);

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
                                                         int boff, long bstep);

  double vector_dot(const double* va, const double* vb, long ndot,
                    int aoff, long astep, int boff, long bstep);

  double vector_norm(const double* v, long nnm, int off, long step);

  double vector_asum(const double* v, long nas, int off, long step);

}

#endif

