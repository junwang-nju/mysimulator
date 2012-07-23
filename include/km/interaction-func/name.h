
/** @file interaction-func/name.h
 * @brief the names for various functions of interaction
 *
 * @author Jun | junwang.nju@gmail.com
 */

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
    StepContinuous,
    AngleHarmonic,
    DihedralPeriodic,
    DihedralPeriodic2P,
    WallHarmonic,
    WallCore12,
    InteractionNumberFuncs,
    UnknownInteractionFunc,
  };

  static unsigned int InteractionFuncIDSize[] = {
    2,    //  Harmonic
    2,    //  LJ612,
    2,    //  LJ1012,
    2,    //  LJ612Cut,
    2,    //  LJ1012Cut,
    2,    //  Core12,
    2,    //  CoreLJ612,
    2,    //  Coulomb,
    2,    //  DistDielCoulomb,
    2,    //  StepContinuous
    3,    //  AngleHarmonic,
    0,    //  DihedralPeriodic
    4,    //  DihedralPeriodic2P,
    2,    //  WallHarmonic
    2     //  WallCore12
  };

}

#endif

