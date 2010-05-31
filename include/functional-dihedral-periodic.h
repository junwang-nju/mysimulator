
#ifndef _Functional_Dihedral_Periodic_H_
#define _Functional_Dihedral_Periodic_H_

#include "parameter-name-dihedral-periodic.h"

namespace std {

  void FuncDihPeriodic(const double dih, const UniqueParameter* prm,
                       double& func) {
    func=0.;
    for(unsigned int i=0,shf=1;i<prm[DihedralPeriodicNumberPeriodicFunc].u;
        ++i,shf+=4)
      func+=prm[DihedralPeriodicStrength+shf].d*
            (cos(prm[DihedralPeriodicFrequence+shf].d*
                (dih-prm[DihedralPeriodicPhase+shf].d))+1.);
  }

  void DiffDihPeriodic(const double dih, const UniqueParameter* prm,
                       double& diff) {
    diff=0.;
    for(unsigned int i=0,shf=1;i<prm[DihedralPeriodicNumberPeriodicFunc].u;
        ++i,shf+=4)
      diff+=-prm[DihedralPeriodicStrengthFrequence+shf].d*
             sin(prm[DihedralPeriodicFrequence+shf].d*
                (dih-prm[DihedralPeriodicPhase+shf].d));
  }

  void BothDihPeriodic(const double dih, const UniqueParameter* prm,
                       double& func, double& diff) {
    double tmd;
    func=diff=0.;
    for(unsigned int i=0,shf=1;i<prm[DihedralPeriodicNumberPeriodicFunc].u;
        ++i,shf+=4) {
      tmd=prm[DihedralPeriodicFrequence+shf].d*
          (dih-prm[DihedralPeriodicPhase+shf].d)
      func+=prm[DihedralPeriodicStrength+shf].d*(cos(tmd)+1.);
      diff+=-prm[DihedralPeriodicStrengthFrequence+shf].d*sin(tmd);
    }
  }

}

#endif
