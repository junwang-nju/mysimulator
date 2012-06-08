
#ifndef _Interaction_Parameter_LJ612_Interface_H_
#define _Interaction_Parameter_LJ612_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/lj612/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterLJ612 : public InteractionParameter<T> {

    public:

      typedef InteractionParameterLJ612<T>    Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterLJ612() : ParentType() {}
      virtual ~InteractionParameterLJ612() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=LJ612;
        this->_data.Allocate(LJ612NumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=LJ612NumberParameter);
        T tmd=Value<T>(this->_data[LJ612EqRadius]);
        tmd*=tmd;
        T tmd1=tmd*tmd*tmd;
        tmd=tmd1*Value<T>(this->_data[LJ612EqEnergyDepth]);
        T A=tmd*tmd1;
        T B=tmd+tmd;
        Value<T>(this->_data[LJ612FactorA])=A;
        Value<T>(this->_data[LJ612FactorB])=B;
        Value<T>(this->_data[LJ612DiffFactorA])=12*A;
        Value<T>(this->_data[LJ612DiffFactorB])=6*B;
      }

    private:

      InteractionParameterLJ612(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterLJ612<T>& P) {
    typedef typename InteractionParameterLJ612<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterLJ612<T>& P,
             const InteractionParameterLJ612<T>& BP) {
    typedef typename InteractionParameterLJ612<T>::ParentType PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

