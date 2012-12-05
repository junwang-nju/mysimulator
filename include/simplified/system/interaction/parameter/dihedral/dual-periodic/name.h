
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_Name_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_Name_H_

namespace mysimulator {

  class DihedralDualPeriodicParameterName {

    public:

      static const unsigned int Period1         = 0;
      static const unsigned int Period2         = Period1+1;
      static const unsigned int NumberParameter = Period2+1;

  };

  const unsigned int DihedralDualPeriodicParameterName::Period1;
  const unsigned int DihedralDualPeriodicParameterName::Period2;
  const unsigned int DihedralDualPeriodicParameterName::NumberParameter;

}

#endif

