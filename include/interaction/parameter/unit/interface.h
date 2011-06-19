
#ifndef _Interaction_Parameter_Unit_H_
#define _Interaction_Parameter_Unit_H_

#include "vector/interface.h"
#include "unique-parameter/64bit/interface.h"
#include "interaction/func/name.h"

namespace mysimulator {

  struct InteractionParameterUnit {

    typedef InteractionParameterUnit  Type;

    Vector<UniqueParameter64Bit> prm;
    Vector<unsigned int> idx;
    InteractionFunctionName tag;

    InteractionParameterUnit() : prm(), idx(), tag(UnknownInteractionFunc) {}
    InteractionParameterUnit(const Type&) {
      Error("Copier of InteractionParameterUnit Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for InteractionParameterUnit Disabled!");
      return *this;
    }
    ~InteractionParameterUnit() { clearData(); }

    void clearData() { release(prm); release(idx); tag=UnknownInteractionFunc; }

  };

  bool IsValid(const InteractionParameterUnit& P) {
    return IsValid(P.prm)&&IsValid(P.idx)&&(P.tag!=UnknownInteractionFunc);
  }

  void release(InteractionParameterUnit& P) { P.clearData(); }

}

#endif

