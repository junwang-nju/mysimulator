
#ifndef _Interaction_Parameter_Step_Continuous_Interface_H_
#define _Interaction_Parameter_Step_Continuous_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/step-continuous/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterStepContinuous : public InteractionParameter<T> {

    public:

      typedef InteractionParameterStepContinuous<T>   Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterStepContinuous() : ParentType() {}
      virtual ~InteractionParameterStepContinuous() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=StepContinuous;
        this->_data.Allocate(StepContinuousNumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=StepContinuousNumberParameter);
        assert(Value<T>(this->_data[StepContinuousRadius])>0);
        Value<T>(this->_data[StepContinuousHalfDepth])=
          0.5*Value<T>(this->_data[StepContinuousDepth]);
        Value<T>(this->_data[StepContinuousRadiusSQ])=
          Value<T>(this->_data[StepContinuousRadius])*
          Value<T>(this->_data[StepContinuousRadius]);
        if(Value<T>(this->_data[StepContinuousSharpness])*
           Value<T>(this->_data[StepContinuousRadius])<2) {
          fprintf(stderr,"Sharpness is Small! Default value Used!\n");
          Value<T>(this->_data[StepContinuousSharpness])=
              10./Value<T>(this->_data[StepContinuousRadius]);
        }
        Value<T>(this->_data[StepContinuousDepthSharp])=
          Value<T>(this->_data[StepContinuousDepth])*
          Value<T>(this->_data[StepContinuousSharpness]);
      }

    private:

      InteractionParameterStepContinuous(const Type&) {}
      Type& operator=(const Type&) { return *this; }
  };

  template <typename T>
  void Clear(InteractionParameterStepContinuous<T>& P) {
    typedef typename InteractionParameterStepContinuous<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void Clear(InteractionParameterStepContinuous<T>& P,
             const InteractionParameterStepContinuous<T>& BP) {
    typedef typename InteractionParameterStepContinuous<T>::ParentType PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

