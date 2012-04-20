
#ifndef _System_Interaction_Use_H_
#define _System_Interaction_Use_H_

#include "system/interaction/interface.h"
#include "array/common/refer.h"

#ifndef _UseFunc
#define _UseFunc(PART,PartType) \
  template <typename T,typename IDType,typename ParamType,typename GeomType,\
            typename BufferType,template<typename> class ContentType> \
  void use##PART(\
      SystemInteraction<T,IDType,ParamType,GeomType,BufferType,ContentType>& I,\
      const PartType i##PART) { \
    release(I.PART); refer(I.PART,i##PART); \
  }
#else
#error "Duplicate Definitions for _UseFunc"
#endif

#ifndef FuncType
#define FuncType InteractionFunc<GeomType,T>*
#else
#error "Duplicate Definitions for FuncType"
#endif

#ifndef _Use
#define _Use(PART) _UseFunc(PART,PART##Type)
#else
#error "Duplicate Definitions for _Use"
#endif

namespace mysimulator {

  _Use(Func)
  _Use(ID)
  _Use(Param)
  _Use(Buffer)
  _UseFunc(Geom,GeomType&)

}

#ifdef _UseFunc
#undef _UseFunc
#endif

#endif

