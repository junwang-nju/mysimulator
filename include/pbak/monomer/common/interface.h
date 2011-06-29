
#ifndef _Propagator_Monomer_Common_Interface_H_
#define _Propagator_Monomer_Common_Interface_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  struct MonomerPropagatorCommon {

    typedef MonomerPropagatorCommon<T>    Type;

    int MonomerKind;
    Vector<T>   XVector;
    Vector<T>   VVector;
    Vector<T>   GVector;
    Vector<T>   MskVector;
    T Mass;
    T ivMass;

    MonomerPropagatorCommon()
      : MonomerKind(-1), XVector(), VVector(), GVector(), MskVector(),
        Mass(0), ivMass(0) {}
    MonomerPropagatorCommon(const Type&) {
      Error("Copier of MonomerPropagatorCommon Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MonomerPropagatorCommon Disabled!");
      return *this;
    }
    ~MonomerPropagatorCommon() { clearData(); }

    void clearData() {
      MonomerKind=-1;
      release(XVector);
      release(VVector);
      release(GVector);
      release(MskVector);
      Mass=ivMass=0;
    }

    void update() {
      assert(Mass>1e-8);
      ivMass=1./Mass;
    }

  };

  template <typename T>
  bool IsValid(const MonomerPropagatorCommon<T>& P) {
    return IsValid(P.XVector)&&IsValid(P.VVector)&&IsValid(P.GVector)&&
           IsValid(P.MskVector)&&(P.NumMonomerKinds>0)&&(P.Mass>1e-8);
  }

  template <typename T>
  void release(MonomerPropagatorCommon<T>& P) { P.clearData(); }

}

#endif

