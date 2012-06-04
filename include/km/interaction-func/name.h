
#ifndef _Interaction_Func_Name_H_
#define _Interaction_Func_Name_H_

namespace mysimulator {

  enum InteractionFuncName {
    Harmonic=0,
    LJ612,
    LJ1012,
    LJ612Cut,
    LJ1012Cut,
    Core12,
    CoreLJ612,
    Coulomb,
    DistDielCoulomb,
    AngleHarmonic,
    DihedralPeriodic,
    InteractionNumberFuncs,
    UnknownInteractionFunc
  };

}

#endif

