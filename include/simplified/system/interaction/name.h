
#ifndef _System_Interaction_Name_H_
#define _System_Interaction_Name_H_

namespace mysimulator {

  enum class InteractionName {
    PairHarmonic,
    PairLJ612,
    PairLJ612Cut,
    Core12,
    UnknownInteraction
  };

}

namespace std {

  void swap(mysimulator::InteractionName& N1,
            mysimulator::InteractionName& N2) {
    mysimulator::InteractionName TN=N1;
    N1=N2;
    N2=TN;
  }

}

#endif

