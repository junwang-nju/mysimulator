
#ifndef _Interaction_Parameter_DistCoulomb_Interface_H_
#define _Interaction_Parameter_DistCoulomb_Interface_H_

#include "interaction-parameter/coulomb/interface.h"
#include "interaction-parameter/dist-coulomb/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterDistDielCoulomb
    : public InteractionParameterCoulomb<T> {

    public:

      typedef InteractionParameterDistDielCoulomb<T>  Type;
      typedef InteractionParameterCoulomb<T>  ParentType;

      InteractionParameterDistDielCoulomb() : ParentType() {}
      ~InteractionParameterDistDielCoulomb() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=DistDielCoulomb;
        this->_data.Allocate(DistDielCoulombNumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=DistDielCoulombNumberParameter);
        static_cast<ParentType*>(this)->Build();
        Value<T>(this->_data[DistDielCoulombDualStrength])=
          2*Value<T>(this->_data[DistDielCoulombStrength]);
      }

    private:

      InteractionParameterDistDielCoulomb(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterDistDielCoulomb<T>& P) {
    typedef typename InteractionParameterDistDielCoulomb<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterDistDielCoulomb<T>& P,
             const InteractionParameterDistDielCoulomb<T>& BP) {
    typedef typename InteractionParameterDistDielCoulomb<T>::ParentType PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

