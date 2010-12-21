
#ifndef _Parameter_External_Object_LJ612Cut_H_
#define _Parameter_External_Object_LJ612Cut_H_

#include "data/name/external-object-base.h"
#include "data/name/lj612cut.h"

namespace std {

  enum ExtObjectLJ612CutParameterName {
    ExtObjLJ612CutEqRadius=ExtObjectBaseParameterName+LJ612CutEqRadius,
    ExtObjLJ612CutEqEnergyDepth=
        ExtObjectBaseNumberParameter+LJ612CutEqEnergyDepth,
    ExtObjLJ612CutCutR=ExtObjectBaseNumberParameter+LJ612CutCutR,
    ExtObjLJ612CutCutRSQ=ExtObjectBaseNumberParameter+LJ612CutCutRSQ,
    ExtObjLJ612CutVc=ExtObjectBaseNumberParameter+LJ612CutVc,
    ExtObjLJ612CutKc=ExtObjectBaseNumberParameter+LJ612CutKc,
    ExtObjLJ612CutRealSigma6=ExtObjectBaseNumberParameter+LJ612CutRealSigma6,
    ExtObjLJ612CutRealStrength=
        ExtObjectBaseNumberParameter+LJ612CutRealStrength,
    ExtObjLJ612CutTwlfRealStrength=
        ExtObjectBaseNumberParameter+LJ612CutTwlfRealStrength,
    ExtObjLJ612CutNumber
  };

}

#endif
