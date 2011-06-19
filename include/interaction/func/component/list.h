
#ifndef _Interaction_Function_Component_List_H_
#define _Interaction_Function_Component_List_H_

#include "interaction/func/component/name.h"
#include "interaction/func/name.h"
#include "interaction/func/component/method/name.h"

#include "functional/harmonic/func.h"
#include "functional/lj612/func.h"
#include "functional/lj612cut/func.h"
#include "functional/lj1012/func.h"
#include "functional/lj1012cut/func.h"
#include "functional/core12/func.h"
#include "functional/corelj612/func.h"
#include "functional/coulomb/func.h"

#include "functional/harmonic/diff.h"
#include "functional/lj612/diff.h"
#include "functional/lj612cut/diff.h"
#include "functional/lj1012/diff.h"
#include "functional/lj1012cut/diff.h"
#include "functional/core12/diff.h"
#include "functional/corelj612/diff.h"
#include "functional/coulomb/diff.h"

#include "functional/harmonic/both.h"
#include "functional/lj612/both.h"
#include "functional/lj612cut/both.h"
#include "functional/lj1012/both.h"
#include "functional/lj1012cut/both.h"
#include "functional/core12/both.h"
#include "functional/corelj612/both.h"
#include "functional/coulomb/both.h"

#include "interaction/func/component/method/pairwise/energy.h"
#include "interaction/func/component/method/pairwise/gradient.h"
#include "interaction/func/component/method/pairwise/both.h"

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

  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::EFunctionalType
  InteractionFuncList<DBuffer,GeomType,T>::EFunctional[]={
    FuncHarmonic<T>,
    FuncLJ612<T>,
    FuncLJ612Cut<T>,
    FuncLJ1012<T>,
    FuncLJ1012Cut<T>,
    FuncCore12<T>,
    FuncCoreLJ612<T>,
    FuncCoulomb<T>
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::DFunctionalType
  InteractionFuncList<DBuffer,GeomType,T>::DFunctional[]={
    DiffHarmonic<T>,
    DiffLJ612<T>,
    DiffLJ612Cut<T>,
    DiffLJ1012<T>,
    DiffLJ1012Cut<T>,
    DiffCore12<T>,
    DiffCoreLJ612<T>,
    DiffCoulomb<T>
  };

  template <template<typename> class DBuffer,typename GeomType,typename T>
  const typename InteractionFuncList<DBuffer,GeomType,T>::BFunctionalType
  InteractionFuncList<DBuffer,GeomType,T>::BFunctional[]={
    BothHarmonic<T>,
    BothLJ612<T>,
    BothLJ612Cut<T>,
    BothLJ1012<T>,
    BothLJ1012Cut<T>,
    BothCore12<T>,
    BothCoreLJ612<T>,
    BothCoulomb<T>
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

  static const InteractionFunctionMethodName
  MethodMap[InteractionNumberFunction]={
    PairwiseMethod,
    PairwiseMethod,
    PairwiseMethod,
    PairwiseMethod,
    PairwiseMethod,
    PairwiseMethod,
    PairwiseMethod,
    PairwiseMethod
  };

}

#endif

