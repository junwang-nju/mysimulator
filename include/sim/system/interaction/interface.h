
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "interaction/func/interface.h"

#ifndef _WorkParam
#define _WorkParam \
  const InteractionFunc<GeomType,T>*,const DataType,const IDType&,\
  const ParamType,BufferType,const GeomType&
#else
#error "Duplicate Definition for _WorkParam
#endif

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType,typename DataType,
            template<typename,typename> class ContentType>
  struct SystemInteraction {

    public:

      typedef
        SystemInteraction<T,IDType,ParamType,GeomType,BufferType,DataType,
                          ContentType>
        Type;
      typedef typename ContentType<T,DataType>::EGDataType  EGDataType;
      typedef void (*EWorkType)(_WorkParam,T&);
      typedef void (*GWorkType)(_WorkParam,DataType);
      typedef void (*BWorkType)(_WorkParam,T&,DataType);

      InteractionFunc<GeomType,T>*    Func;
      IDType                          ID;
      ParamType                       Param;
      BufferType                      Buffer;
      GeomType                        Geom;
      EGDataType                      EGData;
      EWorkType                       WorkE;
      GWorkType                       WorkG;
      BWorkType                       WorkB;

      SystemInteraction()
        : Func(NULL), ID(NULL), Param(NULL), Buffer(NULL), Geom(), EGData(),
          WorkE(NULL), WorkG(NULL), WorkB(NULL) {}
      ~SystemInteraction() { clearData(); }

      void clearData() {
        WorkB=NULL; WorkG=NULL; WorkE=NULL;
        release(EGData); release(Geom); release(Buffer); release(Param);
        release(ID);  release(Func);
      }
      bool isvalid() const {
        return (Func!=NULL)&&(ID!=NULL)&&(Param!=NULL)&&(Buffer!=NULL)&&
               IsValid(Geom)&&IsValid(EGData)&&
               (WorkE!=NULL)&&(WorkG!=NULL)&&(WorkB!=NULL);
      }

    private:

      SystemInteraction(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            typename DT,template<typename,typename> class CT>
  void release(SystemInteraction<T,IDT,PT,GT,BT,DT,CT>& I) { I.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            typename DT,template<typename,typename> class CT>
  bool IsValid(const SystemInteraction<T,IDT,PT,GT,BT,DT,CT>& I) {
    return I.isvalid();
  }

}

#ifdef _WorkParam
#undef _WorkParam
#endif

#endif

