
#ifndef _System_Interaction_ID_Size_H_
#define _System_Interaction_ID_Size_H_

#include "system/interaction/name.h"

namespace mysimulator {

  unsigned int __id_size_of(InteractionName N) {
    switch(N) {
      case InteractionName::PairHarmonic:
      case InteractionName::PairLJ612:
      case InteractionName::PairLJ612Cut:
      case InteractionName::PairCore12:
      case InteractionName::PairLJ1012:
        return 2;
      case InteractionName::AngleHarmonic:
        return 3;
      case InteractionName::DihedralPeriodic:
      case InteractionName::DihedralDualPeriodic:
        return 4;
      default:
        fprintf(stderr,"Unknown Interaction!\n");
    }
    return 0;
  }

}

#endif

