
#ifndef _Minimizer_Line_BackTracking_For_PropertyList_H_
#define _Minimizer_Line_BackTracking_For_PropertyList_H_

#include "minimizer-line-4propertylist.h"
#include "minimizer-line-backtracking.h"

namespace std {
  template <template <typename> class ListType,
            typename DistEvalObj, typename GeomType, uint bMode,
            uint CondType>
  class BacktrackingLineMinimizer4PropertyList
    : public BacktrackingLineMinimizer<
                LineMinimizerBase4PropertyList<ListType,
                                               DistEvalObj,GeomType,bMode>,
                CondType> {
    public:
      typedef BacktrackingLineMinimizer4PropertyList<ListType,DistEvalObj,
                                                     GeomType,bMode,CondType>
              Type;
      typedef BacktrackingLineMinimizer<
                 LineMinimizerBase4PropertyList<ListType,
                                                DistEvalObj,GeomType,bMode>,
                 CondType>
              ParentType;
  };

}

#endif

