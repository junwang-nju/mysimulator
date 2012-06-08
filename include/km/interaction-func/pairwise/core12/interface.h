
#ifndef _Interaction_Func_Pairwise_Core12_Interface_H_
#define _Interaction_Func_Pairwise_Core12_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/core12/pre-name.h"
#include "interaction-func/pairwise/core12/vec-name.h"
#include "interaction-func/pairwise/core12/post-name.h"
#include "interaction-parameter/interface.h"
#include "interaction-parameter/core12/name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseCore12
      : public InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseCore12<T,GeomType>   Type;
      typedef InteractionFuncPairwise<T,GeomType>   ParentType;

      InteractionFuncPairwiseCore12() : ParentType() {}
      ~InteractionFuncPairwiseCore12() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=Core12;
        this->_pre.Allocate(Core12NumberPre);
        this->_post.Allocate(Core12NumberPost);
        this->_tmvec.Allocate(Core12NumberVec);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        *Func=Value<T>((*P)[Core12EqStrength])*this->_post[Core12IvDistance12];
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        *Diff=Value<T>((*P)[Core12TwlfEqStrength])*
              this->_post[Core12IvDistance12]*this->_post[Core12IvDistanceSQ];
      }
      virtual BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=Value<T>((*P)[Core12EqStrength])*this->_post[Core12IvDistance12];
        *Func=tmd;
        *Diff=tmd*this->_post[Core12IvDistanceSQ];
      }

      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=1./this->_pre[PairwiseDistanceSQ];
        tmd*=tmd;
        this->_post[Core12IvDistance12]=tmd*tmd*tmd;
        this->_update=true;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=1./this->_pre[PairwiseDistanceSQ];
        this->_post[Core12IvDistanceSQ]=tmd;
        tmd*=tmd;
        this->_post[Core12IvDistance12]=tmd*tmd*tmd;
        this->_update=false;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4G(P);
      }

    private:

      InteractionFuncPairwiseCore12(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseCore12<T,GT>& F) {
    typedef typename InteractionFuncPairwiseCore12<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncPairwiseCore12<T1,GT1>& F,
             const InteractionFuncPairwiseCore12<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseCore12<T1,GT1>::ParentType  PType1;
    typedef typename InteractionFuncPairwiseCore12<T2,GT2>::ParentType  PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

