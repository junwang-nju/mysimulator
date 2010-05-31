
#ifndef _Parameter_Name_Dihedral_Periodic_H_
#define _Parameter_Name_Dihedral_Periodic_H_

namespace std {

  enum DihedralPeriodicParameterName {
    DihedralPeriodicNumberPeriodicFunc=0,
    DihedralPeriodicStrength=0,
    DihedralPeriodicFrequence,
    DihedralPeriodicPhase,
    DihedralPeriodicStrengthFrequence
  };
  
  unsigned int DihedralPeriodicNumberParameter;

}

#include "vector.h"
#include "unique-parameter.h"

namespace std {

  void allocateDihedralPeriodicParameter(UniqueParameter* prm,
                                         const unsigned int np) {
    DihedralPeriodicNumberParameter=4*np+1;
    prm=new UniqueParameter[DihedralPeriodicNumberParameter];
    prm[DihedralPeriodNumberPeriodicFunc]=np;
  }

  void allocateDihedralPeriodicParameter(Vector<UniqueParameter>& prm,
                                         const unsigned int np) {
    DihedralPeriodicNumberParameter=4*np+1;
    allocate(prm,DihedralPeriodicNumberParameter);
    prm[DihedralPeriodNumberPeriodicFunc]=np;
  }

  void GenerateParameterDihedralPeriodic(UniqueParameter* prm) {
    unsigned int shf;
    for(unsigned int i=0,sft=1;i<prm[DihedralPeriodicNumberPeriodicFunc].u;
        ++i,shf+=4) {
      prm[DihedralPeriodicStrengthFrequence+shf]=
        prm[DihedralPeriodicStrength+shf].d*
        prm[DihedralPeriodicFrequence+shf].d;
    }
  }

  void GenerateParameterDihedralPeriodic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=DihedralPeriodicNumberParameter);
    GenerateParameterDihedralPeriodic(prm());
  }

}

#endif
