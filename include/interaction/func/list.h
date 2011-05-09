
#ifndef _Interaction_Function_List_H_
#define _Interaction_Function_List_H_

#include "interaction/func/base/interface.h"
#include "interaction/func/name.h"
#include "interaction/func/mode-name.h"

#include "functional/harmonic/func.h"
#include "functional/lj612/func.h"
#include "functional/lj612cut/func.h"

#include "functional/harmonic/diff.h"
#include "functional/lj612/diff.h"
#include "functional/lj612cut/diff.h"

#include "functional/harmonic/both.h"
#include "functional/lj612/both.h"
#include "functional/lj612cut/both.h"

#include "interaction/func/mode/pairwise/energy.h"
#include "interaction/func/mode/pairwise/gradient.h"
#include "interaction/func/mode/pairwise/both.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType,typename T>
  struct InteractionFuncList {

    typedef typename InteractionFuncBase<DBuffer,GeomType,T>::EFunctionalType
            EFunctionalType;
    typedef typename InteractionFuncBase<DBuffer,GeomType,T>::DFunctionalType
            DFunctionalType;
    typedef typename InteractionFuncBase<DBuffer,GeomType,T>::BFunctionalType
            BFunctionalType;
    typedef typename InteractionFuncBase<DBuffer,GeomType,T>::EFuncType
            EFuncType;
    typedef typename InteractionFuncBase<DBuffer,GeomType,T>::GFuncType
            GFuncType;
    typedef typename InteractionFuncBase<DBuffer,GeomType,T>::BFuncType
            BFuncType;

    static const EFunctionalType EFunctional[InteractionNumberFunction];
    static const DFunctionalType DFunctional[InteractionNumberFunction];
    static const BFunctionalType BFunctional[InteractionNumberFunction];
    static const EFuncType       EFunc[InteractionFuncNumberMode];
    static const GFuncType       GFunc[InteractionFuncNumberMode];
    static const BFuncType       BFunc[InteractionFuncNumberMode];
    static const InteractionFunctionModeName
                                 ModeMap[InteractionNumberFunction];

  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::EFunctionalType
  InteractionFuncList<DBuffer,GeomType,T>::EFunctional[]={
    FuncHarmonic<T>,
    FuncLJ612<T>,
    FuncLJ612Cut<T>
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::DFunctionalType
  InteractionFuncList<DBuffer,GeomType,T>::DFunctional[]={
    DiffHarmonic<T>,
    DiffLJ612<T>,
    DiffLJ612Cut<T>
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::BFunctionalType
  InteractionFuncList<DBuffer,GeomType,T>::BFunctional[]={
    BothHarmonic<T>,
    BothLJ612<T>,
    BothLJ612Cut<T>
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::EFuncType
  InteractionFuncList<DBuffer,GeomType,T>::EFunc[]={
    EFuncPairwise
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::GFuncType
  InteractionFuncList<DBuffer,GeomType,T>::GFunc[]={
    GFuncPairwise
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::BFuncType
  InteractionFuncList<DBuffer,GeomType,T>::BFunc[]={
    BFuncPairwise
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const InteractionFunctionModeName
  InteractionFuncList<DBuffer,GeomType,T>::ModeMap[]={
    PairwiseFunc,
    PairwiseFunc,
    PairwiseFunc
  };

}

#endif

