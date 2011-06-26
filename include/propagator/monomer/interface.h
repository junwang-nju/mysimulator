
#ifndef _Propagator_Monomer_Interface_H_
#define _Propagator_Monomer_Interface_H_

#include "vector/interface.h"
#include "unique-parameter/64bit/interface.h"
#include "propagator/move-name.h"
#include "propagator/ensemble-name.h"
#include "propagator/monomer/name.h"

namespace mysimulator {

  template <typename T>
  struct MonomerPropagator {

    typedef MonomerPropagator<T>  Type;
    typedef void (*MoveType)(Vector<UniqueParameter64Bit>&,
                             const Vector<UniqueParameter64Bit>&);

    PropagatorMoveName  MoveMode;
    PropagatorEnsembleName  EnsembleMode;
    PropagatorMonomerName   MonomerMode;
    Vector<UniqueParameter64Bit>  Data;
    Vector<MoveType>  Move;

    MonomerPropagator() : Data(), Move() {}
    MonomerPropagator(const Type&) {
      Error("Copier of MonomerPropagator Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MonomerPropagator Disabled!");
      return *this;
    }
    ~MonomerPropagator() { clearData(); }

    void clearData() { release(Data); release(Move); }

  };

  template <typename T>
  bool IsValid(const MonomerPropagator<T>& P) {
    return IsValid(P.Data)&&IsValid(P.Move);
  }

  template <typename T>
  void release(MonomerPropagator<T>& P) { P.clearData(); }

}

#endif

