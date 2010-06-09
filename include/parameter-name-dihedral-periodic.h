
#ifndef _Parameter_Name_Dihedral_Periodic_H_
#define _Parameter_Name_Dihedral_Periodic_H_

namespace std {

  enum DihedralPeriodicParameterName {
    DihedralPeriodicNumberPeriodicFunc=0,
    DihedralPeriodicNumberParameter,
    DihedralPeriodicStrength=0,
    DihedralPeriodicFrequence,
    DihedralPeriodicPhase,
    DihedralPeriodicStrengthFrequence
  };
  
}

#include "vector.h"
#include "unique-parameter.h"

namespace std {

  void allocateDihedralPeriodicParameter(UniqueParameter* prm,
                                         const unsigned int np) {
    prm=new UniqueParameter[4*np+2];
    prm[DihedralPeriodicNumberPeriodicFunc]=np;
    prm[DihedralPeriodicNumberParameter]=4*np+2;
  }

  void allocateDihedralPeriodicParameter(Vector<UniqueParameter>& prm,
                                         const unsigned int np) {
    allocate(prm,4*np+2);
    prm[DihedralPeriodicNumberPeriodicFunc]=np;
    prm[DihedralPeriodicNumberParameter]=4*np+2;
  }

  void GenerateParameterDihedralPeriodic(UniqueParameter* prm) {
    for(unsigned int i=0,shf=2;i<prm[DihedralPeriodicNumberPeriodicFunc].u;
        ++i,shf+=4) {
      prm[DihedralPeriodicStrengthFrequence+shf]=
        prm[DihedralPeriodicStrength+shf].d*
        prm[DihedralPeriodicFrequence+shf].d;
    }
  }

  void GenerateParameterDihedralPeriodic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=prm[DihedralPeriodicNumberParameter].u);
    GenerateParameterDihedralPeriodic(prm());
  }

}

#endif
