
#ifndef _Propagator_Parameter_Element_H_
#define _Propagator_Parameter_Element_H_

namespace std {

  union PropagatorDataElementType {
    double d;
    void*  ptr;
    PropagatorDataElementType() {}
    PropagatorDataElementType(const PropagatorDataElementType& P) {
      myError("Cannot create from Propagator Data Element");
    }
    PropagatorDataElementType& operator=(const PropagatorDataElementType& P) {
      d=P.d;
      return *this;
    }
  };

}

#endif

