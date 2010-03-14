
#ifndef _Interaction_Method_Operation_H_
#define _Interaction_Method_Operation_H_

#include "interaction-method.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void SetInteractionMethod(InteractionMethod<DistEvalMethod,GeomType>& IM,
                            const unsigned int iTag) {
  }

}

#endif

