
#ifndef _Interaction_Parameter_Core12_Interface_H_
#define _Interaction_Parameter_Core12_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/core12/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterCore12 : public InteractionParameter<T> {

    public:

      typedef InteractionParameterCore12<T>   Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterCore12() : ParentType() {}
      virtual ~InteractionParameterCore12() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=Core12;
        this->_data.Allocate(Core12NumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=Core12NumberParameter);
        Value<T>(this->_data[Core12TwlfEqStrength])=
          12*Value<T>(this->_data[Core12EqStrength]);
      }

    private:

      InteractionParameterCore12(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterCore12<T>& P) {
    typedef typename InteractionParameterCore12<T>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterCore12<T>& P,
             const InteractionParameterCore12<T>& BP) {
    typedef typename InteractionParameterCore12<T>::ParentType  PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

