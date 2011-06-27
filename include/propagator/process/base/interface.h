
#ifndef _Propagator_Process_Base_Interface_H_
#define _Propagator_Process_Base_Interface_H_

#include "io/error.h"

namespace mysimulator {

  template <typename PropagatorType>
  struct PropagatorProcessBase {
    typedef PropagatorProcessBase<PropagatorType> Type;
    PropagatorProcessBase() {}
    PropagatorProcessBase(const Type&) {
      Error("Copier of PropagatorProcessBase Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for PropagatorProcessBase Disabled!");
      return *this;
    }
    ~PropagatorProcessBase() { clearData(); }

    void clearData() {}
    virtual void operator()(PropagatorType&)=0;
  };

}

#endif

