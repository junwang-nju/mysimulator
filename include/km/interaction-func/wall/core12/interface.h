
#ifndef _Interaction_Func_Wall_Core12_Interface_H_
#define _Interaction_Func_Wall_Core12_Interface_H_

#include "interaction-func/wall/interface.h"
#include "interaction-func/pairwise/core12/interface.h"
#include "interaction-func/wall/core12/pre-name.h"
#include "interaction-func/wall/core12/post-name.h"
#include "interaction-func/wall/core12/vec-name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncWallCore12
      : public InteractionFuncWall<T,GeomType,InteractionFuncPairwiseCore12> {

    public:

      typedef InteractionFuncWallCore12<T,GeomType>   Type;
      typedef InteractionFuncWall<T,GeomType,InteractionFuncPairwiseCore12>
              ParentType;

      InteractionFuncWallCore12() : ParentType() {}
      virtual ~InteractionFuncWallCore12() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=WallCore12;
        this->_pre.Allocate(WallCore12NumberPre);
        this->_post.Allocate(WallCore12NumberPost);
        this->_tmvec.Allocate(WallCore12NumberVec,dim);
      }

    protected:

      virtual
      void GFunc(const InteractionParameter<T>* P,T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        *Diff=Value<T>((*P)[Core12TwlfEqStrength])*
              this->_post[WallCore12IvDistance13];
      }

      virtual
      void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        T tmd=1./this->_pre[WallDistance];
        tmd*=tmd;
        tmd*=tmd;
        this->_post[WallCore12IvDistance12]=tmd*tmd*tmd;
        this->_update|=EFuncUpdateOK;
      }
      virtual
      void Pre2Post4G(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        T tmd=1./this->_pre[WallDistance];
        T tmd1=tmd*tmd;
        tmd1*=tmd1;
        tmd1*=tmd1*tmd1;
        this->_post[WallCore12IvDistance12]=tmd1;
        this->_post[WallCore12IvDistance13]=tmd1*tmd;
        this->_update|=EGFuncUpdateOK;
      }

    private:

      InteractionFuncWallCore12(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncWallCore12<T,GT>& F) {
    typedef typename InteractionFuncWallCore12<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

}

#endif

