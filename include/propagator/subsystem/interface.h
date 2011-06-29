
#ifndef _Propagator_Subsystem_Interface_H_
#define _Propagator_Subsystem_Interface_H_

#include "propagator/monomer/interface.h"

namespace mysimulator {

  template <typename T>
  struct SubsysPropagator {

    typedef SubsysPropagator<T>   Type;
    typedef void (*MoveType)(Type&);
    typedef void (*BuildParameterType)(Type&);

    PropagatorMoveName  MoveMode;
    PropagatorEnsembleName  EnsembleMode;
    Vector<UniqueParameter64Bit>  Data;
    Vector<MonomerPropagator<T> > Mer;
    Vector<MoveType>  Move;
    BuildParameterType Update;

    SubsysPropagator() : MoveMode(UnknownMove), EnsembleMode(UnknownEnsemble),
                         Data(), Mer(), Move(), Update(NULL) {}
    SubsysPropagator(const Type&) {
      Error("Copier of SubsysPropagator Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for SubsysPropagator Disabled!");
      return *this;
    }
    ~SubsysPropagator() { clearData(); }

    void clearData() {
      MoveMode=UnknownMove;
      EnsembleMode=UnknownEnsemble;
      release(Data); release(Mer);  release(Move);
      Update=NULL;
    }

  };

  template <typename T>
  bool IsValid(const SubsysPropagator<T>& P) {
    bool fg=IsValid(P.Data)&&IsValid(P.Mer)&&IsValid(P.Move)&&(P.Update!=NULL);
    if(fg)
      for(unsigned int i=0;i<P.Mer.size;++i)
        if(!IsValid(P.Mer[i])) { fg=false; break; }
    return fg;
  }

  template <typename T>
  void IsValid(SubsysPropagator<T>& P) { P.clearData(); }

}

#endif

