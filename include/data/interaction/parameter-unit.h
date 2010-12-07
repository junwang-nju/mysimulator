
#ifndef _Interaction_Parameter_Unit_H_
#define _Interaction_Parameter_Unit_H_

#include "data/basic/unique-parameter.h"

namespace std {

  struct InteractionParameterUnit {
    typedef InteractionParameterUnit  Type;
    Vector<UniqueParameter> prm;
    Vector<unsigned int> idx;

    InteractionParameterUnit() : prm(), idx() {}
    InteractionParameterUnit(const Type&) {
      myError("Cannot create Interaction Parameter Unit");
    }
    Type& operator=(const Type& P) {
      myError("Cannot copy Interaction Parameter Unit");
      return *this;
    }
    ~InteractionParameterUnit() { release(*this); }
  };

  bool IsAvailable(const InteractionParameterUnit& P) {
    return IsAvailable(P.prm)&&IsAvailable(P.idx);
  }

}

#endif

