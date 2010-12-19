
#ifndef _Interaction_Parameter_Regular_Operation_H_
#define _Interaction_Parameter_Regular_Operation_H_

#include "data/interaction/parameter-unit.h"

namespace std {

  template <typename T, typename GeomType>
  void update(InteractionParameterUnit& P,
              const Vector<T>* X, const GeomType& Geo) {
  }

  template <typename T, typename GeomType>
  void update(Vector<InteractionParameterUnit>& P,
              const Vector<T>* X, const GeomType& Geo) {
  }

}

#include "data/basic/property-list.h"

namespace std {

  template <typename T, typename GeomType>
  void update(PropertyList<InteractionParameterUnit>& P,
              const Vector<T>* X, const GeomType& Geo) {
  }

}

#include "data/derived/dual-vector.h"

namespace std {

  template <typename T, typename GeomType>
  void update(DualVector<InteractionParameterUnit>& P,
              const Vector<T>*X, const GeomType& Geo) {
  }

}

#endif

