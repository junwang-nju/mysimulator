
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "interaction/calc.h"
#include "array/1d/release.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType,template<typename> class ContentType>
  struct SystemInteraction {

    public:

      typedef
        SystemInteraction<T,IDType,ParamType,GeomType,BufferType,ContentType>
        Type;
      typedef typename ContentType<T>::EGDataType  EGDataType;

      InteractionFunc<GeomType,T>*    Func;
      IDType                          ID;
      ParamType                       Param;
      BufferType                      Buffer;
      GeomType                        Geom;
      EGDataType                      EGData;

      SystemInteraction()
        : Func(NULL), ID(NULL), Param(NULL), Buffer(NULL), Geom(), EGData() {}
      ~SystemInteraction() { clearData(); }

      void clearData() {
        release(EGData); release(Geom); release(Buffer); release(Param);
        release(ID);  release(Func);
      }
      bool isvalid() const {
        return (Func!=NULL)&&(ID!=NULL)&&(Param!=NULL)&&(Buffer!=NULL)&&
               IsValid(Geom)&&IsValid(EGData);
      }

      void WorkE(const T** X, T& Energy) {
        Calc(Func,X,ID,Param,Buffer,Geom,Energy);
      }
      void WorkG(const T** X, T** Grad) {
        Calc(Func,X,ID,Param,Buffer,Geom,Grad);
      }
      void WorkB(const T** X, T& Energy, T** Grad) {
        Calc(Func,X,ID,Param,Buffer,Geom,Energy,Grad);
      }

    private:

      SystemInteraction(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void release(SystemInteraction<T,IDT,PT,GT,BT,CT>& I) { I.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  bool IsValid(const SystemInteraction<T,IDT,PT,GT,BT,CT>& I) {
    return I.isvalid();
  }

}

#ifdef _WorkParam_
#undef _WorkParam_
#endif

#endif

