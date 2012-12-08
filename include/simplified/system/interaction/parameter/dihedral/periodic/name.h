
#ifndef _System_Interaction_Parameter_Dihedral_Periodic_Name_H_
#define _System_Interaction_Parameter_Dihedral_Periodic_Name_H_

namespace mysimulator {

  class DihedralPeriodicParameterName {
    public:
      class Int {
        public:
          static const unsigned int Frequency       = 0;
          static const unsigned int NumberParameter = Frequency+1;
      };
      class Double {
        public:
          static const unsigned int Strength        = 0;
          static const unsigned int Phase           = Strength+1;
          static const unsigned int SFProduct       = Phase+1;
          static const unsigned int NumberParameter = SFProduct+1;
      };
  };

  const unsigned int DihedralPeriodicParameterName::Int::Frequency;
  const unsigned int DihedralPeriodicParameterName::Int::NumberParameter;
  const unsigned int DihedralPeriodicParameterName::Double::Strength;
  const unsigned int DihedralPeriodicParameterName::Double::Phase;
  const unsigned int DihedralPeriodicParameterName::Double::SFProduct;
  const unsigned int DihedralPeriodicParameterName::Double::NumberParameter;

}

#endif

