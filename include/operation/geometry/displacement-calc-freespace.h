
#ifndef _Displacement_Calculate_FreeSpace_H_
#define _Displacement_Calculate_FreeSpace_H_

#include "data/geometry/free-space.h"
#include "operation/geometry/displacement-calc-direct.h"

namespace std {

  template <typename TA, typename TB, typename TD>
  void Displacement(const TA* va, const TB* vb, TD* vd, const unsigned int dim,
                    const FreeSpace& G,
                    const int aoff=iZero, const long astep=lOne,
                    const int boff=iZero, const long bstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    Displacement(va,vb,vd,dim,aoff,astep,boff,bstep,doff,dstep);
  }

  template <typename TA, typename TB, typename TD>
  void Displacement(const Vector<TA>& va, const Vector<TB>& vb, Vector<TD>& vd,
                    const FreeSpace& G) {
    Displacement(va,vb,vd);
  }

}

#endif
