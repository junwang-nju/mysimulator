
#ifndef _System_Interaction_Load_H_
#define _System_Interaction_Load_H_

#include "system/interaction/interface.h"
#include "object/allocate.h"
#include "object/copy.h"
#include "interaction/func/allocate.h"
#include "interaction/func/copy.h"

#define _LoadDirect(PART) \
  template <typename T,typename IDType,typename ParamType,typename GeomType,\
            typename BufferType,template<typename> class VecType,\
            template<typename,template<typename>class> class SysContentType>\
  void load##PART(\
      SysInteraction<T,IDType,ParamType,GeomType,BufferType,VecType,SysContentType>& SI,\
      const PART##Type& i##PART) {\
    assert(IsValid(i##PART));\
    imprint(SI.PART,i##PART);\
    copy(SI.PART,i##PART);\
  }

#define _LoadObject(PART) \
  template <typename T,typename IDType,typename ParamType,typename GeomType,\
            typename BufferType,template<typename> class VecType,\
  template<typename,template<typename>class> class SysContentType>\
  void load##PART(\
      SysInteraction<T,IDType,ParamType,GeomType,BufferType,VecType,SysContentType>& SI,\
      const Object<PART##Type>& i##PART) {\
    assert(IsValid(i##PART));\
    load##PART(SI,i##PART());\
  }

#define _Load(PART) \
  _LoadDirect(PART) \
  _LoadObject(PART)

#define FuncType  Array1D<InteractionFunc<GeomType,T> >

namespace mysimulator {

  _Load(Func)
  _Load(ID)
  _Load(Param)
  _Load(Geom)
  _Load(Buffer)

}

#undef _Load
#undef _LoadObject
#undef _LoadDirect

#endif

