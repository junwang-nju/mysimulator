
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
      ~SystemInteraction() { Clear(*this); }

      bool IsValid() const {
        return Func.IsValid()&&ID.IsValid()&&Param.IsValid()&&
               Buffer.IsValid()&&Geom.IsValid()&&EGData.IsValid();
      }

      void AllocateData() { EGData.Allocate(); }
      void AllocateData(const Array2D<T>& X) { EGData.Allocate(X); }

      void WorkCalc(const Array1D<Array1D<T> >& X,T& Energy) {
        Calc(Func,X,ID,Param,Buffer,Geom,Energy);
      }
      void WorkCalc(const Array1D<Array1D<T> >& X,Array1D<Array1D<T> >& Grad) {
        Calc(Func,X,ID,Param,Buffer,Geom,Grad);
      }
      void WorkCalc(const Array1D<Array1D<T> >& X,T& Energy,
                Array1D<Array1D<T> >& Grad) {
        Calc(Func,X,ID,Param,Buffer,Geom,Energy,Grad);
      }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename>class CT>
  void Clear(SystemInteraction<T,IDT,PT,GT,BT,CT>& SI) {
    Clear(SI.EGData); Clear(SI.Geom); Clear(SI.Buffer); Clear(SI.Param);
    Clear(SI.ID); Clear(SI.Func);
  }

}

#endif

