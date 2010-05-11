
#ifndef _Functional_Dihedral_Periodic_H_
#define _Functional_Dihedral_Periodic_H_

#include "vector-base.h"
#include "parameter-name-dihedral-periodic.h"
#include <cmath>

namespace std {

  void FuncDihedralPeriodic(
      const double dihedral, const VectorBase<double>& Prm, double& func) {
    func=0.;
    for(unsigned int i=0;i<Prm.size();i+=4)
      func+=Prm[i+DihedralPeriodic_Strength]*
            (cos(Prm[i+DihedralPeriodic_Period]*
                (dihedral-Prm[i+DihedralPeriodic_Phase]))+1.);
  }

  void DiffDihedralPeriodic(const double dihedral,
                            const VectorBase<double>& Prm, double& diff) {
    diff=0.;
    for(unsigned int i=0;i<Prm.size();i+=4)
      diff+=-Prm[i+DihedralPeriodic_StrengthPeriod]*
            sin(Prm[i+DihedralPeriodic_Period]*
               (dihedral-Prm[i+DihedralPeriodic_Phase]));
  }

  void BothDihedralPeriodic(const double dihedral,
                            const VectorBase<double>& Prm,
                            double& func, double& diff) {
    double tmd;
    func=diff=0.;
    for(unsigned int i=0;i<Prm.size();i+=4) {
      tmd=Prm[i+DihedralPeriodic_Period]*
          (dihedral-Prm[i+DihedralPeriodic_Phase]);
      func+=Prm[i+DihedralPeriodic_Strength]*(cos(tmd)+1.);
      diff+=-Prm[i+DihedralPeriodic_StrengthPeriod]*sin(tmd);
    }
  }

}

#endif

