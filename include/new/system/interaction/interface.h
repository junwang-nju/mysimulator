
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "object/interface.h"
#include "interaction/func/interface.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct SysInteraction {

    public:

      typedef SysInteraction<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;
      typedef InteractionFunc<GeomType,T>   FuncType;
      typedef typename SysContentType<T,VecType>::EGDataType   EGDataType;

      Object<FuncType>    Func;
      Object<IDType>      ID;
      Object<ParamType>   Param;
      Object<GeomType>    Geom;
      Object<EGDataType>  EGData;

      SysInteraction() : Func(), ID(), Param(), Geom(), EGData() {}
      ~SysInteraction() { clearData(); }

      void clearData() {
        release(EGData);release(Geom);release(Param);release(ID);release(Func);
      }
      bool isvalid() const {
        return IsValid(Func)&&IsValid(ID)&&IsValid(Param)&&IsValid(Geom)&&
               IsValid(EGData);
      }

  };

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(SysInteraction<T,IDT,PT,GT,VT,SCT>& I) { I.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const SysInteraction<T,IDT,PT,GT,VT,SCT>& I) {
    return I.isvalid();
  }

}

#endif

