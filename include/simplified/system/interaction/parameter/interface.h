
#ifndef _System_Interaction_Parameter_Interface_H_
#define _System_Interaction_Parameter_Interface_H_

#include "array/interface.h"

namespace mysimulator {

  template <typename FT=double>
  class InteractionParameter {

    public:

      static_assert(__float_point_flag<FT>::FG,
                    "Floating-Point Data are expected!\n");

      typedef InteractionParameter<T>   Type;

    private:

      InteractionName       _tag;
      Array<Intrinsic<FT>>  _FParam;
      Array<Int>            _IParam;

  };

}

#endif

