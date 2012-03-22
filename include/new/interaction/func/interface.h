
#ifndef _Interaction_Func_Interface_H_
#define _Interaction_Func_Interface_H_

#include "unique/64bit/interface.h"
#include "array/2d/interface.h"
#include "interaction/func/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  struct InteractionFunc {

    public:

      typedef InteractionFunc<GeomType,T>   Type;

      typedef void (*EFuncType)(const T*,const Unique64Bit*,T*);
      typedef void (*GFuncType)(const T*,const Unique64Bit*,T*);
      typedef void (*BFuncType)(const T*,const Unique64Bit*,T*,T*);
      typedef void (*EMethodType)(const Array1DContent<T>*,const int*,
          const Unique64Bit*,const GeomType&,T&,Array1DContent<T>*,EFuncType);
      typedef void (*GMethodType)(const Array1DContent<T>*,const int*,
          const Unique64Bit*,const GeomType&,Array1DContent<T>*,
          Array1DContent<T>*,GFuncType);
      typedef void (*BMethodType)(const Array1DContent<T>*,const int*,
          const Unique64Bit*,const GeomType&,T&,Array1DContent<T>*,
          Array1DContent<T>*,BFuncType);

      InteractionFuncName tag;
      Array2D<T> tmvec;
      EFuncType EFunc;
      GFuncType GFunc;
      BFuncType BFunc;
      EMethodType EMethod;
      GMethodType GMethod;
      BMethodType BMethod;

      InteractionFunc() : tag(UnknownInteractionFunc), tmvec(),
                          EFunc(NULL), GFunc(NULL), BFunc(NULL),
                          EMethod(NULL), GMethod(NULL), BMethod(NULL) {}
      ~InteractionFunc() { clearData(); }

      void clearData() {
        tag=UnknownInteractionFunc;
        release(tmvec);
        EFunc=NULL;   GFunc=NULL;   BFunc=NULL;
        EMethod=NULL; GMethod=NULL; BMethod=NULL;
      }
      const bool isvalid() const {
        return (tag!=UnknownInteractionFunc)&&
               ((EMethod!=NULL)||(GMethod!=NULL)||(BMethod!=NULL));
      }

      void Energy(
          const Array1DContent<T>* X, const int* id,
          const Unique64Bit* P, const GeomType& Geo, T& E) {
        assert(IsValid(EMethod));
        EMethod(X,id,P,Geo,E,tmvec.infra.start,EFunc);
      }

      void Gradient(
          const Array1DContent<T>* X, const int* id,
          const Unique64Bit* P, const GeomType& Geo, Array1DContent<T>* Grad) {
        assert(IsValid(GMethod));
        GMethod(X,id,P,Geo,Grad,tmvec.infra.start,GFunc);
      }

      void Both(
          const Array1DContent<T>* X, const int* id,
          const Unique64Bit* P, const GeomType& Geo, T& E,
          Array1DContent<T>* Grad) {
        assert(IsValid(BMethod));
        BMethod(X,id,P,Geo,E,Grad,tmvec.infra.start,BFunc);
      }

    private:

      InteractionFunc(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename GeomType, typename T>
  bool IsValid(const InteractionFunc<GeomType,T>& F) { return F.isvalid(); }

  template <typename GeomType, typename T>
  void release(InteractionFunc<GeomType,T>& F) { F.clearData(); }

}

#endif

