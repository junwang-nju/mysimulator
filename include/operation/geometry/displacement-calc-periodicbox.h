
#ifndef _Displacement_Calculate_Periodic_Box_H_
#define _Displacement_Calculate_Periodic_Box_H_

#include "operation/geometry/periodic-box-op.h"
#include "operation/geometry/displacement-calc-direct.h"

namespace std {

  template <typename TA, typename TB, typename TD, typename T>
  void Displacement(const TA* va, const TB* vb, TD* vd, const unsigned int dim,
                    const PeriodicBox<T>& G,
                    const int aoff=iZero, const long astep=lOne,
                    const int boff=iZero, const long bstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    Displacement(va,vb,vd,dim,aoff,astep,boff,bstep,doff,dstep);
    relocateVector(vd,dim,G,doff,dstep);
  }

  template <typename TA, typename TB, typename TD, typename T>
  void Displacement(const Vector<TA>& va, const Vector<TB>& vb, Vector<TD>& vd,
                    const PeriodicBox<T>& G) {
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    n=(n<vd.size?n:vd.size);
    Displacement(va.data,vb.data,vd.data,n,G);
  }

}

#endif
