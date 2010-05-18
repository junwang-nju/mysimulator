
#ifndef _Propagator_Parameter_Element_H_
#define _Propagator_Parameter_Element_H_

#include "error-proc.h"

namespace std {

  union PropagatorDataElementType {
    double d;
    void*  vptr;
    unsigned long long int ull;
    PropagatorDataElementType() {}
    PropagatorDataElementType(const PropagatorDataElementType& P) {
      myError("Cannot create from Propagator Data Element");
    }
    PropagatorDataElementType& operator=(const PropagatorDataElementType& P) {
      d=P.d;
      return *this;
    }
    PropagatorDataElementType& operator=(const double value) {
      d=value;
      return *this;
    }
    template <typename T>
    PropagatorDataElementType& operator=(const T* tptr) {
      vptr=reinterpret_cast<void*>(const_cast<T*>(tptr));
      return *this;
    };
  };

  ostream& operator<<(ostream& os, const PropagatorDataElementType& PD) {
    os<<PD.ull;
    return os;
  }

}

#endif

