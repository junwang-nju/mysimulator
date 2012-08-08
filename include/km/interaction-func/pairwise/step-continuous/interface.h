
#ifndef _Interaction_Func_Step_Continuous_Interface_H_
#define _Interaction_Func_Step_Continuous_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-parameter/step-continuous/name.h"
#include "interaction-func/pairwise/step-continuous/post-name.h"
#include "interaction-func/pairwise/step-continuous/pre-name.h"
#include "interaction-func/pairwise/step-continuous/vec-name.h"
#include "basic/tanh.h"

namespace mysimulator {

  template <typename T,typename GT>
  class InteractionFuncPairwiseStepContinuous
      : public InteractionFuncPairwise<T,GT> {

    public:

      typedef InteractionFuncPairwiseStepContinuous<T,GT>   Type;
      typedef InteractionFuncPairwise<T,GT> ParentType;

      InteractionFuncPairwiseStepContinuous() : ParentType() {}
      virtual ~InteractionFuncPairwiseStepContinuous() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=StepContinuous;
        this->_pre.Allocate(StepContinuousNumberPre);
        this->_post.Allocate(StepContinuousNumberPost);
        this->_tmvec.Allocate(StepContinuousNumberVec,dim);
      }

    protected:

      virtual
      void EFunc(const InteractionParameter<T>* P,T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd2=this->_post[StepContinuousDistSQ]-
              Value<T>((*P)[StepContinuousRadiusSQ]);
        T SD2=Value<T>((*P)[StepContinuousSharpness])*Dd2;
        *Func=Value<T>((*P)[StepContinuousHalfDepth])*(1+_Tanh(SD2));
      }

      virtual
      void GFunc(const InteractionParameter<T>* P,T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd2=this->_post[StepContinuousDistSQ]-
              Value<T>((*P)[StepContinuousRadiusSQ]);
        T SD2=Value<T>((*P)[StepContinuousSharpness])*Dd2;
        T TH=_Tanh(SD2);
        *Diff=Value<T>((*P)[StepContinuousDepthSharp])*(1-TH*TH);
      }

      virtual
      void BFunc(const InteractionParameter<T>* P,T* Func,T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd2=this->_post[StepContinuousDistSQ]-
              Value<T>((*P)[StepContinuousRadiusSQ]);
        T SD2=Value<T>((*P)[StepContinuousSharpness])*Dd2;
        T TH=_Tanh(SD2);
        *Func=Value<T>((*P)[StepContinuousHalfDepth])*(1+TH);
        *Diff=Value<T>((*P)[StepContinuousDepthSharp])*(1-TH*TH);
      }

      virtual
      void Pre2Post4E(const InteractionParameter<T>* P) {
        this->_post[StepContinuousDistSQ]=this->_pre[PairwiseDistanceSQ];
        this->_update|=EGFuncUpdateOK;
      }
      virtual
      void Pre2Post4G(const InteractionParameter<T>* P) { Pre2Post4E(P); }
      virtual
      void Pre2Post4B(const InteractionParameter<T>* P) { Pre2Post4E(P); }

    private:

      InteractionFuncPairwiseStepContinuous(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseStepContinuous<T,GT>& F) {
    typedef typename InteractionFuncPairwiseStepContinuous<T,GT>::ParentType
                     PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename T2,typename GT1,typename GT2>
  void Clear(InteractionFuncPairwiseStepContinuous<T1,GT1>& F,
             const InteractionFuncPairwiseStepContinuous<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseStepContinuous<T1,GT1>::ParentType
                     PType1;
    typedef typename InteractionFuncPairwiseStepContinuous<T2,GT2>::ParentType
                     PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

