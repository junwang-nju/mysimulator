
#ifndef _Topology_Dihedral_Calc_H_
#define _Topology_Dihedral_Calc_H_

#include "array/2d/allocate.h"
#include "array/1d/cross.h"
#include "intrinsic-type/acos.h"
#include "distance/calc.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  double Dihedral(const Array1DContent<T>& XI, const Array1DContent<T>& XJ,
                  const Array1DContent<T>& XK, const Array1DContent<T>& XL,
                  const GeomType& Geo) {
    Array2D<T> tmvec;
    allocate(tmvec,6,3);
    DisplacementCalc(tmvec[0],XJ,XI,Geo);
    DisplacementCalc(tmvec[1],XK,XJ,Geo);
    DisplacementCalc(tmvec[2],XL,XK,Geo);
    cross(tmvec[3],tmvec[0],tmvec[1]);
    cross(tmvec[4],tmvec[1],tmvec[2]);
    T nr3=norm(tmvec[3]);
    T nr4=norm(tmvec[4]);
    assert(nr3>1e-8);
    assert(nr4>1e-8);
    T csDih=dot(tmvec[3],tmvec[4])/(nr3*nr4);
    cross(tmvec[5],tmvec[3],tmvec[4]);
    T sgnDih=(dot(tmvec[1],tmvec[5])>0?1:-1);
    return arcCos(csDih)*sgnDih;
  }

}

#endif

