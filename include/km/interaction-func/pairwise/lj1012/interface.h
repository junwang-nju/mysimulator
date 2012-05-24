
#ifndef _Interaction_Func_Pairwise_LJ1012_Interface_H_
#define _Interaction_Func_Pairwise_LJ1012_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/lj1012/pre-name.h"
#include "interaction-func/pairwise/lj1012/post-name.h"
#include "interaction-func/pairwise/lj1012/vec-name.h"
#include "interaction-parameter/interface.h"
#include "interaction-parameter/lj1012/name.h"

namespace mysimulator {

  template <typename T,typename GT> class InteractionFuncPairwiseLJ1012Cut;

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseLJ1012
      : public InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseLJ1012<T,GeomType> Type;
      typedef InteractionFuncPairwise<T,GeomType>  ParentType;
      template <typename T1,typename GT>
      friend class InteractionFuncPairwiseLJ1012Cut;

      InteractionFuncPairwiseLJ1012() : ParentType() {}
      virtual ~InteractionFuncPairwiseLJ1012() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=LJ1012;
        this->_pre.Allocate(LJ1012NumberPre);
        this->_post.Allocate(LJ1012NumberPost);
        this->_tmvec.Allocate(LJ1012NumberVec,dim);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        *Func=this->_post[LJ1012IvDistance10]*
              (Value<T>((*P)[LJ1012FactorA])*this->_post[LJ1012IvDistanceSQ]-
               Value<T>((*P)[LJ1012FactorB]));
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd=this->_post[LJ1012IvDistanceSQ];
        *Diff=this->_post[LJ1012IvDistance10]*tmd*
              (Value<T>((*P)[LJ1012DiffFactorA])*tmd-
               Value<T>((*P)[LJ1012DiffFactorB]));
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T tmd1=this->_post[LJ1012IvDistanceSQ];
        T tmd2=this->_post[LJ1012IvDistance10];
        *Func=tmd2*(Value<T>((*P)[LJ1012FactorA])*tmd1-
                    Value<T>((*P)[LJ1012FactorB]));
        *Diff=tmd2*tmd1*(Value<T>((*P)[LJ1012DiffFactorA])*tmd1-
                         Value<T>((*P)[LJ1012DiffFactorB]));
      }

      void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        T tmd=1./this->_pre[PairwiseDistanceSQ];
        this->_post[LJ1012IvDistanceSQ]=tmd;
        T tmd1=tmd*tmd;
        tmd1*=tmd1;
        this->_post[LJ1012IvDistance10]=tmd1*tmd;
        this->_update=false;
      }
      void Pre2Post4G(const InteractionParameter<T>* P) { Pre2Post4E(P); }
      void Pre2Post4B(const InteractionParameter<T>* P) { Pre2Post4E(P); }

    private:

      InteractionFuncPairwiseLJ1012(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseLJ1012<T,GT>& F) {
    typedef typename InteractionFuncPairwiseLJ1012<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncPairwiseLJ1012<T1,GT1>& F,
             const InteractionFuncPairwiseLJ1012<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseLJ1012<T1,GT1>::ParentType  PType1;
    typedef typename InteractionFuncPairwiseLJ1012<T2,GT2>::ParentType  PType2;
    _Copy(static_cast<PType1&>(F),static_cast<PType2&>(BF));
  }

}

#endif

