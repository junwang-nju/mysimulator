
#ifndef _Interaction_Kernel_Interface_H_
#define _Interaction_Kernel_Interface_H_

#include "list/interface.h"
#include "interaction/func/name.h"

namespace mysimulator {

  template <InteractionFunctionName ItType, template<typename> class DBuffer,
            typename GeomType, typename T=double>
  struct InteractionKernel {

    typedef InteractionKernel<ItType,DBuffer,GeomType,T>    Type;

    List<T> tmvec;
    DBuffer<T> DB;
    GeomType  Geo;

    InteractionKernel() : tmvec(), DB(), Geo() {}
    InteractionKernel(const Type&) {
      Error("Copier of InteractionKernel Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for InteractionKernel Disabled!");
      return *this;
    }
    ~InteractionKernel() { clearData(); }

    void clearData() { release(tmvec); release(DB); release(Geo); }
    const unsigned int NumUnit() const { return DB.UnitNumber(); }
    const unsigned int Dimension() const { return DB.Dimension(); }

  };

  template <InteractionFunctionName ItType,template<typename> class DBuffer,
            typename GeomType, typename T>
  bool IsValid(const InteractionKernel<ItType,DBuffer,GeomType,T>& K) {
    return IsValid(K.DB)&&IsValid(K.Geo);
  }

  template <InteractionFunctionName ItType,template<typename> class DBuffer,
            typename GType, typename T>
  void release(InteractionKernel<ItType,DBuffer,GType,T>& K) { K.clearData(); }

}

#endif

