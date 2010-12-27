
#ifndef _Mass_Center_Calc_H_
#define _Mass_Center_Calc_H_

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void MassCenter(const Vector<T>* X, const unsigned int* idx,
                  const unsigned int nidx, Vector<T>& cv) {
    copy(cv,0.);
    for(unsigned int i=0;i<nidx;++i)  shift(cv,iOne,X[idx[i]]);
    scale(cv,static_cast<T>(1./nidx));
  }

  template <typename T>
  void MassCenter(const Vector<T>* X, const unsigned int nidx,
                  Vector<T>& cv) {
    copy(cv,0.);
    for(unsigned int i=0;i<nidx;++i)  shift(cv,iOne,X[i]);
    scale(cv,static_cast<T>(1./nidx));
  }

}

#endif
