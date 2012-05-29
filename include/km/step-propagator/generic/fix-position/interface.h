
#ifndef _Step_Propagator_Generic_FixPosition_Interface_H_
#define _Step_Propagator_Generic_FixPosition_Interface_H_

#include "step-propagator/generic/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorFixPosition : public StepPropagatorGeneric<T> {

    public:

      typedef StepPropagatorFixPosition<T>    Type;
      typedef StepPropagatorGeneric<T>  ParentType;

      StepPropagatorFixPosition() : ParentType() {}
      ~StepPropagatorFixPosition() { Clear(*this); }

      virtual void Allocate() { this->_tag=FixPosition; }
      virtual void Init() {
        if(this->_V.IsValid())
          for(unsigned int i=0;i<this->_V.Size();++i) this->_V[i].BlasFill(0);
      }
      virtual void Clean() {}
      virtual void Update() {}
      virtual void Update1() {}
      virtual void Update2() {}
      virtual void Update3() {}
      virtual void Update4() {}
      virtual void Update5() {}
      virtual void Update6() {}
      virtual void Update7() {}
      virtual void Evolute1() {}
      virtual void Evolute2() {}
      virtual void Evolute3() {}
      virtual void Evolute4() {}
      virtual void Load(Array<Unique64Bit>&) {}
      virtual const T KineticEnergy() const { return 0; }
      virtual unsigned int DegreeFreedom() const { return 0; }

    private:

      StepPropagatorFixPosition(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorFixPosition<T>& P) {
    typedef typename StepPropagatorFixPosition<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

