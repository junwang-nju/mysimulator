
#ifndef _Interaction_Parameter_Meta_Operation_H_
#define _Interaction_Parameter_Meta_Operation_H_

#include "data/interaction/meta-parameter.h"

namespace std {
  
  template <typename PType, typename IType, typename T, typename GeomType>
  void update(InteractionMetaParameter<PType,IType,T>& P,
              const Vector<T>* X, const GeomType& Geo) {
    update(P.inprm,X,Geo);
  }

}

#endif
