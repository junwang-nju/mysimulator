
#ifndef _Propagator_Interaction_H_
#define _Propagator_Interaction_H_

#include "propagator/subsystem/interface.h"
#include "list/interface.h"

namespace mysimulator {

  template <typename T>
  struct Propagator {

    typedef Propagator<T>   Type;
    typedef void (*BuildParameterType)(Type&);

    PropagatorMoveName  MoveMode;
    Vector<UniqueParameter64Bit>  Data;
    Vector<SubsysPropagator<T> >  Sys;
    List<T> ID;
    List<T> X;
    List<T> V;
    List<T> G;
    List<T> Msk;
    BuildParameterType  Update;

    Propagator()
      :MoveMode(UnknownMove),Data(),Sys(),ID(),X(),V(),G(),Msk(),Update(NULL){}
    Propagator(const Type&) { Error("Copier of Propagator Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Propagator Disabled!");
      return *this;
    }
    ~Propagator() { clearData(); }

    void clearData() {
      MoveMode=UnknownMove;
      release(Data);    release(Sys);
      release(ID); release(X); release(V); release(G); release(Msk);
      Update=NULL;
    }
    T& value(const unsigned int I) { return Data[I].value<T>(); }
    const T& value(const unsigned int I) const { return Data[I].value<T>(); }

  };

  template <typename T>
  bool IsValid(const Propagator<T>& P) {
    return (P.MoveMode!=UnknownMove)&&IsValid(P.Data)&&IsValid(P.Sys)&&
           IsValid(P.X)&&IsValid(P.V)&&IsValid(P.G)&&IsValid(P.Msk);
  }

  template <typename T>
  void release(Propagator<T>& P) { P.clearData(); }

} 

#endif

