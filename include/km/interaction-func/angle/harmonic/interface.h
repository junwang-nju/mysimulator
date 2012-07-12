
#ifndef _Interaction_Func_Angle_Harmonic_Interface_H_
#define _Interaction_Func_Angle_Harmonic_Interface_H_

#include "interaction-func/angle/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  class InteractionFuncAngleHarmonic : public InteractionFuncAngle<T,GT> {

    public:

      typedef InteractionFuncAngleHarmonic<T,GT>  Type;
      typedef InteractionFuncAngle<T,GT> ParentType;

      InteractionFuncAngleHarmonic() : ParentType() {}
      virtual ~InteractionFuncAngleHarmonic() { Clear(*this); }

    protected:

      virtual void EFunc(const Array)

      virtual void Pre2Post4E(const InteractionParameter<T>* P) {
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

}

#endif
