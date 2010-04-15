
#ifndef _Functional_Dihedral_Periodic_H_
#define _Functional_Dihedral_Periodic_H_

#include <cmath>

namespace std {

  void FuncDihedralPeriodic(
      const double dihedral, const VectorBase<double>& Prm, double& func) {
    func=0.;
    for(unsigned int i=1;i<Prm.size();i+=2)
      func+=cos(Prm[i]*(dihedral-Prm[i+1]))+1.;
    func*=Prm[DihPeriodic_EqStrength];
  }

}

#endif

