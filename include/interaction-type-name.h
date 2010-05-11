
#ifndef _Interaction_Type_H_
#define _Interaction_Type_H_

namespace std {
  enum InteractionTypeName {
    PairwiseHarmonic=0,
    PairwiseLJ612,
    PairwiseLJ1012,
    PairwiseCore12,
    PairwiseLJ612Cut,
    PairwiseLJ1012Cut,
    PairwiseCoreLJ612,
    InteractionTypeTableTerminus,
    NumberInteractions = InteractionTypeTableTerminus-1
  };
}

#endif

