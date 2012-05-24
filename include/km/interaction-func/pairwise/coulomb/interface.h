
#ifndef _Interaction_Func_Pairwise_Coulomb_Interface_H_
#define _Interaction_Func_Pairwise_Coulomb_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/coulomb/pre-name.h"
#include "interaction-func/pairwise/coulomb/vec-name.h"
#include "interaction-func/pairwise/coulomb/post-name.h"
#include "interaction-parameter/interface.h"
#include "interaction-parameter/coulomb/name.h"

namespace mysimulator {

  template <typename T, typename GeomType>
  class InteractionFuncPairwiseCoulomb
      : InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseCoulomb<T,GeomType>  Type;
      typedef InteractionFuncPairwise<T,GeomType>   ParentType;

      InteractionFuncPairwiseCoulomb() : ParentType() {}
      ~InteractionFuncPairwiseCoulomb() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        this->_tag=Coulomb;
        this->_pre.Allocate(CoulombNumberPre);
        this->_post.Allocate(CoulombNumberPost);
        this->_post.Allocate(CoulombNumberVec,dim);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        *Func=Value<T>((*P)[CoulombStrength])*this->_post[CoulombIvDistance];
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        *Diff=Value<T>((*P)[CoulombStrength])*this->_post[CoulombIvDistanceSQ]*
              this->_post[CoulombIvDistance];
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        EFunc(P,Func);
        *Diff=(*Func)*this->_post[CoulombIvDistance];
      }

      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
        this->_post[CoulombIvDistance]=
          1./__SqRoot(this->_pre[PairwiseDistanceSQ]);
        this->_update=true;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>* P) {
        T tmd=1./this->_pre[PairwiseDistanceSQ];
        this->_post[CoulombIvDistanceSQ]=tmd;
        this->_post[CoulombIvDistance]=__SqRoot(tmd);
        this->_update=false;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4G(P);
      }

    private:

      InteractionFuncPairwiseCoulomb(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseCoulomb<T,GT>& F) {
    typedef typename InteractionFuncPairwiseCoulomb<T,GT>::ParentType Type;
    Clear(static_cast<PType&>(F));
  }

  template <typename T,typename GT>
  void _Copy(InteractionFuncPairwiseCoulomb<T,GT>& F,
             const InteractionFuncPairwiseCoulomb<T,GT>& BF) {
    typedef typename InteractionFuncPairwiseCoulomb<T,GT>::ParentType Type;
    _Copy(static_cast<PType&>(F),static_cast<const PType&>(BF));
  }

}

#endif

