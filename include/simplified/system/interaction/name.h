
#ifndef _System_Interaction_Name_H_
#define _System_Interaction_Name_H_

namespace mysimulator {

  enum class InteractionName {
    PairHarmonic,
    PairLJ612,
    PairLJ612Cut,
    PairLJ1012,
    PairCore12,
    PairCoreLJ612,
    PairStepContinuous,
    AngleHarmonic,
    DihedralPeriodic,
    DihedralDualPeriodic,
    DihedralDualPeriodicCommonPhase,
    Unknown
  };

}

#endif

