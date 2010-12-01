
#ifndef _Build_Parameter_Dihedral_Periodic_H_
#define _Build_Parameter_Dihedral_Periodic_H_

#include "data/name/parameter-dihedral-periodic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  void allocateDihPeriodicParameter(UniqueParameter* prm,
                                    const unsigned int np){
    prm=new UniqueParameter[4*np+2];
    prm[DihPeriodicNumberPeriodicFunc].u=np;
    prm[DihPeriodicNumberParameter].u=4*np+2;
  }
  
  template <typename T>
  void BuildParameterDihPeriodic(UniqueParameter* prm) {
    for(unsigned int i=0,s=2;i<prm[DihPeriodicNumberPeriodicFunc].u;++i,s+=4)
      copy(prm[DihPeriodicStrengthFrequence+s],
           prm[DihPeriodicStrength+s].value<T>()*
           prm[DihPeriodicFrequence+s].value<T>());
  }

}

#include "data/basic/vector.h"

namespace std {

  void allocateDihPeriodicParameter(Vector<UniqueParameter>& prm,
                                    const unsigned int np) {
    allocateDihPeriodicParameter(prm.data,np);
  }

  template <typename T>
  void BuildParameterDihPeriodic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=prm[DihPeriodicNumberParameter].u);
    BuildParameterDihPeriodic<T>(prm.data);
  }

}

#endif
