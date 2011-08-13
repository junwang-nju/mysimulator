
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/func/interface.h"
#include "array/3d/interface.h"

#define _CALCE(typeIF,typeID,typePrm) \
  template <typename T, typename GeomType>\
  void Calc(typeIF(GeomType,T)& F, const Array1DContent<T>* X,\
            const typeID(int)& id, const typePrm(Unique64Bit)& P,\
            const GeomType& Geo, T& Energy)

#define _CALCG(typeIF,typeID,typePrm) \
  template <typename T, typename GeomType>\
  void Calc(typeIF(GeomType,T)& F, const Array1DContent<T>* X,\
            const typeID(int)& id, const typePrm(Unique64Bit)& P,\
            const GeomType& Geo, Array1DContent<T>* Grad)

#define _CALCB(typeIF,typeID,typePrm) \
  template <typename T, typename GeomType>\
  void Calc(typeIF(GeomType,T)& F, const Array1DContent<T>* X,\
            const typeID(int)& id, const typePrm(Unique64Bit)& P,\
            const GeomType& Geo, T& Energy, Array1DContent<T>* Grad)

#define _CALCE_VAR  Energy
#define _CALCG_VAR  Grad
#define _CALCB_VAR  Energy,Grad

#define _Single(DT)     Array1DContent<DT>
#define _Set(DT)        Array2DContent<DT>
#define _Array(DT)      Array1DContent<Array1DContent<DT> >
#define _Pile(DT)       Array3DContent<DT>

#define _SingleForce(GEO,DT)  InteractionFunc<GEO,DT>
#define _ArrayForce(GEO,DT)   Array1DContent<InteractionFunc<GEO,DT> >

#define _CALC(CalcMethod) \
  CalcMethod(_CALCE)\
  CalcMethod(_CALCG)\
  CalcMethod(_CALCB)

namespace mysimulator {

  _CALCE(_SingleForce,_Single,_Single) {
    assert(IsValid(F));
    F.Energy(X,id.start,P.start,Geo,Energy);
  }

  _CALCG(_SingleForce,_Single,_Single) {
    assert(IsValid(F));
    F.Gradient(X,id.start,P.start,Geo,Grad);
  }

  _CALCB(_SingleForce,_Single,_Single) {
    assert(IsValid(F));
    F.Both(X,id.start,P.start,Geo,Energy,Grad);
  }

}

