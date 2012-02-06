
#ifndef _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_
#define _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void _UpdateFuncCEVVerletHTIMGlobaleMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM,
      const unsigned int&) {
    *reinterpret_cast<T*>(negHTIM.ptr[0])=
      -0.5*dt/(*reinterpret_cast<T*>(Mass.ptr[0]));
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

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQGlobalMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int&) {
    (*reinterpret_cast<T*>(VSQ.ptr[0]))+=dot(Vel,Vel);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQArrayMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int& n) {
    typedef Array1D<VT<T> > AVT;
    copy((*reinterpret_cast<AVT*>(VSQ.ptr[0]))[n],Vel);
    scale((*reinterpret_cast<AVT*>(VSQ.ptr[0]))[n],Vel);
  }

  template <typename T>
  void _UpdateFuncCEVVerletVSQInitGlobalMass(Unique64Bit& VSQ) {
    (*reinterpret_cast<T*>(VSQ.ptr[0]))=0;
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQInitArrayMass(Unique64Bit& VSQ) {
    typedef Array1D<VT<T> > AVT;
    unsigned int n=reinterpret_cast<AVT*>(VSQ.ptr[0])->size;
    for(unsigned int i=0;i<n;++i)
      fill((*reinterpret_cast<AVT*>(VSQ.ptr[0]))[i],0);
  }

  template <typename T>
  void _UpdateFuncCEVVerletKEnergyGlobalMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    KE=0.5*(*reinterpret_cast<T*>(Mass.ptr[0]))*
           (*reinterpret_cast<T*>(VelSQ.ptr[0]));
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletKEnergyArrayMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    typedef Array1D<VT<T> > AVT;
    unsigned int n=reinterpret_cast<AVT*>(VelSQ.ptr[0])->size;
    KE=0;
    for(unsigned int i=0;i<n;++i)
      KE+=0.5*dot((*reinterpret_cast<AVT*>(Mass.ptr[0]))[i],
                  (*reinterpret_cast<AVT*>(VelSQ.ptr[0]))[i]);
  }

}

#endif

