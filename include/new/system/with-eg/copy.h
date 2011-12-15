
#ifndef _System_With_EnergyGradient_Copy_H_
#define _System_With_EnergyGradient_Copy_H_

#include "system/with-eg/interface.h"
#include "system/with-e/copy.h"
#include "system/masked/component/copy.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType, SystemMaskModeName MN>
  void copy(SystemWithEG<T,IDType,ParamType,GeomType,SpaceType,MN>& S,
            const SystemWithEG<T,IDType,ParamType,GeomType,SpaceType,MN>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef
    typename SystemWithEG<T,IDType,ParamType,GeomType,SpaceType,MN>::ParentType
    Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.G,rS.G);
    copy(S.Mask,rS.Mask);
  }

}

#endif

