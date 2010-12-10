
#ifndef _Monomer_Propagator_H_
#define _Monomer_Propagator_H_

#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  struct monomerPropagator : public Vector<UniqueParameter> {
    typename monomerPropagator<T> Type;
    typedef Vector<UniqueParameter>   ParentType;
    
    monomerPropagator() : ParentType() {}
    monomerPropagator(const Type& P) {
      myError("Cannot create monomer propagator");
    }
    Type& operator=(const Type& P) {
      myError("Cannot copy monomer propagator");
      return *this;
    }
    ~monomerPropagator() { release(*this); }
  };

  template <typename T>
  bool IsAvailable(const monomerPropagator<T>& P) {
    return IsAvailable(static_cast<Vector<UniqueParameter>&>(P));
  }

  template <typename T>
  void release(monomerPropagator<T>& P) {
    release(static_cast<Vector<UniqueParameter>&>(P));
  }

  template <typename T>
  void copy(monomerPropagator<T>& P, const monomerPropagator<T>& cP) {
    copy(static_cast<Vector<UniqueParameter>&>(P),
         static_cast<const Vector<UniqueParameter>&>(cP));
  }

  template <typename T>
  void refer(monomerPropagator<T>& P, const monomerPropagator<T>& rP) {
    refer(static_cast<Vector<UniqueParameter>&>(P),
          static_cast<const Vector<UniqueParameter>&>(rP));
  }

}

#include "data/name/monomer-propagator-type.h"

namespace std {

  template <typename T>
  void allocate(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    assert(mpgtype<monomerPropagatorNumberType);
    allocate(static_cast<Vector<UniqueParameter>&>(P),
             monomerPropagatorParameterSize[mpgtype]);
  }

}

#endif
