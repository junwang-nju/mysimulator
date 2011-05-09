
#ifndef _Interaction_Function_Interface_H_
#define _Interaction_Function_Interface_H_

#include "interaction/func/base/interface.h"
#include "interaction/func/list.h"

namespace mysimulator {

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T=double>
  struct InteractionFunc : public InteractionFuncBase<DBuffer,GeomType,T> {

    typedef InteractionFunc<IF,DBuffer,GeomType,T>    Type;
    typedef InteractionFuncBase<DBuffer,GeomType,T>   ParentType;

    static const typename ParentType::EFunctionalType  efunctional;
    static const typename ParentType::DFunctionalType  dfunctional;
    static const typename ParentType::BFunctionalType  bfunctional;
    static const typename ParentType::EFuncType        efunc;
    static const typename ParentType::GFuncType        gfunc;
    static const typename ParentType::BFuncType        bfunc;

  };

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const
  typename InteractionFunc<IF,DBuffer,GeomType,T>::ParentType::EFunctionalType
  InteractionFunc<IF,DBuffer,GeomType,T>::efunctional=
    InteractionFuncList<DBuffer,GeomType,T>::EFunctional[IF];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const
  typename InteractionFunc<IF,DBuffer,GeomType,T>::ParentType::DFunctionalType
  InteractionFunc<IF,DBuffer,GeomType,T>::dfunctional=
    InteractionFuncList<DBuffer,GeomType,T>::DFunctional[IF];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const
  typename InteractionFunc<IF,DBuffer,GeomType,T>::ParentType::BFunctionalType
  InteractionFunc<IF,DBuffer,GeomType,T>::bfunctional=
    InteractionFuncList<DBuffer,GeomType,T>::BFunctional[IF];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const
  typename InteractionFunc<IF,DBuffer,GeomType,T>::ParentType::EFuncType
  InteractionFunc<IF,DBuffer,GeomType,T>::efunc=
    InteractionFuncList<DBuffer,GeomType,T>::EFunc[
      InteractionFuncList<DBuffer,GeomType,T>::ModeMap[IF]];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const
  typename InteractionFunc<IF,DBuffer,GeomType,T>::ParentType::GFuncType
  InteractionFunc<IF,DBuffer,GeomType,T>::gfunc=
    InteractionFuncList<DBuffer,GeomType,T>::GFunc[
      InteractionFuncList<DBuffer,GeomType,T>::ModeMap[IF]];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const
  typename InteractionFunc<IF,DBuffer,GeomType,T>::ParentType::BFuncType
  InteractionFunc<IF,DBuffer,GeomType,T>::bfunc=
    InteractionFuncList<DBuffer,GeomType,T>::BFunc[
      InteractionFuncList<DBuffer,GeomType,T>::ModeMap[IF]];

}

#endif

