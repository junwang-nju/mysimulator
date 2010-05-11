
#ifndef _Interaction_Type_H_
#define _Interaction_Type_H_

namespace std {
  enum InteractionTypeName {
    PairwiseHarmonic=0,
    PairwiseLJ612,
    PairwiseCore12,
    PairwiseLJ612Cut,
    InteractionTypeTableTerminus,
    NumberInteractions = InteractionTypeTableTerminus-1
  };
}

#endif

