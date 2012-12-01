
#ifndef _System_Interaction_ID_Size_H_
#define _System_Interaction_ID_Size_H_

#include "system/interaction/name.h"

namespace mysimulator {

  unsigned int __id_size_of(InteractionName N) {
    switch(N) {
      case InteractionName::PairHarmonic:   return 2;
      case InteractionName::PairLJ612:      return 2;
      case InteractionName::PairLJ612Cut:   return 2;
      case InteractionName::PairCore12:     return 2;
      default:
        fprintf(stderr,"Unknown Interaction!\n");
    }
    return 0;
  }

}

#endif

