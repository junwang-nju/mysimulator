
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
      ~InteractionParameterLJ612() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=LJ612;
        this->_data.Allocate(LJ612NumberParameter);
      }
      virtual void Build() {
        assert(this->IsValid());
        T tmd=Value<T>(this->_data[LJ612EqRadius]);
        tmd*=tmd;
        T tmd1=tmd*tmd*tmd;
        tmd=tmd1*Value<T>(this->_data[LJ612EqEnergyDepth]);
        Value<T>(this->_data[LJ612FactorA])=tmd*tmd1;
        Value<T>(this->_data[LJ612FactorB])=tmd+tmd;
        tmd*=12;
        Value<T>(this->_data[LJ612DiffFactorA])=tmd*tmd1;
        Value<T>(this->_data[LJ612DiffFactorB])=tmd;
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
    static_cast<PType&>(P).Copy(static_cast<const PType&>(BP));
  }

}

#endif

