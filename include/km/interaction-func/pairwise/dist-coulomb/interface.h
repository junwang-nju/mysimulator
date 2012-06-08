
#ifndef _Interaction_Func_Pairwise_DistCoulomb_Interface_H_
#define _Interaction_Func_Pairwise_DistCoulomb_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/dist-coulomb/pre-name.h"
#include "interaction-func/pairwise/dist-coulomb/post-name.h"
#include "interaction-func/pairwise/dist-coulomb/vec-name.h"
#include "interaction-parameter/interface.h"
#include "interaction-parameter/dist-coulomb/name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseDistDielCoulomb
      : public InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseDistDielCoulomb<T,GeomType>  Type;
      typedef InteractionFuncPairwise<T,GeomType>   ParentType;

      InteractionFuncPairwiseDistDielCoulomb() : ParentType() {}
      virtual ~InteractionFuncPairwiseDistDielCoulomb() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=DistDielCoulomb;
        this->_pre.Allocate(DistDielCoulombNumberPre);
        this->_post.Allocate(DistDielCoulombNumberPost);
        this->_tmvec.Allocate(DistDielCoulombNumberVec,dim);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        *Func=Value<T>((*P)[DistDielCoulombStrength])*
              this->_post[DistDielCoulombIvDistanceSQ];
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        *Diff=Value<T>((*P)[DistDielCoulombDualStrength])*
              _NormSQ(this->_post[DistDielCoulombIvDistanceSQ]);
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        EFunc(P,Func);
        *Diff=(*Func)*2*this->_post[DistDielCoulombIvDistanceSQ];
      }

      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        this->_post[DistDielCoulombIvDistanceSQ]=
          1./this->_pre[PairwiseDistanceSQ];
        this->_update=false;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>* P) {
        Pre2Post4E(P);
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4E(P);
      }

    private:

      InteractionFuncPairwiseDistDielCoulomb(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseDistDielCoulomb<T,GT>& F) {
    typedef typename InteractionFuncPairwiseDistDielCoulomb<T,GT>::ParentType
                     PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncPairwiseDistDielCoulomb<T1,GT1>& F,
             const InteractionFuncPairwiseDistDielCoulomb<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseDistDielCoulomb<T1,GT1>::ParentType
                     PType1;
    typedef typename InteractionFuncPairwiseDistDielCoulomb<T2,GT2>::ParentType
                     PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

