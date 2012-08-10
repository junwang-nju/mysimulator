
#ifndef _Interaction_Func_Wall_Harmonic_Interface_H_
#define _Interaction_Func_Wall_Harmonic_Interface_H_

#include "interaction-func/wall/interface.h"
#include "interaction-func/pairwise/harmonic/interface.h"
#include "interaction-func/wall/harmonic/pre-name.h"
#include "interaction-func/wall/harmonic/post-name.h"
#include "interaction-func/wall/harmonic/vec-name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncWallHarmonic
      : public InteractionFuncWall<T,GeomType,InteractionFuncPairwiseHarmonic> {

    public:

      typedef InteractionFuncWallHarmonic<T,GeomType>   Type;
      typedef InteractionFuncWall<T,GeomType,InteractionFuncPairwiseHarmonic>
              ParentType;

      InteractionFuncWallHarmonic() : ParentType() {}
      virtual ~InteractionFuncWallHarmonic() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=WallHarmonic;
        this->_pre.Allocate(WallHarmonicNumberPre);
        this->_post.Allocate(WallHarmonicNumberPost);
        this->_tmvec.Allocate(WallHarmonicNumberVec,dim);
      }

    protected:

      virtual
      void GFunc(const InteractionParameter<T>* P,T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd=this->_post[WallHarmonicLength]-Value<T>((*P)[HarmonicEqLength]);
        *Diff=Dd*Value<T>((*P)[HarmonicDualEqStrength]);
      }
      virtual
      void BFunc(const InteractionParameter<T>* P,T* Func, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T Dd=this->_post[WallHarmonicLength]-Value<T>((*P)[HarmonicEqLength]);
        T tmd=Dd*Value<T>((*P)[HarmonicEqStrength]);
        *Func=Dd*tmd;
        *Diff=tmd+tmd;
      }
      virtual
      void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        this->_post[WallHarmonicLength]=this->_pre[WallDistance];
        this->_update|=EGFuncUpdateOK;
      }
      virtual 
      void Pre2Post4G(const InteractionParameter<T>* P) { Pre2Post4E(P); }
      virtual 
      void Pre2Post4B(const InteractionParameter<T>* P) { Pre2Post4E(P); }

    private:

      InteractionFuncWallHarmonic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncWallHarmonic<T,GT>& F) {
    typedef typename InteractionFuncWallHarmonic<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

}

#endif

