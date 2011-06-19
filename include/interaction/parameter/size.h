
#ifndef _Interaction_Parameter_Size_H_
#define _Interaction_Parameter_Size_H_

#include "functional/harmonic/parameter/name.h"
#include "functional/lj612/parameter/name.h"
#include "functional/lj612cut/parameter/name.h"
#include "functional/lj1012/parameter/name.h"
#include "functional/lj1012cut/parameter/name.h"
#include "functional/core12/parameter/name.h"
#include "functional/corelj612/parameter/name.h"
#include "functional/coulomb/parameter/name.h"

namespace mysimulator {

  static const unsigned int InteractionParameterSize[]={
    HarmonicNumberParameter,
    LJ612NumberParameter,
    LJ612CutNumberParameter,
    LJ1012NumberParameter,
    LJ1012CutNumberParameter,
    Core12NumberParameter,
    CoreLJ612NumberParameter,
    CoulombNumberParameter
  };

}

#endif

