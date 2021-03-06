
#ifndef _Interaction_Func_Pairwise_Harmonic_Interface_H_
#define _Interaction_Func_Pairwise_Harmonic_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/harmonic/post-name.h"
#include "interaction-func/pairwise/harmonic/pre-name.h"
#include "interaction-func/pairwise/harmonic/vec-name.h"
#include "interaction-parameter/harmonic/name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseHarmonic
    : public InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseHarmonic<T,GeomType>   Type;
      typedef InteractionFuncPairwise<T,GeomType>   ParentType;

      InteractionFuncPairwiseHarmonic() : ParentType() {}
      virtual ~InteractionFuncPairwiseHarmonic() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=Harmonic;
        this->_pre.Allocate(HarmonicNumberPre);
        this->_post.Allocate(HarmonicNumberPost);
        this->_tmvec.Allocate(HarmonicNumberVec,dim);
      }

    protected:

      virtual
      void EFunc(const InteractionParameter<T>* P,T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd=this->_post[HarmonicLength]-Value<T>((*P)[HarmonicEqLength]);
        *Func=Value<T>((*P)[HarmonicEqStrength])*Dd*Dd;
      }
      virtual
      void GFunc(const InteractionParameter<T>* P,T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd=1.-Value<T>((*P)[HarmonicEqLength])*this->_post[HarmonicIvLength];
        *Diff=Value<T>((*P)[HarmonicDualEqStrength])*Dd;
      }
      virtual
      void BFunc(const InteractionParameter<T>* P,T* Func,T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd=this->_post[HarmonicLength]-Value<T>((*P)[HarmonicEqLength]);
        T tmd=Value<T>((*P)[HarmonicEqStrength])*Dd;
        *Func=tmd*Dd;
        *Diff=(tmd+tmd)*this->_post[HarmonicIvLength];
      }
      virtual
      void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        this->_post[HarmonicLength]=__SqRoot(this->_pre[PairwiseDistanceSQ]);
        this->_update|=EFuncUpdateOK;
      }
      virtual
      void Pre2Post4G(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        this->_post[HarmonicIvLength]=
          1./__SqRoot(this->_pre[PairwiseDistanceSQ]);
        this->_update|=GFuncUpdateOK;
      }
      virtual
      void Pre2Post4B(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=__SqRoot(this->_pre[PairwiseDistanceSQ]);
        this->_post[HarmonicLength]=tmd;
        this->_post[HarmonicIvLength]=1./tmd;
        this->_update|=EGFuncUpdateOK;
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

  template <typename T1,typename T2,typename GT1,typename GT2>
  void _Copy(InteractionFuncPairwiseHarmonic<T1,GT1>& F,
             const InteractionFuncPairwiseHarmonic<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseHarmonic<T1,GT1>::ParentType PType1;
    typedef typename InteractionFuncPairwiseHarmonic<T2,GT2>::ParentType PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

