
#ifndef _Minimizer_Hierarchy_Parameter_For_PropertyList_H_
#define _Minimizer_Hierarchy_Parameter_For_PropertyList_H_

#include "ref-property-list.h"
#include "parameter-list.h"
#include "interaction-method.h"
#include "minimizer-parameter-name-4propertylist.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  class MinimizerHierarchyParameter4PropertyList {

    public:

      typedef MinimizerHierarchyParameter4PropertyList<DistEvalMethod,GeomType>
              Type;

      static const unsigned int Mode;

      refPropertyList<unsigned int>::Type iMaskSeq;

      refPropertyList<double>::Type dMaskSeq;

      DistEvalMethod<refVector> DEval;

      GeomType<refVector> Geo;

      refPropertyList<refVector<double> >::Type  ParamLst;

      refVector<InteractionMethod<DistEvalMethod,GeomType> > IMethodLst;

      refPropertyList<refVector<unsigned int> >::Type IdxLst;

      MinimizerHierarchyParameter4PropertyList()
        : iMaskSeq(), dMaskSeq(), DEval(), Geo(), ParamLst(), IMethodLst(),
          IdxLst() {
      }

      MinimizerHierarchyParameter4PropertyList(const Type& MFP) {
        myError("Cannot create from Minimizer Hierarchy Parameter for Property List");
      }

      Type& operator=(const Type& MFP) {
        iMaskSeq.refer(MFP.iMaskSeq);
        dMaskSeq.refer(MFP.dMaskSeq);
        DEval.refer(MFP.DEval);
        Geo.refer(MFP.Geo);
        ParamLst.refer(MFP.Param);
        IMethodLst.refer(MFP.IMethodLst);
        IdxLst.refer(MFP.IdxLst);
        return *this;
      }

      void update() { DEval.update(); }

  };

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  const unsigned int
  MinimizerHierarchyParameter4PropertyList<DistEvalMethod,GeomType>::Mode=
      HierarchyParameter4PropertyList;

}

#endif

