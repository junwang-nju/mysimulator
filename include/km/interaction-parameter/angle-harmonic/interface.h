
#ifndef _Interaction_Parameter_AngleHarmonic_Interface_H_
#define _Interaction_Parameter_AngleHarmonic_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/angle-harmonic/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterAngleHarmonic : public InteractionParameter<T> {

    public:

      typedef InteractionParameterAngleHarmonic<T>  Type;
      typedef InteractionParameter<T> ParentType;

      InteractionParameterAngleHarmonic() : ParentType() {}
      virtual ~InteractionParameterAngleHarmonic() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=AngleHarmonic;
        this->_data.Allocate(AngleHarmonicNumberParameter);
      }
      virtual void Build() {
        Value<T>(this->_data[AngleHarmonicDualStrength])=
          2*Value<T>(this->_data[AngleHarmonicStrength]);
      }

    private:

      InteractionParameterAngleHarmonic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterAngleHarmonic<T>& P) {
    typedef typename InteractionParameterAngleHarmonic<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterAngleHarmonic<T>& P,
             const InteractionParameterAngleHarmonic<T>& BP) {
    typedef typename InteractionParameterAngleHarmonic<T>::ParentType PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

