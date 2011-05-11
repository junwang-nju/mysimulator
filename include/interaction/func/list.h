
#ifndef _Interaction_Function_List_H_
#define _Interaction_Function_List_H_

#include "interaction/func/component-name.h"
#include "interaction/func/name.h"
#include "interaction/func/method-name.h"

#include "functional/harmonic/func.h"
#include "functional/lj612/func.h"
#include "functional/lj612cut/func.h"

#include "functional/harmonic/diff.h"
#include "functional/lj612/diff.h"
#include "functional/lj612cut/diff.h"

#include "functional/harmonic/both.h"
#include "functional/lj612/both.h"
#include "functional/lj612cut/both.h"

#include "interaction/func/method/pairwise/energy.h"
#include "interaction/func/method/pairwise/gradient.h"
#include "interaction/func/method/pairwise/both.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType,typename T>
  struct InteractionFuncList {

    typedef
    typename InteractionFuncComponentName<DBuffer,GeomType,T>::EFunctionalType
             EFunctionalType;
    typedef
    typename InteractionFuncComponentName<DBuffer,GeomType,T>::DFunctionalType
             DFunctionalType;
    typedef
    typename InteractionFuncComponentName<DBuffer,GeomType,T>::BFunctionalType
             BFunctionalType;
    typedef
    typename InteractionFuncComponentName<DBuffer,GeomType,T>::EFuncMethodType
             EFuncMethodType;
    typedef
    typename InteractionFuncComponentName<DBuffer,GeomType,T>::GFuncMethodType
             GFuncMethodType;
    typedef
    typename InteractionFuncComponentName<DBuffer,GeomType,T>::BFuncMethodType
             BFuncMethodType;

    static const EFunctionalType EFunctional[InteractionNumberFunction];
    static const DFunctionalType DFunctional[InteractionNumberFunction];
    static const BFunctionalType BFunctional[InteractionNumberFunction];
    static const EFuncMethodType EFuncMethod[InteractionFuncNumberMode];
    static const GFuncMethodType GFuncMethod[InteractionFuncNumberMode];
    static const BFuncMethodType BFuncMethod[InteractionFuncNumberMode];
    static const InteractionFunctionMethodName
                                 MethodMap[InteractionNumberFunction];

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
  const typename InteractionFuncList<DBuffer,GeomType,T>::EFuncMethodType
  InteractionFuncList<DBuffer,GeomType,T>::EFuncMethod[]={
    EFuncMethodPairwise
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::GFuncMethodType
  InteractionFuncList<DBuffer,GeomType,T>::GFuncMethod[]={
    GFuncMethodPairwise
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::BFuncMethodType
  InteractionFuncList<DBuffer,GeomType,T>::BFuncMethod[]={
    BFuncMethodPairwise
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const InteractionFunctionMethodName
  InteractionFuncList<DBuffer,GeomType,T>::MethodMap[]={
    PairwiseMethod,
    PairwiseMethod,
    PairwiseMethod
  };

}

#endif

