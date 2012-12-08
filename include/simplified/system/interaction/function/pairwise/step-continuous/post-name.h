
#ifndef _System_Interaction_Function_Pairwise_StepContinuous_Post_Name_H_
#define _System_Interaction_Function_Pairwise_StepContinuous_Post_Name_H_

namespace mysimulator {

  class PairStepContinuousPostName {

    public:

      static const unsigned int DistanceSQ        = 0;
      static const unsigned int NumberPost        = DistanceSQ+1;

  };

  const unsigned int PairStepContinuousPostName::DistanceSQ;
  const unsigned int PairStepContinuousPostName::NumberPost;

}

#endif

