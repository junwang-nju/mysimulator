
#ifndef _Interaction_Func_Interface_H_
#define _Interaction_Func_Interface_H_

#include "unique/64bit/interface.h"
#include "interaction/func/name.h"
#include "interaction/buffer/interface.h"
#include <cassert>

namespace mysimulator {

  template <typename GeomType, typename T>
  struct InteractionFunc {

    public:

      typedef InteractionFunc<GeomType,T>   Type;

      typedef void (*EFuncType)(const T*,const Unique64Bit*,T*);
      typedef void (*GFuncType)(const T*,const Unique64Bit*,T*);
      typedef void (*BFuncType)(const T*,const Unique64Bit*,T*,T*);
      typedef void (*EMethodType)(T** const,const int*,const Unique64Bit*,
                                  const GeomType&,T&,InteractionBuffer<T>&,
                                  EFuncType);
      typedef void (*GMethodType)(T** const,const int*,const Unique64Bit*,
                                  const GeomType&,T**,InteractionBuffer<T>&,
                                  GFuncType);
      typedef void (*BMethodType)(T** const,const int*,const Unique64Bit*,
                                  const GeomType&,T&,T**,InteractionBuffer<T>&,
                                  BFuncType);

      InteractionFuncName   tag;
      EFuncType             EFunc;
      GFuncType             GFunc;
      BFuncType             BFunc;
      EMethodType           EMethod;
      GMethodType           GMethod;
      BMethodType           BMethod;

      InteractionFunc() : tag(UnknownInteactionFunc), EFunc(NULL), GFunc(NULL),
                          BFunc(NULL), EMethod(NULL), GMethod(NULL),
                          BMethod(NULL) {}
      ~InteractionFunc() { clearData(); }

      void clearData() {
        tag=UnknownInteactionFunc;
        EFunc=NULL; GFunc=NULL; BFunc=NULL;
        EMethod=NULL; GMethod=NULL; BMethod=NULL;
      }
      bool isvalid() const {
        return (tag!=UnknownInteactionFunc)&&
               ((EMethod!=NULL)||(GMethod!=NULL)||(BMethod!=NULL));
      }

      void Energy(
          T** const X, const int* id, const Unique64Bit* P,
          const GeomType& Geo, T& E, InteractionBuffer<T>& Buf) const {
        assert(EMethod!=NULL);
        EMethod(X,id,P,Geo,E,Buf,EFunc);
      }

      void Gradient(
          T** const X, const int* id, const Unique64Bit* P, const GeomType& Geo,
          T** G, InteractionBuffer<T>& Buf) const {
        assert(GMethod!=NULL);
        GMethod(X,id,P,Geo,G,Buf,GFunc);
      }

      void Both(
          T** const X, const int* id, const Unique64Bit* P, const GeomType& Geo,
          T& E, T** G, InteractionBuffer<T>& Buf) const {
        assert(BMethod!=NULL);
        BMethod(X,id,P,Geo,E,G,Buf,BFunc);
      }

    private:

      InteractionFunc(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename GT, typename T>
  void release(InteractionFunc<GT,T>& F) { F.clearData(); }

  template <typename GT, typename T>
  bool IsValid(const InteractionFunc<GT,T>& F) { return F.isvalid(); }

}

#endif

