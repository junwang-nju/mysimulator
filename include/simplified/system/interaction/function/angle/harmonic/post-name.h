
#ifndef _System_Interaction_Function_Angle_Harmonic_Post_Name_H_
#define _System_Interaction_Function_Angle_Harmonic_Post_Name_H_

#include "system/interaction/function/angle/post-name.h"

namespace mysimulator {

  class AngleHarmonicPostName : public AnglePostName {

    public:

      typedef AnglePostName   ParentType;

      static const unsigned int Angle         = ParentType::NumberPost;
      static const unsigned int NumberPost    = Angle+1;

  };

  const unsigned int AngleHarmonicPostName::Angle;
  const unsigned int AngleHarmonicPostName::NumberPost;

}

#endif

