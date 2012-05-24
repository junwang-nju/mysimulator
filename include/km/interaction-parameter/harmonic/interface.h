
#ifndef _Interaction_Parameter_Harmonic_Interface_H_
#define _Interaction_Parameter_Harmonic_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/harmonic/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterHarmonic : public InteractionParameter<T> {

    public:

      typedef InteractionParameterHarmonic<T>   Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterHarmonic() : ParentType() {}
      ~InteractionParameterHarmonic() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=Harmonic;
        this->_data.Allocate(HarmonicNumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=HarmonicNumberParameter);
        Value<T>(this->_data[HarmonicDualEqStrength])=
          2*Value<T>(this->_data[HarmonicEqStrength]);
      }

    private:

      InteractionParameterHarmonic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterHarmonic<T>& P) {
    typedef typename InteractionParameterHarmonic<T>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterHarmonic<T>& P,
             const InteractionParameterHarmonic<T>& BP) {
    typedef typename InteractionParameterHarmonic<T>::ParentType  PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

