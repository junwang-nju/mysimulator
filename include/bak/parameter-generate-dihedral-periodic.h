
#ifndef _Parameter_Generate_Dihedral_Periodic_H_
#define _Parameter_Generate_Dihedral_Periodic_H_

#include "vector-base.h"
#include "parameter-name-dihedral-periodic.h"

namespace std {

  void ParameterGenerateDihedralPeriodic(VectorBase<double>& Param) {
    for(unsigned int i=0;i<Param.size();i+=4)
      Param[i+DihedralPeriodic_StrengthPeriod]=
        Param[i+DihedralPeriodic_Strength]*Param[i+DihedralPeriodic_Period];
  }
}

#endif
