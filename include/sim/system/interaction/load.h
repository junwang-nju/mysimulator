
#ifndef _System_Interaction_Load_H_
#define _System_Interaction_Load_H_

#include "system/interaction/interface.h"

#ifndef _LoadFunc
#define _LoadFunc(PART,PartType) \
  template <typename T,typename IDType,typename ParamType,typename GeomType,\
            typename BufferType,template<typename> class ContentType> \
  void load##PART(\
      SystemInteraction<T,IDType,ParamType,GeomType,BufferType,ContentType>& I,\
      const PartType i##PART) { \
    Imprint(I.PART,i##PART); \
    Copy(I.PART,i##PART); \
  }
#else
#error "Duplicate Definition for _LoadFunc"
#endif

#ifndef FuncType
#define FuncType InteractionFunc<GeomType,T>*
#else
#error "Duplicate Definition for FuncType"
#endif

#ifndef _Load
#define _Load(PART)   _LoadFunc(PART,PART##Type)
#else
#error "Duplicate Definition for _Load"
#endif

namespace mysimulator {

  _Load(Func)
  _Load(ID)
  _Load(Param)
  _LoadFunc(Geom,GeomType&)
  _Load(Buffer)

}

#ifdef _Load
#undef _Load
#endif

#ifdef FuncType
#undef FuncType
#endif

#ifdef _LoadFunc
#undef _LoadFunc
#endif

#endif

