
#ifndef _System_Interaction_Parameter_Angle_Harmonic_Name_H_
#define _System_Interaction_Parameter_Angle_Harmonic_Name_H_

namespace mysimulator {

  class AngleHarmonicParameterName {

    public:

      static const unsigned int EqAngle         = 0;
      static const unsigned int EqStrength      = EqAngle+1;
      static const unsigned int DualEqStrength  = EqStrength+1;
      static const unsigned int NumberParameter = DualEqStrength+1;

  };

  const unsigned int AngleHarmonicParameterName::EqAngle;
  const unsigned int AngleHarmonicParameterName::EqStrength;
  const unsigned int AngleHarmonicParameterName::DualEqStrength;
  const unsigned int AngleHarmonicParameterName::NumberParameter;

}

#endif

