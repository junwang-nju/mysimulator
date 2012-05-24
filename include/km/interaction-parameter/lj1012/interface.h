
#ifndef _Interaction_Parameter_LJ1012_Interface_H_
#define _Interaction_Parameter_LJ1012_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/lj1012/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterLJ1012 : public InteractionParameter<T> {

    public:

      typedef InteractionParameterLJ1012<T> Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterLJ1012() : ParentType() {}
      ~InteractionParameterLJ1012() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=LJ1012;
        this->_data.Allocate(LJ1012NumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=LJ1012NumberParameter);
        T tmd=Value<T>(this->_data[LJ1012EqRadius]);
        tmd*=tmd;
        T tmd1=tmd*tmd;
        T tmd2=tmd1*tmd1*Value<T>(this->_data[LJ1012EqEnergyDepth]);
        T A=tmd2*tmd1*5;
        T B=tmd2*tmd*6;
        Value<T>(this->_data[LJ1012FactorA])=A;
        Value<T>(this->_data[LJ1012FactorB])=B;
        Value<T>(this->_data[LJ1012DiffFactorA])=A*12;
        Value<T>(this->_data[LJ1012DiffFactorB])=B*10;
      }

    private:

      InteractionParameterLJ1012(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterLJ1012<T>& P) {
    typedef typename InteractionParameterLJ1012<T>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterLJ1012<T>& P,
             const InteractionParameterLJ1012<T>& BP) {
    typedef typename InteractionParameterLJ1012<T>::ParentType  PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

