
#ifndef _System_Interaction_Function_Angle_Post_Name_H_
#define _System_Interaction_Function_Angle_Post_Name_H_

namespace mysimulator {

  class AnglePostName {

    public:

      static const unsigned int Cosine      = 0;
      static const unsigned int IvRabSin    = Cosine+1;
      static const unsigned int IvRaSQCtg   = IvRabSin+1;
      static const unsigned int IvRbSQCtg   = IvRaSQCtg+1;
      static const unsigned int NumberPost  = IvRbSQCtg+1;

  };

  const unsigned int AnglePostName::Cosine;
  const unsigned int AnglePostName::IvRabSin;
  const unsigned int AnglePostName::IvRaSQCtg;
  const unsigned int AnglePostName::IvRbSQCtg;
  const unsigned int AnglePostName::NumberPost;

}

#endif

