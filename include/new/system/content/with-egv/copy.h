
#ifndef _System_Content_WithEGV_Copy_H_
#define _System_Content_WithEGV_Copy_H_

#include "system/content/with-egv/interface.h"
#include "system/content/with-eg/copy.h"

namespace mysimulator {

  template <typename T,typename IDT,typename ParamT,typename GeomT,
            template<typename> class SpaceType>
  void copy(SystemWithEGV<T,IDT,ParamT,GeomT,SpaceType>& S,
            const SystemWithEGV<T,IDT,ParamT,GeomT,SpaceType>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    typedef
      typename SystemWithEGV<T,IDT,ParamT,GeomT,SpaceType>::ParentType
      Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(rS));
    copy(S.V,rS.V);
  }

}

#endif

