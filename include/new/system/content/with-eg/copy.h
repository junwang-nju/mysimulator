
#ifndef _System_Content_With_EnergyGradient_Copy_H_
#define _System_Content_With_EnergyGradient_Copy_H_

#include "system/content/with-eg/interface.h"
#include "system/content/with-e/copy.h"

namespace mysimulator {

  template <typename T, typename IDT, typename ParamT, typename GeomT,
            template <typename> class SpaceType>
  void copy(SystemWithEG<T,IDT,ParamT,GeomT,SpaceType>& S,
            const SystemWithEG<T,IDT,ParamT,GeomT,SpaceType>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef
      typename SystemWithEG<T,IDT,ParamT,GeomT,SpaceType>::ParentType
      Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.G,rS.G);
  }

}

#endif

