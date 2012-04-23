
#ifndef _System_Interaction_Use_H_
#define _System_Interaction_Use_H_

#include "system/interaction/interface.h"

#ifndef _USE
#define _USE(PART) \
  template <typename T,typename IDT,typename ParamT,typename GeomT,\
            typename BufferT,template<typename> class CT> \
  void Use##PART(SystemInteraction<T,IDT,ParamT,GeomT,BufferT,CT>& SI,\
                 PART##T& i##PART) { SI.PART.Refer(i##PART); }
#else
#error "Duplicate Definition for Macro _USE"
#endif

#ifndef FuncT
#define FuncT Array1D<InteractionFunc<GeomT,T> >
#else
#error "Duplicate Definition for Macro FuncT"
#endif

namespace mysimulator {

  _USE(Func)

}

#ifdef FuncT
#undef FuncT
#endif

namespace mysimulator {

  _USE(ID)
  _USE(Param)
  _USE(Geom)
  _USE(Buffer)

}

#ifdef _USE
#undef _USE
#endif

#endif

