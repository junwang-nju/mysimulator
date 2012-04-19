
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/func/interface.h"
#include "array/1d/interface.h"
#include "array/2d/content/interface.h"

#define _CALCE_DCL        T& Energy
#define _CALCG_DCL        Array1DContent<T>* Grad
#define _CALCB_DCL        _CALCE_DCL,_CALCG_DCL

#define _CALCE_FUNC       Energy
#define _CALCG_FUNC       Gradient
#define _CALCB_FUNC       Both

#define _CALCE_VAR        Energy
#define _CALCG_VAR        Grad
#define _CALCB_VAR        Energy,Grad

#define _Single(DT)       DT
#define _Array(DT)        Array1DContent< DT >
#define _RArray(DT)       Array1D< DT >
#define _List(DT)         Array2DContent<DT >
#define _RList(DT)        Array2D< DT >
#define _VList(DT)        Array1DContent<Array1DContent< DT > >
#define _VarVList(DT)     Array1DContent<Array1D< DT > >

#define _Low_Array(DT)    _Single(DT)
#define _Low_RArray(DT)   _Single(DT)
#define _Low_List(DT)     _Array(DT)
#define _Low_RList(DT)    _Array(DT)
#define _Low_VList(DT)    _Array(DT)
#define _Low_VarVList(DT) _Array(DT)

#define _Force(GEO,DT)  InteractionFunc<GEO,DT>

