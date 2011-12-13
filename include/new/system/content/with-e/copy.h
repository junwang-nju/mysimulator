
#ifndef _System_Content_With_Energy_Copy_H_
#define _System_Content_With_Energy_Copy_H_

#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType>
  void copy(SystemWithE<T,IDType,ParamType,GeomType,SpaceType>& S,
            const SystemWithE<T,IDType,ParamType,GeomType,SpaceType>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef
      typename SystemWithE<T,IDType,ParamType,GeomType,SpaceType>::ParentType
      Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.Func,rS.Func);
    copy(S.ID,rS.ID);
    copy(S.Param,rS.Param);
    copy(S.Geo,rS.Geo);
    copy(S.Energy,rS.Energy);
  }

}

#endif
