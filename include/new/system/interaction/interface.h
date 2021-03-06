
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "object/interface.h"
#include "array/1d/interface.h"
#include "interaction/func/interface.h"

#define _WorkParam const FuncType&,const VecType<T>&,const IDType&,const ParamType&,BufferType&,const GeomType&

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType, template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct SysInteraction {

    public:

      typedef SysInteraction<T,IDType,ParamType,GeomType,BufferType,VecType,
                             SysContentType>
              Type;
      typedef Array1D<InteractionFunc<GeomType,T> >   FuncType;
      typedef typename SysContentType<T,VecType>::EGDataType   EGDataType;
      typedef void (*EWorkType)(_WorkParam,T&);
      typedef void (*GWorkType)(_WorkParam,VecType<T>&);
      typedef void (*BWorkType)(_WorkParam,T&,VecType<T>&);

      FuncType            Func;
      Object<IDType>      ID;
      Object<ParamType>   Param;
      Object<InteractionBuffer<T> > Buffer;
      Object<GeomType>    Geom;
      Object<EGDataType>  EGData;
      EWorkType WorkE;
      GWorkType WorkG;
      BWorkType WorkB;

      SysInteraction() : Func(), ID(), Param(), Buffer(), Geom(), EGData(),
                         WorkE(NULL), WorkG(NULL), WorkB(NULL) {}
      ~SysInteraction() { clearData(); }

      void clearData() {
        WorkB=NULL; WorkG=NULL; WorkE=NULL;
        release(EGData);release(Geom);release(Buffer);release(Param);
        release(ID);release(Func);
      }
      bool isvalid() const {
        return IsValid(Func)&&IsValid(ID)&&IsValid(Param)&&IsValid(Buffer)&&
               IsValid(Geom)&&IsValid(EGData)&&IsValid(WorkB)&&IsValid(WorkG)&&
               IsValid(WorkE);
      }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(SysInteraction<T,IDT,PT,GT,BT,VT,SCT>& I) { I.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const SysInteraction<T,IDT,PT,GT,BT,VT,SCT>& I) {
    return I.isvalid();
  }

}

#undef _WorkParam

#include "system/interaction/work-mode-name.h"
#include "system/interaction/work-func.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SetWorkFunc(SysInteraction<T,IDT,PT,GT,BT,VT,SCT>& SI,
                   const SystemInteractionWorkModeName& WN) {
    switch(WN) {
      case SingleInteraction:
        SI.WorkE=_EWorkSingle<T,IDT,PT,GT,BT,VT>;
        SI.WorkG=_GWorkSingle<T,IDT,PT,GT,BT,VT>;
        SI.WorkB=_BWorkSingle<T,IDT,PT,GT,BT,VT>;
        break;
      case ArrayInteraction:
        SI.WorkE=_EWorkArray<T,IDT,PT,GT,BT,VT>;
        SI.WorkG=_GWorkArray<T,IDT,PT,GT,BT,VT>;
        SI.WorkB=_BWorkArray<T,IDT,PT,GT,BT,VT>;
        break;
      default:
        Error("Unknown Work Mode for System Interaction!");
    }
  }

}

#endif

