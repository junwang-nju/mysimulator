
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_Name_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_Name_H_

namespace mysimulator {

  class DihedralDualPeriodicParameterName {

    public:

      class Int {
        public:
          static const unsigned int NumberChild     = 0;
          static const unsigned int NumberParameter = NumberChild+1;
      };

      class Child {
        public:
          static const unsigned int Period1         = 0;
          static const unsigned int Period2         = Period1+1;
          static const unsigned int NumberParameter = Period2+1;
      };

  };

  const unsigned int DihedralDualPeriodicParameterName::Int::NumberChild;
  const unsigned int DihedralDualPeriodicParameterName::Int::NumberParameter;
  const unsigned int DihedralDualPeriodicParameterName::Child::Period1;
  const unsigned int DihedralDualPeriodicParameterName::Child::Period2;
  const unsigned int DihedralDualPeriodicParameterName::Child::NumberParameter;

}

#endif

