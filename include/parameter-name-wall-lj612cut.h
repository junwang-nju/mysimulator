
#ifndef _Parameter_Name_Wall_LJ612Cut_H_
#define _Parameter_Name_Wall_LJ612Cut_H_

#include "parameter-name-wall-base.h"
#include "parameter-name-lj612cut.h"

namespace std {

  enum WallLJ612CutParameterName {
    WallLJ612CutEqRadius=WallBaseNumberParameter+LJ612CutEqRadius,
    WallLJ612CutEqEnergyDepth=WallBaseNumberParameter+LJ612CutEqEnergyDepth,
    WallLJ612CutCutR=WallBaseNumberParameter+LJ612CutCutR,
    WallLJ612CutCutRSQ=WallBaseNumberParameter+LJ612CutCutRSQ,
    WallLJ612CutVc=WallBaseNumberParameter+LJ612CutVc,
    WallLJ612CutKc=WallBaseNumberParameter+LJ612CutKc,
    WallLJ612CutRealSigma6=WallBaseNumberParameter+LJ612CutRealSigma,
    WallLJ612CutRealStrength=WallBaseNumberParameter+LJ612CutRealStrength,
    WallLJ612CutTwlfRealStrength=
        WallBaseNumberParameter+LJ612CutTwlfRealStrength,
    WallLJ612CutNumberParameter,
    WallLJ612CutParameterEnd
  };

}

#include "wall-type.h"

namespace std {

  void allocateWallLJ612Cut

}

#endif

