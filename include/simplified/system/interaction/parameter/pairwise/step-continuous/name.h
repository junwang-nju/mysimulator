
#ifndef _System_Interaction_Parameter_Pairwise_StepContinuous_Name_H_
#define _System_Interaction_Parameter_Pairwise_StepContinuous_Name_H_

namespace mysimulator {

  class PairStepContinuousParameterName {

    public:

      static const unsigned int Depth           = 0;
      static const unsigned int Radius          = Depth+1;
      static const unsigned int Sharpness       = Radius+1;
      static const unsigned int HalfDepth       = Sharpness+1;
      static const unsigned int RadiusSQ        = HalfDepth+1;
      static const unsigned int DSProduct       = RadiusSQ+1;
      static const unsigned int NumberParameter = DSProduct+1;

  };

  const unsigned int PairStepContinuousParameterName::Depth;
  const unsigned int PairStepContinuousParameterName::Radius;
  const unsigned int PairStepContinuousParameterName::Sharpness;
  const unsigned int PairStepContinuousParameterName::HalfDepth;
  const unsigned int PairStepContinuousParameterName::RadiusSQ;
  const unsigned int PairStepContinuousParameterName::DSProduct;
  const unsigned int PairStepContinuousParameterName::NumberParameter;

}

#endif

