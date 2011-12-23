
#ifndef _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_
#define _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void _UpdateFuncCEVVerletHTIMGlobaleMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM,
      const unsigned int&) {
    negHTIM.value<T>()=-0.5*dt/Mass.value<T>();
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletHTIMArrayMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM,
      const unsigned int& n) {
    typedef Array1D<VT<T> > AVT;
    copy((*reinterpret_cast<AVT*>(negHTIM.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Mass.ptr[0]))[n]);
    inverse((*reinterpret_cast<AVT*>(negHTIM.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(negHTIM.ptr[0]))[n],-dt*0.5);
  }

}

#endif

