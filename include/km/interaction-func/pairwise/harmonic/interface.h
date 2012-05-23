
#ifndef _Interaction_Func_Pairwise_Harmonic_Interface_H_
#define _Interaction_Func_Pairwise_Harmonic_Interface_H_

#include "interaction-func/pairwise/interface.h"
#include "interaction-func/pairwise/harmonic/post-name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwiseHarmonic
    : public InteractionFuncPairwise<T,GeomType> {

    public:

      typedef InteractionFuncPairwiseHarmonic<T,GeomType>   Type;
      typedef InteractionFuncPairwise<T,GeomType>   ParentType;

      InteractionFuncPairwiseHarmonic() : ParentType() {}
      ~InteractionFuncPairwiseHarmonic() { Clear(*this); }

    protected:

      virtual
      void EFunc(const ArrayNumeric<T>& Post,const Array<Unique64Bit>& P,
                 T* Func) {
        T Dd=Post[HarmonicLength]-Value<T>(P[HarmonicEqLength]);
        *Func=Value<T>(P[HarmonicEqStrength])*Dd*Dd;
      }

    private:

      InteractionFuncPairwiseHarmonic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwiseHarmonic<T,GT>& F) {
    typedef typename InteractionFuncPairwiseHarmonic<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

}

#endif

