
#ifndef _Minimizer_SteepestDescent_For_PropertyList_H_
#define _Minimizer_SteepestDescent_For_PropertyList_H_

#include "minimizer-steep-base.h"
#include "minimizer-line-backtracking-4propertylist.h"

namespace std {

  template <template <typename> class ListType,
            typename DistEvalObj, typename GeomType, uint bMode,
            uint CondType.
            template <template <typename> class,typename,typename,uint,uint>
            class LineMinMethod>
  class SteepestDescentMinimizer4PropertyList
    : public SteepestDescentMinimizerBase<
                LineMinMethod<ListType,DistEvalObj,GeomType,bMode,CondType> > {
  };

}

#endif

