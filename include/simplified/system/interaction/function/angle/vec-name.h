
#ifndef _System_Interaction_Function_Angle_Vec_Name_H_
#define _System_Interaction_Function_Angle_Vec_Name_H_

namespace mysimulator {

  class AngleVecName {

    public:

      static const unsigned int BondIJ      = 0;
      static const unsigned int BondKJ      = BondIJ+1;
      static const unsigned int NormI       = BondKJ+1;
      static const unsigned int NormK       = NormI+1;
      static const unsigned int ScaleNormI  = NormK+1;
      static const unsigned int ScaleNormK  = ScaleNormI+1;
      static const unsigned int NumberVec   = ScaleNormK+1;

  };

  const unsigned int AngleVecName::BondIJ;
  const unsigned int AngleVecName::BondKJ;
  const unsigned int AngleVecName::NormI;
  const unsigned int AngleVecName::NormK;
  const unsigned int AngleVecName::ScaleNormI;
  const unsigned int AngleVecName::ScaleNormK;
  const unsigned int AngleVecName::NumberVec;

}

#endif