#define _Head(Method,typeID,typePrm) \
  template <typename T, typename GeomType> \
  void Calc(const _Force(GeomType,T)& F, const Array1DContent<T>* X, \
            const typeID(int)& id, const typePrm(Unique64Bit)& P, \
            _Low##typeID(InteractionBuffer<T>)& Buf, const GeomType& Geo, \
            Method##_DCL)

#define _RunCalc(CalcMethod) \
  CalcMethod(_CALCE) \
  CalcMethod(_CALCG) \
  CalcMethod(_CALCB)

#define _RunCalcVar(CalcMethod,DType) \
  CalcMethod(_CALCE,DType) \
  CalcMethod(_CALCG,DType) \
  CalcMethod(_CALCB,DType)

#define _RunCalcVar2(CalcMethod,DTypeA,DTypeB) \
  CalcMethod(_CALCE,DTypeA,DTypeB) \
  CalcMethod(_CALCG,DTypeA,DTypeB) \
  CalcMethod(_CALCB,DTypeA,DTypeB)

#define _Array_Array(Method) \
  _Head(Method,_Array,_Array) { \
    assert(IsValid(F)); \
    F.Method##_FUNC(X,id.start,P.start,Geo,Method##_VAR,Buf); \
  }

namespace mysimulator {

  _RunCalc(_Array_Array)

}

#undef _Array_Array

#define _List_Array(Method) \
  _Head(Method,_List,_Array) { \
    Calc(F,X,id.infra,P,Buf,Geo,Method##_VAR); \
  }

#define _VList_Array(Method,VListType) \
  _Head(Method,VListType,_Array) { \
    assert(id.size==Buf.size); \
    for(unsigned int i=0;i<id.size;++i) \
      Calc(F,X,id[i],P,Buf[i],Geo,Method##_VAR); \
  }

namespace mysimulator {

  _RunCalc(_List_Array)
  _RunCalcVar(_VList_Array,_VList)
  _RunCalcVar(_VList_Array,_VarVList)

}

#undef _VList_Array
#undef _List_Array

#define _List_List(Method) \
  _Head(Method,_List,_List) { \
    Calc(F,X,id.infra,P.infra,Buf,Method##_VAR); \
  }

#define _VList_List(Method,VListType) \
  _Head(Method,VListType,_List) { \
    Calc(F,X,id,P.infra,Buf,Method##_VAR); \
  }

#define _List_VList(Method,VListType) \
  _Head(Method,_List,VListType) { \
    Calc(F,X,id.infra,P,Buf,Method##_VAR); \
  }

#define _VList_VList(Method,VListTypeA,VListTypeB) \
  _Head(Method,VListTypeA,VListTypeB) { \
    assert((id.size==P.size)&&(id.size==Buf.size)); \
    for(unsigned int i=0;i<id.size;++i) \
      Calc(F,X,id[i],P[i],Buf[i],Method##_VAR); \
  }

namespace mysimulator {

  _RunCalc(_List_List)
  _RunCalcVar(_List_VList,_VList)
  _RunCalcVar(_List_VList,_VarVList)
  _RunCalcVar(_VList_List,_VList)
  _RunCalcVar(_VList_List,_VarVList)
  _RunCalcVar2(_VList_VList,_VList,_VList)
  _RunCalcVar2(_VList_VList,_VList,_VarVList)
  _RunCalcVar2(_VList_VList,_VarVList,_VList)
  _RunCalcVar2(_VList_VList,_VarVList,_VarVList)

}

#undef _VList_VList
#undef _List_VList
#undef _VList_List
#undef _List_List

#define _ArrayForce_General(Method) \
  template <typename T,typename GeomType,typename IDType,typename ParamType,\
            typename BufferType> \
  void Calc(const _Array(_Force(GeomType,T))& F, const Array1DContent<T>* X, \
            const IDType& id, const ParamType& P, BufferType& Buf, \
            const GeomType& Geo, Method##_DCL) { \
    assert((F.size==id.size)&&(F.size==P.size)&&(F.size==Buf.size)); \
    for(unsigned int i=0;i<F.size;++i) \
      Calc(F[i],X,id[i],P[i],Buf[i],Geo,Method##_VAR); \
  }

namespace mysimulator {

  _RunCalc(_ArrayForce_General)

}

#undef _ArrayForce_General

#undef _RunCalcVar2
#undef _RunCalcVar
#undef _RunCalc

#undef _Head
#undef _Force

#undef _Low_VarVList
#undef _Low_VList
#undef _Low_RList
#undef _Low_List
#undef _Low_RArray
#undef _Low_Array

#undef _VarVList
#undef _VList
#undef _RList
#undef _List
#undef _RArray
#undef _Array
#undef _Single

#undef _CALCB_VAR
#undef _CALCG_VAR
#undef _CALCE_VAR

#undef _CALCB_FUNC
#undef _CALCG_FUNC
#undef _CALCE_FUNC

#undef _CALCB_DCL
#undef _CALCG_DCL
#undef _CALCE_DCL

namespace mysimulator {

  template <typename IFType, typename IDType, typename ParamType,
            typename BufferType, typename T, typename GeomType>
  void Calc(const IFType& F, const Array2DContent<T>& X, const IDType& id,
            const ParamType& P, BufferType& Buf, const GeomType& Geo,
            T& Energy) {
    Calc(F,X.infra.start,id,P,Buf,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename ParamType,
            typename BufferType, typename T, typename GeomType>
  void Calc(const IFType& F, const Array2DContent<T>& X, const IDType& id,
            const ParamType& P, BufferType& Buf, const GeomType& Geo,
            Array2DContent<T>& Grad) {
    Calc(F,X.infra.start,id,P,Buf,Geo,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename ParamType,
            typename BufferType, typename T, typename GeomType>
  void Calc(const IFType& F, const Array2DContent<T>& X, const IDType& id,
            const ParamType& P, BufferType& Buf, const GeomType& Geo,
            Array1DContent<T>* Grad) {
    Calc(F,X.infra.start,id,P,Buf,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename ParamType,
            typename BufferType, typename T, typename GeomType>
  void Calc(const IFType& F, const Array1DContent<T>* X, const IDType& id,
            const ParamType& P, BufferType& Buf, const GeomType& Geo,
            Array2DContent<T>& Grad) {
    Calc(F,X,id,P,Buf,Geo,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename ParamType,
            typename BufferType, typename T, typename GeomType>
  void Calc(const IFType& F, const Array2DContent<T>& X, const IDType& id,
            const ParamType& P, BufferType& Buf, const GeomType& Geo,
            T& Energy, Array2DContent<T>& Grad) {
    Calc(F,X.infra.start,id,P,Buf,Geo,Energy,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename ParamType,
            typename BufferType, typename T, typename GeomType>
  void Calc(const IFType& F, const Array2DContent<T>& X, const IDType& id,
            const ParamType& P, BufferType& Buf, const GeomType& Geo,
            T& Energy, Array1DContent<T>* Grad) {
    Calc(F,X.infra.start,id,P,Buf,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename ParamType,
            typename BufferType, typename T, typename GeomType>
  void Calc(const IFType& F, const Array1DContent<T>* X, const IDType& id,
            const ParamType& P, BufferType& Buf, const GeomType& Geo,
            T& Energy, Array2DContent<T>& Grad) {
    Calc(F,X,id,P,Buf,Geo,Energy,Grad.infra.start);
  }

}

#endif

