
#ifndef _Distance_Calculate_H_
#define _Distance_Calculate_H_

#include "operation/basic/blas.h"
#include "data/name/constant.h"

namespace std {

  double displacement2distanceSQ(const double* dsp, const unsigned int dim,
                                 const int off=iZero, const long step=lOne) {
    return ddot_(reinterpret_cast<long*>(const_cast<unsigned int*>(&dim)),
                 const_cast<double*>(dsp)+off,const_cast<long*>(&step),
                 const_cast<double*>(dsp)+off,const_cast<long*>(&step));
  }

  float displacement2distanceSQ(const float* dsp, const unsigned int dim,
                                const int off=iZero, const long step=lOne) {
    return sdot_(reinterpret_cast<long*>(const_cast<unsigned int*>(&dim)),
                 const_cast<float*>(dsp)+off,const_cast<long*>(&step),
                 const_cast<float*>(dsp)+off,const_cast<long*>(&step));
  }

  int displacement2distanceSQ(const int* dsp, const unsigned int dim,
                              const int off=iZero, const long step=lOne) {
    int s=0;
    for(unsigned int i=0;i<dim;++i) s+=dsp[i]*dsp[i];
    return s;
  }

  unsigned int displacement2distanceSQ(const unsigned int* dsp,
                                       const unsigned int dim,
                                       const int off=iZero,
                                       const long step=lOne) {
    unsigned int s=0;
    for(unsigned int i=0;i<dim;++i) s+=dsp[i]*dsp[i];
    return s;
  }

  template <typename TA, typename TB, typename TD, typename GeomType>
  TD Distance(const TA* va, const TB* vb, TD* dsp, const unsigned int dim,
              const GeomType& Geo,
              const int aoff=iZero, const long astep=lOne,
              const int boff=iZero, const long bstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    Displacement(va,vb,dsp,dim,Geo,aoff,astep,boff,bstep,doff,dstep);
    return displacement2distanceSQ(dsp,dim,doff,dstep);
  }

}

#include "operation/basic/vector-op.h"

namespace std {

  template <typename T>
  T displacement2distanceSQ(const Vector<T>& dsp) { return normSQ(dsp); }

  template <typename TA, typename TB, typename TD, typename GeomType>
  TD Distance(const Vector<TA>& va, const Vector<TB>& vb, Vector<TD>& dsp,
              const GeomType& Geo) {
    Displacement(va,vb,dsp,Geo);
    return displacement2distanceSQ(dsp);
  }

}

#endif
