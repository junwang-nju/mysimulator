
#ifndef _Interaction_Func_Pairwise_LJ612Cut_Interface_H_
#define _Interaction_Func_Pairwise_LJ612Cut_Interface_H_

#include "interaction-func/pairwise/lj612cut/pre-name.h"
#include "interaction-func/pairwise/lj612cut/vec-name.h"
#include "interaction-func/pairwise/lj612cut/post-name.h"
#include "interaction-func/pairwise/lj612/interface.h"
#include "interaction-parameter/lj612cut/name.h"

namespace mysimulator {

  template <typename T, typename GeomType>
  class InteractionFuncPairwiseLJ612Cut
      : public InteractionFuncPairwiseLJ612<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseLJ612Cut<T,GeomType> Type;
      typedef InteractionFuncPairwiseLJ612<T,GeomType>  ParentType;

      InteractionFuncPairwiseLJ612Cut() : ParentType() {}
      ~InteractionFuncPairwiseLJ612Cut() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        this->_tag=LJ612Cut;
        this->_pre.Allocate(LJ612CutNumberPre);
        this->_post.Allocate(LJ612CutNumberPost);
        this->_vec.Allocate(LJ612CutNumberVec);
      }

    protected:

      virtual void EFunc(InteractionParameter<T>* P, T* Func) {
        if(this->_Post[LJ612CutDistanceSQ]>Value<T>((*P)[LJ612CutCutRSQ]))
          *Func=0;
        else {
          static_cast<ParentType*>(this)->EFunc(P,Func);
          (*Func)-=Value<T>((*P)[LJ612CutVc]);
          (*Func)-=Value<T>((*P)[LJ612CutKc])*
                   (this->_post[LJ612CutDistance]-Value<T>((*P)[LJ612CutCutR]));
        }
      }
      virtual void GFunc(InteractionParameter<T>* P, T* Diff) {
        if(this->_Post[LJ612CutDistanceSQ]>Value<T>((*P)[LJ612CutCutRSQ]))
          *Diff=0;
        else {
          static_cast<ParentType*>(this)->GFunc(P,Diff);
          (*Diff)-=Value<T>((*P)[LJ612CutKc])*this->_post[LJ612CutIvDistance];
        }
      }
      virtual void BFunc(InteractionParameter<T>* P, T* Func, T* Diff) {
        if(this->_Post[LJ612CutDistanceSQ]>Value<T>((*P)[LJ612CutCutRSQ])) {
          *Func=0;
          *Diff=0;
        } else {
          static_cast<ParentType*>(this)->BFunc(P,Func,Diff);
          (*Func)-=Value<T>((*P)[LJ612CutVc]);
          (*Func)-=Value<T>((*P)[LJ612CutKc])*
                   (this->_post[LJ612CutDistance]-Value<T>((*P)[LJ612CutCutR]));
          (*Diff)-=Value<T>((*P)[LJ612CutKc])*this->_post[LJ612CutIvDistance];
        }
      }

      virtual void Pre2Post2E(const InteractionParameter<T>* P) {
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[LJ612CutDistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[LJ612CutCutRSQ])) {
          this->_post[LJ612CutDistance]=__SqRoot(tmd);
          static_cast<ParentType*>(this)->Pre2Post2E(P);
        } else this->_update=false;
      }
      virtual void Pre2Post2G(const InteractionParameter<T>* P) {
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[LJ612CutDistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[LJ612CutCutRSQ])) {
          static_cast<ParentType*>(this)->Pre2Post2G(P);
          this->_post[LJ612CutIvDistance]=
            __SqRoot(this->_post[LJ612CutIvDistanceSQ]);
          flag=true;
        } else this->_update=false;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        T tmd=this->_pre[PairwiseDistanceSQ];
        this->_post[LJ612CutDistanceSQ]=tmd;
        if(tmd<Value<T>((*P)[LJ612CutCutRSQ])) {
          static_cast<ParentType*>(this)->Pre2Post4B(P);
          this->_post[LJ612CutDistance]=__SqRoot(tmd);
          this->_post[LJ612CutIvDistance]=this->_post[LJ612CutDistance]*
                                          this->_post[LJ612CutIvDistanceSQ];
        } else flag=false;
      }

    private:

      InteractionFuncPairwiseLJ612Cut(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseLJ612Cut<T,GT>& F) {
    typedef typename InteractionFuncPairwiseLJ612Cut<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncPairwiseLJ612Cut<T1,GT1>& F,
             const InteractionFuncPairwiseLJ612Cut<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwiseLJ612Cut<T1,GT1>::ParentType PType1;
    typedef typename InteractionFuncPairwiseLJ612Cut<T2,GT2>::ParentType PType2;
    _Copy(static_cast<PType&>(F),static_cast<const PType&>(BF));
  }

}

#endif

