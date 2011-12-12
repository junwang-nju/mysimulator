
#ifndef _System_Masked_Method_NoOperation_Do_H_
#define _System_Masked_Method_NoOperation_Do_H_

#include "system/masked/component/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class SpaceType>
  struct _SystemNoOperationApply {
    public:
      void Do(SpaceType<T>& V, const Mask4System<T,SpaceType>& M) {}
  };

}

#endif

