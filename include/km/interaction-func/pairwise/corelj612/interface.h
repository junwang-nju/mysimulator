
#ifndef _Interaction_Func_Pairwise_CoreLJ612_Interface_H_
#define _Interaction_Func_Pairwise_CoreLJ612_Interface_H_

#include "interaction-func/pairwise/corelj612/pre-name.h"
#include "interaction-func/pairwise/corelj612/vec-name.h"
#include "interaction-func/pairwise/corelj612/post-name.h"
#include "interaction-func/pairwise/lj612/interface.h"
#include "interaction-parameter/corelj612/name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseCoreLJ612
      : public InteractionFuncPairwiseLJ612<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseCoreLJ612<T,GeomType>  Type;
      typedef InteractionFuncPairwiseLJ612<T,GeomType>  ParentType;

      InteractionFuncPairwiseCoreLJ612() : ParentType() {}
      virtual ~InteractionFuncPairwiseCoreLJ612() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=CoreLJ612;
        this->_pre.Allocate(CoreLJ612NumberPre);
        this->_post.Allocate(CoreLJ612NumberPost);
        this->_vec.Allocate(CoreLJ612NumberVec,dim);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        if(this->_post[CoreLJ612DistanceSQ]>Value<T>((*P)[CoreLJ612RadiusSQ]))
          *Func=0;
        else {
          static_cast<ParentType*>(this)->EFunc(P,Func);
          (*Func)+=Value<T>((*P)[CoreLJ612EnergyDepth]);
        }
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        if(this->_post[CoreLJ612DistanceSQ]>Value<T>((*P)[CoreLJ612RadiusSQ]))
          *Diff=0;
        else
          static_cast<ParentType*>(this)->GFunc(P,Diff);
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        if(this->_post[CoreLJ612DistanceSQ]>Value<T>((*P)[CoreLJ612RadiusSQ])) {
          *Func=0;
          *Diff=0;
        } else {
          static_cast<ParentType*>(this)->BFunc(P,Func,Diff);
          (*Func)+=Value<T>((*P)[CoreLJ612EnergyDepth]);
        }
      }

      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[CoreLJ612DistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[CoreLJ612RadiusSQ]))
          static_cast<ParentType*>(this)->Pre2Post4E(P);
        else
          this->_update=false;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[CoreLJ612DistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[CoreLJ612RadiusSQ]))
          static_cast<ParentType*>(this)->Pre2Post4G(P);
        else
          this->_update=false;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4G(P);
      }

    private:

      InteractionFuncPairwiseCoreLJ612(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseCoreLJ612<T,GT>& F) {
    typedef typename InteractionFuncPairwiseCoreLJ612<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncPairwiseCoreLJ612<T1,GT1>& F,
             const InteractionFuncPairwiseCoreLJ612<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseCoreLJ612<T1,GT1>::ParentType
                     PType1;
    typedef typename InteractionFuncPairwiseCoreLJ612<T2,GT2>::ParentType
                     PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

