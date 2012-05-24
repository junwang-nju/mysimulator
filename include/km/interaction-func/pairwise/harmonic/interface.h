
#ifndef _Interaction_Func_Pairwise_Harmonic_Interface_H_
#define _Interaction_Func_Pairwise_Harmonic_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/harmonic/post-name.h"
#include "interaction-func/pairwise/harmonic/pre-name.h"
#include "interaction-func/pairwise/harmonic/vec-name.h"
#include "interaction-parameter/interface.h"
#include "interaction-parameter/harmonic/name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseHarmonic
    : public InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseHarmonic<T,GeomType>   Type;
      typedef InteractionFuncPairwise<T,GeomType>   ParentType;

      InteractionFuncPairwiseHarmonic() : ParentType() {}
      ~InteractionFuncPairwiseHarmonic() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=Harmonic;
        this->_pre.Allocate(PairwiseNumberPre);
        this->_post.Allocate(HarmonicNumberPost);
        this->_tmvec.Allocate(HarmonicNumberVec,dim);
      }

    protected:

      virtual
      void EFunc(const InteractionParameter<T>* P,T* Func) {
        T Dd=this->_post[HarmonicLength]-Value<T>((*P)[HarmonicEqLength]);
        *Func=Value<T>((*P)[HarmonicEqStrength])*Dd*Dd;
      }
      virtual
      void GFunc(const InteractionParameter<T>* P,T* Diff) {
        T Dd=1.-Value<T>((*P)[HarmonicEqLength])*this->_post[HarmonicIvLength];
        *Diff=Value<T>((*P)[HarmonicDualEqStrength])*Dd;
      }
      virtual
      void BFunc(const InteractionParameter<T>* P,T* Func,T* Diff) {
        T Dd=this->_post[HarmonicLength]-Value<T>((*P)[HarmonicEqLength]);
        T tmd=Value<T>((*P)[HarmonicEqStrength])*Dd;
        *Func=tmd*Dd;
        *Diff=(tmd+tmd)*this->_post[HarmonicIvLength];
      }
      virtual
      void Pre2Post4E(const InteractionParameter<T>* P) {
        this->_post[HarmonicLength]=__SqRoot(this->_pre[PairwiseDistanceSQ]);
        this->_update=true;
      }
      virtual
      void Pre2Post4G(const InteractionParameter<T>* P) {
        this->_post[HarmonicIvLength]=
          1./__SqRoot(this->_pre[PairwiseDistanceSQ]);
        this->_update=true;
      }
      virtual
      void Pre2Post4B(const InteractionParameter<T>* P) {
        T tmd=__SqRoot(this->_pre[PairwiseDistanceSQ]);
        this->_post[HarmonicLength]=tmd;
        this->_post[HarmonicIvLength]=1./tmd;
        this->_update=false;
      }

    private:

      InteractionFuncPairwiseHarmonic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseHarmonic<T,GT>& F) {
    typedef typename InteractionFuncPairwiseHarmonic<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T,typename GT>
  void _Copy(InteractionFuncPairwiseHarmonic<T,GT>& F,
             const InteractionFuncPairwiseHarmonic<T,GT>& BF) {
    typedef typename InteractionFuncPairwiseHarmonic<T,GT>::ParentType  PType;
    static_cast<PType&>(F).Copy(static_cast<const PType&>(BF));
  }

}

#endif