#define _Single_Array_Single(CalcType) \
  CalcType(_SingleForce,_Array,_Single) {\
    typedef Array1DContent<int> Type;\
    Type* p=const_cast<Type*>(id.start);\
    Type* e=p+id.size;\
    for(;p!=e;) Calc(F,X,*(p++),P,Geo,CalcType##_VAR);\
  }

#define _Single_Single_Array(CalcType) \
  CalcType(_SingleForce,_Single,_Array) {\
    typedef Array1DContent<Unique64Bit> Type;\
    Type* p=const_cast<Type*>(P.start);\
    Type* e=p+P.size;\
    for(;p!=e;) Calc(F,X,id,*(p++),Geo,CalcType##_VAR);\
  }

#define _Single_Array_Array(CalcType) \
  CalcType(_SingleForce,_Array,_Array) {\
    unsigned int n=(id.size<P.size?id.size:P.size);\
    typedef Array1DContent<int>   TypeID;\
    typedef Array1DContent<Unique64Bit> TypePrm;\
    TypeID* p=const_cast<TypeID*>(id.start);\
    TypeID* e=p+n;\
    TypePrm* q=const_cast<TypePrm*>(P.start);\
    for(;p!=e;) Calc(F,X,*(p++),*(q++),Geo,CalcType##_VAR);\
  }

#define _Array_Single_Array(CalcType) \
  CalcType(_ArrayForce,_Single,_Array) {\
    unsigned int n=(F.size<P.size?F.size:P.size);\
    typedef InteractionFunc<GeomType,T>   TypeIF;\
    typedef Array1DContent<Unique64Bit>   TypePrm;\
    TypeIF* p=const_cast<TypeIF*>(F.start);\
    TypeIF* e=p+n;\
    TypePrm* q=const_cast<TypePrm*>(P.start);\
    for(;p!=e;) Calc(*(p++),X,id,*(q++),Geo,CalcType##_VAR);\
  }

#define _Array_Array_Array(CalcType) \
  CalcType(_ArrayForce,_Array,_Array) {\
    unsigned int n;\
    n=(F.size<id.size?F.size:id.size);\
    n=(n<P.size?n:P.size);\
    typedef InteractionFunc<GeomType,T>   TypeIF;\
    typedef Array1DContent<int> TypeID;\
    typedef Array1DContent<Unique64Bit>   TypePrm;\
    TypeIF* p=const_cast<TypeIF*>(F.start);\
    TypeIF* e=p+n;\
    TypeID* q=const_cast<TypeID*>(id.start);\
    TypePrm* r=const_cast<TypePrm*>(P.start);\
    for(;p!=e;) Calc(*(p++),X,*(q++),*(r++),Geo,CalcType##_VAR);\
  }

namespace mysimulator {

  _CALC(_Single_Array_Single)
  _CALC(_Single_Single_Array)
  _CALC(_Single_Array_Array)
  _CALC(_Array_Single_Array)
  _CALC(_Array_Array_Array)

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Set(IDType)& id,
            const PrmType& P, const GeomType& Geo, T& Energy) {
    Calc(F,X,id.infra,P,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Set(IDType)& id,
            const PrmType& P, const GeomType& Geo, Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Set(IDType)& id,
            const PrmType& P, const GeomType& Geo, T& Energy,
            Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const _Set(PrmType)& P, const GeomType& Geo, T& Energy) {
    Calc(F,X,id,P.infra,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const _Set(PrmType)& P, const GeomType& Geo,
            Array1DContent<T>* Grad) {
    Calc(F,X,id,P.infra,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const _Set(PrmType)& P, const GeomType& Geo, T& Energy,
            Array1DContent<T>* Grad) {
    Calc(F,X,id,P.infra,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Set(IDType)& id,
            const _Set(PrmType)& P, const GeomType& Geo, T& Energy) {
    Calc(F,X,id.infra,P.infra,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Set(IDType)& id,
            const _Set(PrmType)& P, const GeomType& Geo,
            Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P.infra,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Set(IDType)& id,
            const _Set(PrmType)& P, const GeomType& Geo, T& Energy,
            Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P.infra,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Pile(IDType)& id,
            const PrmType& P, const GeomType& Geo, T& Energy) {
    Calc(F,X,id.infra,P,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Pile(IDType)& id,
            const PrmType& P, const GeomType& Geo, Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Pile(IDType)& id,
            const PrmType& P, const GeomType& Geo, T& Energy,
            Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const _Pile(PrmType)& P, const GeomType& Geo, T& Energy) {
    Calc(F,X,id,P.infra,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const _Pile(PrmType)& P, const GeomType& Geo,
            Array1DContent<T>* Grad) {
    Calc(F,X,id,P.infra,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const IDType& id,
            const _Pile(PrmType)& P, const GeomType& Geo, T& Energy,
            Array1DContent<T>* Grad) {
    Calc(F,X,id,P.infra,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Pile(IDType)& id,
            const _Pile(PrmType)& P, const GeomType& Geo, T& Energy) {
    Calc(F,X,id.infra,P.infra,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Pile(IDType)& id,
            const _Pile(PrmType)& P, const GeomType& Geo,
            Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P.infra,Geo,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const Array1DContent<T>* X, const _Pile(IDType)& id,
            const _Pile(PrmType)& P, const GeomType& Geo, T& Energy,
            Array1DContent<T>* Grad) {
    Calc(F,X,id.infra,P.infra,Geo,Energy,Grad);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy) {
    Calc(F,X.infra.start,id,P,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, _Set(T)& Grad) {
    Calc(F,X.infra.start,id,P,Geo,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Set(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy, _Set(T)& Grad) {
    Calc(F,X.infra.start,id,P,Geo,Energy,Grad.infra.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy) {
    Calc(F,X.start,id,P,Geo,Energy);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, _Array(T)& Grad) {
    Calc(F,X.start,id,P,Geo,Grad.start);
  }

  template <typename IFType, typename IDType, typename PrmType,
            typename GeomType, typename T>
  void Calc(IFType& F, const _Array(T)& X, const IDType& id, const PrmType& P,
            const GeomType& Geo, T& Energy, _Array(T)& Grad) {
    Calc(F,X.start,id,P,Geo,Energy,Grad.start);
  }

}

#undef _Array_Array_Array
#undef _Array_Single_Array
#undef _Single_Array_Array
#undef _Single_Single_Array
#undef _Single_Array_Single

#undef _CALC
#undef _ArrayForce
#undef _SingleForce
#undef _Pile
#undef _Array
#undef _Set
#undef _Single
#undef _CALCB_VAR
#undef _CALCG_VAR
#undef _CALCE_VAR
#undef _CALCB
#undef _CALCG
#undef _CALCE


#endif

