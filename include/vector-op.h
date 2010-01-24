
#ifndef _Vector_Operation_H_
#define _Vector_Operation_H_

#include "vector-base.h"

namespace std {
  double dot(const VectorBase<double>& va, const VectorBase<double>& vb);
  double dot(const VectorBase<double>& va, const VectorBase<double>& vb,
             long ndot, int aoff=iZero, long astep=lOne,
                        int boff=iZero, long bstep=lOne);
  double normSQ(const VectorBase<double>& v);
  double normSQ(const VectorBase<double>& v, long nnsq,
                int off=iZero, long step=lOne);
  double norm(const VectorBase<double>& v);
  double norm(const VectorBase<double>& v, long nnm,
              int off=iZero, long step=lOne);
  double sumABS(const VectorBase<double>& v);
  double sumABS(const VectorBase<double>& v, long nsa,
                int off=iZero, long step=lOne);
  void crossProd(const VectorBase<double>& va, const VectorBase<double>& vb,
                 VectorBase<double>& v, int aoff=iZero, long astep=lOne,
                                        int boff=iZero, long bstep=lOne,
                                        int coff=iZero, long cstep=lOne);
}

#endif

