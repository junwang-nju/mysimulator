
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "interaction/calc.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType,template<typename>class ContentType>
  struct SystemInteraction {

    public:

      typedef
        SystemInteraction<T,IDType,ParamType,GeomType,BufferType,ContentType>
        Type;
      typedef typename ContentType<T>::EGDataType EGDataType;

      Array1D<InteractionFunc<GeomType,T> >   Func;
      IDType                                  ID;
      ParamType                               Param;
      BufferType                              Buffer;
      GeomType                                Geom;
      EGDataType                              EGData;

      SystemInteraction() : Func(),ID(),Param(),Buffer(),Geom(),EGData() {}
      ~SystemInteraction() { Clear(); }

      void Clear() {
        EGData.Clear(); Geom.Clear(); Buffer.Clear(); Param.Clear();
        ID.Clear(); Func.Clear();
      }
      bool IsValid() const {
        return Func.IsValid()&&ID.IsValid()&&Param.IsValid()&&
               Buffer.IsValid()&&Geom.IsValid()&&EGData.IsValid();
      }

      void AllocateData() { EGData.Allocate(); }
      void AllocateData(const Array2D<T>& X) { EGData.Allocate(X); }

      void Calc(const Array1D<Array1D<T> >& X,T& Energy) {
        Calc(Func,X,ID,Param,Buffer,Geom,Energy);
      }
      void Calc(const Array1D<Array1D<T> >& X,Array1D<Array1D<T> >& Grad) {
        Calc(Func,X,ID,Param,Buffer,Geom,Grad);
      }
      void Calc(const Array1D<Array1D<T> >& X,T& Energy,
                Array1D<Array1D<T> >& Grad) {
        Calc(Func,X,ID,Param,Buffer,Geom,Energy,Grad);
      }

  };

}

#endif

