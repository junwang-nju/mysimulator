
#ifndef _Interaction_Func_Angle_Harmonic_Interface_H_
#define _Interaction_Func_Angle_Harmonic_Interface_H_

#include "interaction-func/angle/interface.h"
#include "interaction-func/angle/harmonic/post-name.h"
#include "interaction-func/angle/harmonic/pre-name.h"
#include "interaction-func/angle/harmonic/vec-name.h"
#include "interaction-func/angle/harmonic/neighbor-name.h"
#include "basic/acos.h"

namespace mysimulator {

  template <typename T,typename GT>
  class InteractionFuncAngleHarmonic : public InteractionFuncAngle<T,GT> {

    public:

      typedef InteractionFuncAngleHarmonic<T,GT>  Type;
      typedef InteractionFuncAngle<T,GT> ParentType;

      InteractionFuncAngleHarmonic() : ParentType() {}
      virtual ~InteractionFuncAngleHarmonic() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=AngleHarmonic;
        this->_pre.Allocate(AngleHarmonicNumberPre);
        this->_post.Allocate(AngleHarmonicNumberPost);
        this->_tmvec.Allocate(AngleHarmonicNumberVec,dim);
        this->_neighbor.Allocate(AngleHarmonicNumberNeighbor);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        assert(this->IsValid());
        assert(P!=NULL);
        T dA=this->_post[AngleHarmonicValue]-
             Value<T>((*P)[AngleHarmonicEqAngle]);
        *Func=Value<T>((*P)[AngleHarmonicStrength])*dA*dA;
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T dA=this->_post[AngleHarmonicValue]-
             Value<T>((*P)[AngleHarmonicEqAngle]);
        *Diff=Value<T>((*P)[AngleHarmonicDualStrength])*dA;
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        assert(this->IsValid());
        assert(P!=NULL);
        T dA=this->_post[AngleHarmonicValue]-
             Value<T>((*P)[AngleHarmonicEqAngle]);
        T tmd=dA*Value<T>((*P)[AngleHarmonicStrength]);
        *Func=tmd*dA;
        *Diff=tmd+tmd;
      }

      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        ParentType::Pre2Post4E(P);
        this->_post[AngleHarmonicValue]=_ACos(this->_post[AngleCosine]);
      }
      virtual void Pre2Post4G(const InteractionParameter<T>* P) {
        assert(this->IsValid());
        assert(P!=NULL);
        ParentType::Pre2Post4G(P);
        this->_post[AngleHarmonicValue]=_ACos(this->_post[AngleCosine]);
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4G(P);
      }

    private:

      InteractionFuncAngleHarmonic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename GT>
  void Clear(InteractionFuncAngleHarmonic<T,GT>& F) {
    typedef typename InteractionFuncAngleHarmonic<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename T2,typename GT1,typename GT2>
  void _Copy(InteractionFuncAngleHarmonic<T1,GT1>& F,
             const InteractionFuncAngleHarmonic<T2,GT2>& BF) {
    typedef typename InteractionFuncAngleHarmonic<T1,GT1>::ParentType PType1;
    typedef typename InteractionFuncAngleHarmonic<T2,GT2>::ParentType PType2;
    _Copy(static_cast<PType1&>(F),static_cast<PType2&>(BF));
  }

}

#endif
