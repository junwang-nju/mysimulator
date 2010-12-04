
#ifndef _Functional_Dihedral_Periodic_H_
#define _Functional_Dihedral_Periodic_H_

#include "data/name/dihedral-periodic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncDihPeriodic(const T& dih, const UniqueParameter* prm, T& func) {
    func=0.;
    for(unsigned int i=0,s=2;i<prm[DihPeriodicNumberPeriodicFunc].u;++i,s+=4)
      func+=prm[DihPeriodicStrength+s].value<T>()*
            (cosine(prm[DihPeriodicFrequence+s].value<T>()*
                    (dih+prm[DihPeriodicPhase+s].value<T>()))+1.);
  }

  template <typename T>
  void DiffDihPeriodic(const T& dih, const UniqueParameter* prm, T& diff) {
    diff=0.;
    for(unsigned int i=0,s=2;i<prm[DihPeriodicNumberPeriodicFunc].u;++i,s+=4)
      diff-=prm[DihPeriodicStrengthFrequence+s].value<T>()*
            sine(prm[DihPeriodicFrequence+s].value<T>()*
                 (dih+prm[DihPeriodicPhase+s].value<T>()));
  }

  template <typename T>
  void BothDihPeriodic(const T& dih, const UniqueParameter* prm,
                       T& func, T& diff) {
    T tmd;
    func=diff=0.;
    for(unsigned int i=0,s=2;i<prm[DihPeriodicNumberPeriodicFunc].u;++i,s+=4) {
      tmd=prm[DihPeriodicFrequence+s].value<T>()*
          (dih+prm[DihPeriodicPhase+s].value<T>());
      func+=prm[DihPeriodicStrength+s].value<T>()*(cosine(tmd)+1.);
      diff-=prm[DihPeriodicStrengthFrequence+s].value<T>()*sine(tmd);
    }
  }

}

#endif
