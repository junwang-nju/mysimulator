
#ifndef _Interaction_Function_Interface_H_
#define _Interaction_Function_Interface_H_

#include "interaction/func/component/name.h"
#include "interaction/func/component/list.h"

namespace mysimulator {

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T=double>
  struct InteractionFunc {

    typedef InteractionFunc<IF,DBuffer,GeomType,T>    Type;

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

    static const EFunctionalType  efunctional;
    static const DFunctionalType  dfunctional;
    static const BFunctionalType  bfunctional;
    static const EFuncMethodType  efuncmethod;
    static const GFuncMethodType  gfuncmethod;
    static const BFuncMethodType  bfuncmethod;

    static void Energy(
        const Vector<T>* X,const unsigned int* id,const UniqueParameter64Bit* P,
        DBuffer<T>& B,const GeomType& G,T& E,Vector<T>* tvec) {
      assert(IsValid(efuncmethod));
      efuncmethod(X,id,P,B,G,E,tvec,efunctional);
    }
    static void Gradient(
        const Vector<T>* X,const unsigned int* id,const UniqueParameter64Bit* P,
        DBuffer<T>& B,const GeomType& G,Vector<T>* D,Vector<T>* tvec) {
      assert(IsValid(gfuncmethod));
      gfuncmethod(X,id,P,B,G,D,tvec,dfunctional);
    }
    static void Both(
        const Vector<T>* X,const unsigned int* id,const UniqueParameter64Bit* P,
        DBuffer<T>& B,const GeomType& G,T& E,Vector<T>* D,Vector<T>* tvec) {
      assert(IsValid(bfuncmethod));
      bfuncmethod(X,id,P,B,G,E,D,tvec,bfunctional);
    }

  };

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const typename InteractionFunc<IF,DBuffer,GeomType,T>::EFunctionalType
  InteractionFunc<IF,DBuffer,GeomType,T>::efunctional=
    InteractionFuncList<DBuffer,GeomType,T>::EFunctional[IF];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const typename InteractionFunc<IF,DBuffer,GeomType,T>::DFunctionalType
  InteractionFunc<IF,DBuffer,GeomType,T>::dfunctional=
    InteractionFuncList<DBuffer,GeomType,T>::DFunctional[IF];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const typename InteractionFunc<IF,DBuffer,GeomType,T>::BFunctionalType
  InteractionFunc<IF,DBuffer,GeomType,T>::bfunctional=
    InteractionFuncList<DBuffer,GeomType,T>::BFunctional[IF];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const typename InteractionFunc<IF,DBuffer,GeomType,T>::EFuncMethodType
  InteractionFunc<IF,DBuffer,GeomType,T>::efuncmethod=
    InteractionFuncList<DBuffer,GeomType,T>::EFuncMethod[
      InteractionFuncList<DBuffer,GeomType,T>::MethodMap[IF]];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const typename InteractionFunc<IF,DBuffer,GeomType,T>::GFuncMethodType
  InteractionFunc<IF,DBuffer,GeomType,T>::gfuncmethod=
    InteractionFuncList<DBuffer,GeomType,T>::GFuncMethod[
      InteractionFuncList<DBuffer,GeomType,T>::MethodMap[IF]];

  template <InteractionFunctionName IF, template<typename> class DBuffer,
            typename GeomType, typename T>
  const typename InteractionFunc<IF,DBuffer,GeomType,T>::BFuncMethodType
  InteractionFunc<IF,DBuffer,GeomType,T>::bfuncmethod=
    InteractionFuncList<DBuffer,GeomType,T>::BFuncMethod[
      InteractionFuncList<DBuffer,GeomType,T>::MethodMap[IF]];

}

#endif

