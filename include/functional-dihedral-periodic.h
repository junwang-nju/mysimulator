
#ifndef _Functional_Dihedral_Periodic_H_
#define _Functional_Dihedral_Periodic_H_

#include "ref-vector.h"
#include <cmath>

namespace std {

  void FuncDihedralPeriodic(
      const double dihedral, const VectorBase<double>& Prm, double& func) {
    func=0.;
    for(unsigned int i=1;i<Prm.size();i+=2)
      func+=cos(Prm[i]*(dihedral-Prm[i+1]))+1.;
    func*=Prm[DihPeriodic_EqStrength];
  }

  void DiffDihedralPeriodic(
      const double dihedral, const double dsq01, const double dsq12,
      const double dsq23, const VectorBase<refVector<double> >& tmVec,
      const VectorBase<double>& Prm,
      double& ef0, double& ef1, double ef2, double& ef2) {
  }

}

#endif

