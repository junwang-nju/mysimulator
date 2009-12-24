
#ifndef _Minimizer_Line_PropertyList_H_
#define _Minimizer_Line_PropertyList_H_

#include "minimizer-line-base.h"
#include "property-list.h"
#include "property-list-op.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class Parameter4MinimizerPropertyList {
    public:
      PropertyList<refVector,refVector,uint>    Mask;
      PropertyList<refVector>                   DMask;
      DistEvalObj                               *pDEval;
      GeomType                                  *pRunGeo;
      ParamList                                 *RunParam;
      IDL
  };

  template <typename DistEvalObj, typename GeomType,
            template <typename> class ListType>
  class Backtracking4PropertyList
    : public BacktrackingLineMinimizer<
                PropertyList<ListType>,
                Parameter4MinimizerPropertyList<DistEvalObj,GeomType> > {
  };

}

#endif

