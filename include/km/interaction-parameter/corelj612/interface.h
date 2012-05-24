
#ifndef _Interaction_Parameter_CoreLJ612_Interface_H_
#define _Interaction_Parameter_CoreLJ612_Interface_H_

#include "interaction-parameter/lj612/interface.h"
#include "interaction-parameter/corelj612/name.h"
#include "basic/norm-square.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterCoreLJ612 : public InteractionParameterLJ612<T> {

    public:

      typedef InteractionParameterCoreLJ612<T>    Type;
      typedef InteractionParameterLJ612<T>        ParentType;

      InteractionParameterCoreLJ612() : ParentType() {}
      ~InteractionParameterCoreLJ612() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=CoreLJ612;
        this->_data.Allocate(CoreLJ612NumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=CoreLJ612NumberParameter);
        static_cast<ParentType*>(this)->Build();
        Value<T>(this->_data[CoreLJ612RadiusSQ])=
          _NormSQ(Value<T>(this->_data[CoreLJ612Radius]));
      }

    private:

      InteractionParameterCoreLJ612(const Type&) { return *this; }
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterCoreLJ612<T>& P) {
    typedef typename InteractionParameterCoreLJ612<T>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterCoreLJ612<T>& P,
             const InteractionParameterCoreLJ612<T>& BP) {
    typedef typename InteractionParameterCoreLJ612<T>::ParentType  PType;
    static_cast<PType&>(P).Copy(static_cast<const PType&>(BP));
  }

}

#endif

