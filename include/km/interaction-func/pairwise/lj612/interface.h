
#ifndef _Interaction_Func_Pairwise_LJ612_Interface_H_
#define _Interaction_Func_Pairwise_LJ612_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/lj612/pre-name.h"
#include "interaction-func/pairwise/lj612/post-name.h"
#include "interaction-func/pairwise/lj612/vec-name.h"
#include "interaction-parameter/interface.h"
#include "interaction-parameter/lj612/name.h"

namespace mysimulator {

  template <typename T,typename GT> class InteractionFuncPairwiseLJ612Cut;

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseLJ612
    : public InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseLJ612<T,GeomType>  Type;
      typedef InteractionFuncPairwise<T,GeomType>   ParentType;
      template <typename T1,typename GT>
      friend class InteractionFuncPairwiseLJ612Cut;

      InteractionFuncPairwiseLJ612() : ParentType() {}
      virtual ~InteractionFuncPairwiseLJ612() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=LJ612;
        this->_pre.Allocate(LJ612NumberPre);
        this->_post.Allocate(LJ612NumberPost);
        this->_tmvec.Allocate(LJ612NumberVec,dim);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=this->_post[LJ612IvDistance6];
        *Func=tmd*(Value<T>((*P)[LJ612FactorA])*tmd-
                   Value<T>((*P)[LJ612FactorB]));
      }
      virtual void GFunc(const InteractionParameter<T>* P, T *Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=this->_post[LJ612IvDistance6];
        *Diff=tmd*this->_post[LJ612IvDistanceSQ]*
              (Value<T>((*P)[LJ612DiffFactorB])-
               Value<T>((*P)[LJ612DiffFactorA])*tmd);
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=this->_post[LJ612IvDistance6];
        *Func=tmd*(Value<T>((*P)[LJ612FactorA])*tmd-
                   Value<T>((*P)[LJ612FactorB]));
        *Diff=tmd*this->_post[LJ612IvDistanceSQ]*
              (Value<T>((*P)[LJ612DiffFactorB])-
               Value<T>((*P)[LJ612DiffFactorA])*tmd);
      }
      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        T tmd=1./this->_pre[PairwiseDistanceSQ];
        this->_post[LJ612IvDistance6]=tmd*tmd*tmd;
        this->_update=true;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        T tmd=1./this->_pre[PairwiseDistanceSQ];
        this->_post[LJ612IvDistanceSQ]=tmd;
        this->_post[LJ612IvDistance6]=tmd*tmd*tmd;
        this->_update=false;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4G(P);
      }

    private:

      InteractionFuncPairwiseLJ612(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseLJ612<T,GT>& F) {
    typedef typename InteractionFuncPairwiseLJ612<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncPairwiseLJ612<T1,GT1>& F,
             const InteractionFuncPairwiseLJ612<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseLJ612<T1,GT1>::ParentType PType1;
    typedef typename InteractionFuncPairwiseLJ612<T2,GT2>::ParentType PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

