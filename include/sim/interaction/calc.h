
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/func/interface.h"

#if !(defined(_CALCE_DCL)||defined(_CALCG_DCL)||defined(_CALCB_DCL))
#define _CALCE_DCL        T& Energy
#define _CALCG_DCL        T** Grad
#define _CALCB_DCL        _CALCE_DCL,_CALCG_DCL
#else
#error "Duplicate Definitions of _CALCE_DCL,_CALCG_DCL,_CALCB_DCL"
#endif

#if !(defined(_CALCE_FUNC)||defined(_CALCG_FUNC)||defined(_CALCB_FUNC))
#define _CALCE_FUNC       Energy
#define _CALCG_FUNC       Gradient
#define _CALCB_FUNC       Both
#else
#error "Duplicate Definitions of _CALCE_FUNC,_CALCG_FUNC,_CALCB_FUNC"
#endif

#if !(defined(_CALCE_VAR)||defined(_CALCG_VAR)||defined(_CALCB_VAR))
#define _CALCE_VAR        Energy
#define _CALCG_VAR        Grad
#define _CALCB_VAR        _CALCE_VAR,_CALCG_VAR
#else
#error "Duplicate Definitions of _CALCE_VAR,_CALCG_VAR,_CALCB_VAR"
#endif

#if !(defined(_Single)||defined(_Array)||defined(_List))
#define _Single(DT)       DT&
#define _Array(DT)        DT*
#define _List(DT)         DT**
#else
#error "Duplicate Definitions of _Single,_Array,_List"
#endif

#if !(defined(_Low_Array)||defined(_Low_List))
#define _Low_Array(DT)    _Single(DT)
#define _Low_List(DT)     _Array(DT)
#else
#error "Duplicate Definitions of _Low_Array,_Low_List"
#endif

#ifndef _HEAD
#define _HEAD(Method,typeID,typePrm) \
  template <typename T,typename GeomType> \
  void Calc(const InteractionFunc<GeomType,T>& F, const T** X,\
            const typeID(unsigned int) id, const typePrm(Unique64Bit) P,\
            _Low##typeID(InteractionBuffer<T>) Buf, const GeomType& Geo,\
            Method##_DCL)
#else
#error "Duplicate Definitions of _HEAD"
#endif

#ifndef _RunCalc
#define _RunCalc(CalcMethod) \
  CalcMethod(_CALCE) \
  CalcMethod(_CALCG) \
  CalcMethod(_CALCB)
#else
#error "Duplicate Definitions of _RunCalc"
#endif

#ifndef _Array_Array
#define _Array_Array(Method) \
  _Head(Method,_Array,_Array) { \
    assert(IsValid(F)); \
    F.Method##_Func(X,id,P,Geo,Method##_VAR,Buf); \
  }
#else
#error "Duplicate Definitions of _Array_Array"
#endif

namespace mysimulator {

  _RunCalc(_Array_Array)

}

#ifdef _Array_Array
#undef _Array_Array
#endif

#include "array/1d/size.h"

#ifndef _List_Array
#define _List_Array(Method) \
  _Head(Method,_List,_Array) { \
    unsigned int n=size(id); \
    assert(n==size(Buf)); \
    for(unsigned int i=0;i<n;++i) Calc(F,X,id[i],P,Buf[i],Geo,Method##_VAR); \
  }
#else
#error "Duplicate Definitions of _List_Array"
#endif

namespace mysimulator {

  _RunCalc(_List_Array)

}

#ifdef _List_Array
#undef _List_Array
#endif

#ifndef _List_List
#define _List_List(Method) \
  _Head(Method,_List,_List) { \
    unsigned int n=size(id); \
    assert((n==size(P))&&(n==size(Buf))); \
    for(unsigned int i=0;i<n;++i) Calc(F,X,id[i],P[i],Buf[i],Geo,Method##_VAR);\
  }
#else
#error "Duplicate Definitions of _List_List"
#endif

namespace mysimulator {

  _RunCalc(_List_List)

}

#ifdef _List_List
#undef _List_List
#endif

#ifndef _ArrayForceCase
#define _ArrayForceCase(Method) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT> \
  void Calc(const InteractionFunc<GT,T>* F,const T** X,const IDT id, \
            const PT P, BT Buf, const GT& Geo, Method##_DCL) { \
    unsigned int n=size(F); \
    assert((n==size(id))&&(n==sizeof(P))&&(n==sizeof(Buf))); \
    for(unsigned int i=0;i<n;++i) \
      Calc(F[i],X,id[i],P[i],Buf[i],Geo,Method##_VAR); \
  }
#else
#error "Duplicate Definitions of _ArrayForceCase
#endif

namespace mysimulator {

  _RunCalc(_ArrayForceCase)

}

#ifdef _ArrayForceCase
#undef _ArrayForceCase
#endif

#ifdef _RunCalc
#undef _RunCalc
#endif

#ifdef _Head
#undef _Head
#endif

#if defined(_Low_List)||defined(_Low_Array)
#undef _Low_List
#undef _Low_Array
#endif

#if defined(_List)||defined(_Array)||defined(_Single)
#undef _List
#undef _Array
#undef _Single
#endif

#if defined(_CALCE_VAR)||defined(_CALCG_VAR)||defined(_CALCB_VAR)
#undef _CALCB_VAR
#undef _CALCG_VAR
#undef _CALCE_VAR
#endif

#if defined(_CALCE_Func)||defined(_CALCG_Func)||defined(_CALCB_Func)
#undef _CALCB_Func
#undef _CALCG_Func
#undef _CALCE_Func
#endif

#if defined(_CALCE_DCL)||defined(_CALCG_DCL)||defined(_CALCB_DCL)
#undef _CALCB_DCL
#undef _CALCG_DCL
#undef _CALCE_DCL
#endif

#endif

