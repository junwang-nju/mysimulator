
#ifndef _Interaction_Kernel_Interface_H_
#define _Interaction_Kernel_Interface_H_

#include "interaction/geometry/interface.h"

namespace mysimulator {

  template <typename InteractionFuncType,template<typename> class DBuffer,
            typename GeomType, typename T>
  struct InteractionKernel {

    typedef InteractionKernel<InteractionFuncType,DBuffer,GeomType,T> Type;

    InteractionFuncType IF;
    InteractionGeometry<DBuffer,GeomType,T> IG;

    InteractionKernel() : IF(), IG() {}
    InteractionKernel(const Type&) {
      Error("Copier of InteractionKernel Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for InteractionKernel Disabled!");
      return *this;
    }
    ~InteractionKernel() { clearData(); }

    void clearData() { release(IF); release(IG); }

  };

  template <typename FT,template<typename> class DB,typename GT,typename T>
  bool IsValid(const InteractionKernel<FT,DB,GT,T>& K) {
    return IsValid(K.IF)&&IsValid(K.IG);
  }

  template <typename FT,template<typename> class DB,typename GT,typename T>
  void release(InteractionKernel<FT,DB,GT,T>& K) { K.clearData(); }

}

#endif

