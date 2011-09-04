
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/func/interface.h"
#include "array/1d/interface.h"
#include "array/3d/interface.h"

#define _CALCE_DCL  T& Energy
#define _CALCG_DCL  Array1DContent<T>* Grad
#define _CALCB_DCL  _CALCE_DCL,_CALCG_DCL

#define _CALCE_FUNC   Energy
#define _CALCG_FUNC   Gradient
#define _CALCB_FUNC   Both

#define _CALCE_VAR  Energy
#define _CALCG_VAR  Grad
#define _CALCB_VAR  Energy,Grad

#define _Single(DT)     Array1DContent<DT>
#define _Set(DT)        Array2DContent<DT>
#define _IArray(DT)     Array1DContent<Array1DContent<DT> >
#define _Array(DT)      Array1DContent<Array1D<DT> >
#define _Pile(DT)       Array3DContent<DT>

#define _SingleForce(GEO,DT)  InteractionFunc<GEO,DT>
#define _ArrayForce(GEO,DT)   Array1DContent<InteractionFunc<GEO,DT> >

#define _IArray_Line    Array1DContent
#define _Array_Line     Array1D

#define _Head(Method,typeIF,typeID,typePrm) \
  template <typename T, typename GeomType>\
  void Calc(typeIF(GeomType,T)& F, const Array1DContent<T>* X,\
            const typeID(int)& id, const typePrm(Unique64Bit)& P,\
            const GeomType& Geo, Method##_DCL)

#define _Single_Single_Single(Method) \
  _Head(Method,_SingleForce,_Single,_Single) {\
    assert(IsValid(F));\
    F.Method##_FUNC(X,id.start,P.start,Geo,Method##_VAR);\
  }

namespace mysimulator {

  _Single_Single_Single(_CALCE)
  _Single_Single_Single(_CALCG)
  _Single_Single_Single(_CALCB)

}

#undef _Single_Single_Single

#define _Single_Array_Single(Method,AType) \
  _Head(Method,_SingleForce,AType,_Single) {\
    typedef AType##_Line<int> Type;\
    Type* p=const_cast<Type*>(id.start);\
    Type* e=p+id.size;\
    for(;p!=e;) Calc(F,X,*(p++),P,Geo,Method##_VAR);\
  }

#define _Single_Single_Array(Method,AType) \
  _Head(Method,_SingleForce,_Single,AType) {\
    typedef AType##_Line<Unique64Bit> Type;\
    Type* p=const_cast<Type*>(P.start);\
    Type* e=p+P.size;\
    for(;p!=e;) Calc(F,X,id,*(p++),Geo,Method##_VAR);\
  }

#define _Single_Array_Array(Method,AType1,AType2) \
  _Head(Method,_SingleForce,AType1,AType2) {\
    unsigned int n=(id.size<P.size?id.size:P.size);\
    typedef AType1##_Line<int>   TypeID;\
    typedef AType2##_Line<Unique64Bit> TypePrm;\
    TypeID* p=const_cast<TypeID*>(id.start);\
    TypeID* e=p+n;\
    TypePrm* q=const_cast<TypePrm*>(P.start);\
    for(;p!=e;) Calc(F,X,*(p++),*(q++),Geo,Method##_VAR);\
  }

#define _Array_Single_Array(Method,AType) \
  _Head(Method,_ArrayForce,_Single,AType) {\
    unsigned int n=(F.size<P.size?F.size:P.size);\
    typedef InteractionFunc<GeomType,T>   TypeIF;\
    typedef AType##_Line<Unique64Bit>   TypePrm;\
    TypeIF* p=const_cast<TypeIF*>(F.start);\
    TypeIF* e=p+n;\
    TypePrm* q=const_cast<TypePrm*>(P.start);\
    for(;p!=e;) Calc(*(p++),X,id,*(q++),Geo,Method##_VAR);\
  }

#define _Array_Array_Array(Method,AType1,AType2) \
  _Head(Method,_ArrayForce,AType1,AType2) {\
    unsigned int n;\
    n=(F.size<id.size?F.size:id.size);\
    n=(n<P.size?n:P.size);\
    typedef InteractionFunc<GeomType,T>   TypeIF;\
    typedef AType1##_Line<int> TypeID;\
    typedef AType2##_Line<Unique64Bit>   TypePrm;\
    TypeIF* p=const_cast<TypeIF*>(F.start);\
    TypeIF* e=p+n;\
    TypeID* q=const_cast<TypeID*>(id.start);\
    TypePrm* r=const_cast<TypePrm*>(P.start);\
    for(;p!=e;) Calc(*(p++),X,*(q++),*(r++),Geo,Method##_VAR);\
  }

#define _CALC1(CalcMethod,AType) \
  CalcMethod(_CALCE,AType)\
  CalcMethod(_CALCG,AType)\
  CalcMethod(_CALCB,AType)

#define _CALC2(CalcMethod,AType1,AType2) \
  CalcMethod(_CALCE,AType1,AType2)\
  CalcMethod(_CALCG,AType1,AType2)\
  CalcMethod(_CALCB,AType1,AType2)

namespace mysimulator {

  _CALC1(_Single_Array_Single,_Array)
  _CALC1(_Single_Array_Single,_IArray)

  _CALC1(_Single_Single_Array,_Array)
  _CALC1(_Single_Single_Array,_IArray)

  _CALC2(_Single_Array_Array,_Array,_Array)
  _CALC2(_Single_Array_Array,_IArray,_Array)
  _CALC2(_Single_Array_Array,_Array,_IArray)
  _CALC2(_Single_Array_Array,_IArray,_IArray)

  _CALC1(_Array_Single_Array,_Array)
  _CALC1(_Array_Single_Array,_IArray)

  _CALC2(_Array_Array_Array,_Array,_Array)
  _CALC2(_Array_Array_Array,_IArray,_Array)
  _CALC2(_Array_Array_Array,_Array,_IArray)
  _CALC2(_Array_Array_Array,_IArray,_IArray)

}

#undef _CALC2
#undef _CALC1

#undef _Array_Array_Array
#undef _Array_Single_Array

#undef _Single_Array_Array
#undef _Single_Single_Array
#undef _Single_Array_Single

#undef _Array_Line
#undef _IArray_Line

#undef _Head

#define _Head(Method,typeID,typePrm) \
  template <typename IFType, typename IDType, typename PrmType, typename GeomType,\
            typename T>\
  void Calc(IFType& F, const Array1DContent<T>* X, const typeID(IDType)& id,\
            const typePrm(PrmType)& P, const GeomType& Geo, Method##_DCL)

#define _Single_Set_Single(Method) \
  _Head(Method,_Set,_Single) { Calc(F,X,id.infra,P,Geo,Method##_VAR); }

#define _Single_Single_Set(Method) \
  _Head(Method,_Single,_Set) { Calc(F,X,id,P.infra,Geo,Method##_VAR); }

#define _Single_Set_Set(Method) \
  _Head(Method,_Set,_Set) { Calc(F,X,id.infra,P.infra,Geo,Method##_VAR); }

#define _Single_Pile_Single(Method) \
  _Head(Method,_Pile,_Single) { Calc(F,X,id.infra,P,Geo,Method##_VAR); }

#define _Single_Single_Pile(Method) \
  _Head(Method,_Single,_Pile) { Calc(F,X,id,P.infra,Geo,Method##_VAR); }

#define _Single_Pile_Pile(Method) \
  _Head(Method,_Pile,_Pile) { Calc(F,X,id.infra,P.infra,Geo,Method##_VAR); }

#define _CALC(CalcMethod) \
  CalcMethod(_CALCE)\
  CalcMethod(_CALCG)\
  CalcMethod(_CALCB)

namespace mysimulator {

  _CALC(_Single_Set_Single)
  _CALC(_Single_Single_Set)
  _CALC(_Single_Set_Set)

  _CALC(_Single_Pile_Single)
  _CALC(_Single_Single_Pile)
  _CALC(_Single_Pile_Pile)

}

#undef _CALC

#undef _Single_Pile_Pile
#undef _Single_Single_Pile
#undef _Single_Pile_Single

#undef _Single_Set_Set
#undef _Single_Single_Set
#undef _Single_Set_Single

#undef _Head

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

  template <typename T>
  Array1DContent<T>* _CalcWrap(const _Set(T)& C) { return C.infra.start; }

  template <typename T>
  Array1DContent<T>* _CalcWrap(const _Array(T)& C) { return C.start; }

  template <typename T>
  Array1DContent<T>* _CalcWrap(const Array1DContent<T>* const& C) {
    return const_cast<Array1DContent<T>*>(C); }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy) {
    Calc(F,X.infra.start,id,P,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy) {
    Calc(F,X.start,id,P,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, Array1DContent<T>* Grad) {
    Calc(F,X.infra.start,id,P,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, Array1DContent<T>* Grad) {
    Calc(F,X.start,id,P,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const PrmType& P, const GeomType& Geo, _Set(T)& Grad) {
    Calc(F,X,id,P,Geo,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, _Set(T)& Grad) {
    Calc(F,X.infra.start,id,P,Geo,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, _Set(T)& Grad) {
    Calc(F,X.start,id,P,Geo,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const PrmType& P, const GeomType& Geo, _Array(T)& Grad) {
    Calc(F,X,id,P,Geo,Grad.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, _Array(T)& Grad) {
    Calc(F,X.infra.start,id,P,Geo,Grad.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, _Array(T)& Grad) {
    Calc(F,X.start,id,P,Geo,Grad.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy, Array1DContent<T>* Grad) {
    Calc(F,X.infra.start,id,P,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy, Array1DContent<T>* Grad) {
    Calc(F,X.start,id,P,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const PrmType& P, const GeomType& Geo, T& Energy, _Set(T)& Grad) {
    Calc(F,X,id,P,Geo,Energy,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, T& Energy, _Set(T)& Grad) {
    Calc(F,X.infra.start,id,P,Geo,Energy,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, T& Energy, _Set(T)& Grad) {
    Calc(F,X.start,id,P,Geo,Energy,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const PrmType& P, const GeomType& Geo, T& Energy, _Array(T)& Grad) {
    Calc(F,X,id,P,Geo,Energy,Grad.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, T& Energy, _Array(T)& Grad) {
    Calc(F,X.infra.start,id,P,Geo,Energy,Grad.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
           typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id,
            const PrmType& P, const GeomType& Geo, T& Energy, _Array(T)& Grad) {
    Calc(F,X.start,id,P,Geo,Energy,Grad.start);
  }

}

#undef _ArrayForce
#undef _SingleForce

#undef _Pile
#undef _Array
#undef _IArray
#undef _Set
#undef _Single

#endif

