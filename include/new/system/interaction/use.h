
#ifndef _System_Interaction_Use_H_
#define _System_Interaction_Use_H_

#include "system/interaction/interface.h"
#include "object/refer.h"

#define _UseDirect(PART) \
  template <typename T,typename IDType,typename ParamType,typename GeomType,\
            typename BufferType,template<typename> class VecType,\
            template<typename,template<typename>class> class SysContentType>\
  void use##PART(\
      SysInteraction<T,IDType,ParamType,GeomType,BufferType,VecType,SysContentType>& SI,\
      const PART##Type& i##PART) {\
    assert(IsValid(i##PART));\
    refer(SI.PART,i##PART);\
  }

#define _UseObject(PART) \
  template <typename T,typename IDType,typename ParamType,typename GeomType,\
            typename BufferType, template<typename> class VecType,\
            template<typename,template<typename>class> class SysContentType>\
  void use##PART(\
      SysInteraction<T,IDType,ParamType,GeomType,BufferType,VecType,SysContentType>& SI,\
      const Object<PART##Type>& i##PART) {\
    assert(IsValid(i##PART));\
    refer(SI.PART,i##PART);\
  }

#define _Use(PART) \
  _UseDirect(PART) \
  _UseObject(PART)

#define FuncType  Array1D<InteractionFunc<GeomType,T> >

namespace mysimulator {

  _Use(Func)
  _Use(ID)
  _Use(Param)
  _Use(Buffer)
  _Use(Geom)

}

#undef FuncType

#undef _Use
#undef _UseObject
#undef _UseDirect

#endif

