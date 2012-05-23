
#ifndef _Interaction_Parameter_Coulomb_Interface_H_
#define _Interaction_Parameter_Coulomb_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/coulomb/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterCoulomb : public InteractionParameter<T> {

    public:

      typedef InteractionParameterCoulomb<T> Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterCoulomb() : ParentType() {}
      ~InteractionParameterCoulomb() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=Coulomb;
        this->_data.Allocate(CoulombNumberParameter); }
      virtual void Build() {
        Value<T>(this->_data[CoulombStrength])=
          Value<T>(this->_data[CoulombChargeA])*
          Value<T>(this->_data[CoulombChargeB])*
          Value<T>(this->_data[CoulombDielectric]);
      }

    private:

      InteractionParameterCoulomb(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterCoulomb<T>& P) {
    typedef typename InteractionParameterCoulomb<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterCoulomb<T>& P,
             const InteractionParameterCoulomb<T>& BP) {
    typedef typename InteractionParameterCoulomb<T>::ParentType PType;
    static_cast<PType&>(P).Copy(static_cast<const PType&>(BP));
  }

}

#endif

