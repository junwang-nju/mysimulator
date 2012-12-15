
#ifndef _System_Interaction_Function_Angle_Pre_Name_H_
#define _System_Interaction_Function_Angle_Pre_Name_H_

namespace mysimulator {

  class AnglePreName {

    public:

      static const unsigned int EdgeASQ     = 0;
      static const unsigned int EdgeBSQ     = EdgeASQ+1;
      static const unsigned int DotAB       = EdgeBSQ+1;
      static const unsigned int NumberPre   = DotAB+1;

  };

  const unsigned int AnglePreName::EdgeASQ;
  const unsigned int AnglePreName::EdgeBSQ;
  const unsigned int AnglePreName::DotAB;
  const unsigned int AnglePreName::NumberPre;

}

#endif

