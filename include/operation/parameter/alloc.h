
#ifndef _Parameter_Allocation_H_
#define _Parameter_Allocation_H_

#include "data/name/all-interaction.h"

namespace std {

  void allocateParameter(Vector<UniqueParameter>& P, const unsigned int tag) {
    switch (tag) {
      case Harmonic:
        allocate(P,HarmonicNumberParameter);  break;
      case LJ612:
        allocate(P,LJ612NumberParameter);  break;
      case LJ1012:
        allocate(P,LJ1012NumberParameter);  break;
      case LJ612Cut:
        allocate(P,LJ612CutNumberParameter);  break;
      case LJ1012Cut:
        allocate(P,LJ1012CutNumberParameter); break;
      case Core12:
        allocate(P,Core12NumberParameter);  break;
      case CoreLJ612:
        allocate(P,CoreLJ612NumberParameter); break;
      case Coulomb:
        allocate(P,CoulombNumberParameter); break;
      default:
        myError("Unknown interaction type");
    }
  }

}

#endif

