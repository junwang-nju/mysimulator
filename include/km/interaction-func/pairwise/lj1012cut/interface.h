
#ifndef _Interaction_Func_Pairwise_LJ1012Cut_Interface_H_
#define _Interaction_Func_Pairwise_LJ1012Cut_Interface_H_

#include "interaction-func/pairwise/lj1012cut/pre-name.h"
#include "interaction-func/pairwise/lj1012cut/post-name.h"
#include "interaction-func/pairwise/lj1012cut/vec-name.h"
#include "interaction-func/pairwise/lj1012/interface.h"
#include "interaction-parameter/lj1012cut/name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseLJ1012Cut
      : public InteractionFuncPairwiseLJ1012<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseLJ1012Cut<T,GeomType>    Type;
      typedef InteractionFuncPairwiseLJ1012<T,GeomType>   ParentType;

      InteractionFuncPairwiseLJ1012Cut() : ParentType() {}
      virtual ~InteractionFuncPairwiseLJ1012Cut() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=LJ1012Cut;
        this->_pre.Allocate(LJ1012CutNumberPre);
        this->_post.Allocate(LJ1012CutNumberPost);
        this->_tmvec.Allocate(LJ1012CutNumberVec,dim);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        if(this->_post[LJ1012CutDistanceSQ]>Value<T>((*P)[LJ1012CutCutRSQ]))
          *Func=0;
        else {
          ParentType::EFunc(P,Func);
          (*Func)-=Value<T>((*P)[LJ1012CutVc]);
          (*Func)-=Value<T>((*P)[LJ1012CutKc])*
                   (this->_post[LJ1012CutDistance]-
                    Value<T>((*P)[LJ1012CutCutR]));
        }
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        if(this->_post[LJ1012CutDistanceSQ]>Value<T>((*P)[LJ1012CutCutRSQ]))
          *Diff=0;
        else {
          ParentType::GFunc(P,Diff);
          (*Diff)-=Value<T>((*P)[LJ1012CutKc])*this->_post[LJ1012CutIvDistance];
        }
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        if(this->_post[LJ1012CutDistanceSQ]>Value<T>((*P)[LJ1012CutCutRSQ])) {
          *Func=0;
          *Diff=0;
        } else {
          ParentType::BFunc(P,Func,Diff);
          (*Func)-=Value<T>((*P)[LJ1012CutVc]);
          (*Func)-=Value<T>((*P)[LJ1012CutKc])*
                   (this->_post[LJ1012CutDistance]-
                    Value<T>((*P)[LJ1012CutCutR]));
          (*Diff)-=Value<T>((*P)[LJ1012CutKc])*this->_post[LJ1012CutIvDistance];
        }
      }

      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        InteractionFuncUpdateName IUN=this->_update;
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[LJ1012CutDistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[LJ1012CutCutRSQ])) {
          ParentType::Pre2Post4E(P);
          this->_post[LJ1012CutDistance]=__SqRoot(tmd);
          this->_update=IUN|EFuncUpdateOK;
        } else this->_update=IUN|EGFuncUpdateOK;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        InteractionFuncUpdateName IUN=this->_update;
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[LJ1012CutDistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[LJ1012CutCutRSQ])) {
          ParentType::Pre2Post4G(P);
          this->_post[LJ1012CutIvDistance]=
            __SqRoot(this->_post[LJ1012CutIvDistanceSQ]);
          this->_update=IUN|GFuncUpdateOK;
        } else this->_update=IUN|EGFuncUpdateOK;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        InteractionFuncUpdateName IUN=this->_update;
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[LJ1012CutDistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[LJ1012CutCutRSQ])) {
          ParentType::Pre2Post4B(P);
          this->_post[LJ1012CutDistance]=__SqRoot(tmd);
          this->_post[LJ1012CutIvDistance]=this->_post[LJ1012CutIvDistanceSQ]*
                                           this->_post[LJ1012CutDistance];
          this->_update=IUN|EGFuncUpdateOK;
        } else this->_update=IUN|EGFuncUpdateOK;
      }

    private:

      InteractionFuncPairwiseLJ1012Cut(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseLJ1012Cut<T,GT>& F) {
    typedef typename InteractionFuncPairwiseLJ1012Cut<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncPairwiseLJ1012Cut<T1,GT1>& F,
             const InteractionFuncPairwiseLJ1012Cut<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseLJ1012Cut<T1,GT1>::ParentType
                     PType1;
    typedef typename InteractionFuncPairwiseLJ1012Cut<T2,GT2>::ParentType
                     PType2;
    _Copy(static_cast<PType1&>(F),static_cast<PType2&>(BF));
  }

}

#endif

