
#ifndef _System_Propagate_VelocityVerlet_Langevin_Update_Func_H_
#define _System_Propagate_VelocityVerlet_Langevin_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"
#include "intrinsic-type/inverse.h"

namespace mysimulator {

  template <typename T>
  void _UpdateFuncLgVVerletHTIMGMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM,
      const unsigned int&) {
    negHTIM.value<T>()=-0.5*dt/Mass.value<T>();
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletHTIMAMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM,
      const unsigned int& n) {
    typedef Array1D<VT<T> >     AVT;
    copy((*reinterpret_cast<AVT*>(negHTIM.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Mass.ptr[0]))[n]);
    inverse((*reinterpret_cast<AVT*>(negHTIM.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(negHTIM.ptr[0]))[n],-dt*0.5);
  }

}

#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void _UpdateFuncLgVVerletRSizeGMassGFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize, const unsigned int&) {
    RSize.value<T>()=sqroot(dt*Temp*Fric.value<T>()/Mass.value<T>());
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletRSizeAMassGFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize, const unsigned int& n) {
    typedef Array1D<VT<T> >     AVT;
    copy((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Mass.ptr[0]))[n]);
    inverse((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n],dt*Temp*Fric.value<T>());
    sqroot((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n]);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletRSizeGMassAFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize, const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    copy((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Fric.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n],dt*Temp*Mass.value<T>());
    sqroot((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n]);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletRSizeAMassAFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize, const unsigned int& n) {
    typedef Array1D<VT<T> >     AVT;
    copy((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Mass.ptr[0]))[n]);
    inverse((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n],dt*Temp);
    scale((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n],
          (*reinterpret_cast<const AVT*>(Fric.ptr[0]))[n]);
    sqroot((*reinterpret_cast<AVT*>(RSize.ptr[0]))[n]);
  }

  template <typename T>
  void _UpdateFuncLgVVerletFacGMassGFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2, const unsigned int&) {
    T d=0.5*dt*Fric.value<T>()/Mass.value<T>();
    Fac1.value<T>()=ValueOne<T>()-d;
    Fac2.value<T>()=ValueOne<T>()+d;
    inverse(Fac2.value<T>());
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletFacAMassGFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2, const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    copy((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Mass.ptr[0]))[n]);
    inverse((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],-0.5*dt*Fric.value<T>());
    copy((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Fac1.ptr[0]))[n]);
    shift((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],cOne);
    scale((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],-cOne);
    shift((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],cOne);
    inverse((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n]);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletFacGMassAFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2, const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    copy((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Fric.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],-0.5*dt/Mass.value<T>());
    copy((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Fac1.ptr[0]))[n]);
    shift((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],cOne);
    scale((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],-cOne);
    shift((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],cOne);
    inverse((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n]);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletFacAMassAFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2, const unsigned int& n) {
    typedef Array1D<VT<T> >     AVT;
    copy((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Mass.ptr[0]))[n]);
    inverse((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n]);
    scale((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],-0.5*dt);
    scale((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],
          (*reinterpret_cast<const AVT*>(Fric.ptr[0]))[n]);
    copy((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],
         (*reinterpret_cast<const AVT*>(Fac1.ptr[0]))[n]);
    shift((*reinterpret_cast<AVT*>(Fac1.ptr[0]))[n],cOne);
    scale((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],-cOne);
    shift((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n],cOne);
    inverse((*reinterpret_cast<AVT*>(Fac2.ptr[0]))[n]);
  }

}

#include "system/propagate/vverlet/const-e/_update.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletVSQGMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int& n) {
    _UpdateFuncCEVVerletVSQGMass<T,VT>(VSQ,Vel,n);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletVSQAMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int& n) {
    _UpdateFuncCEVVerletVSQAMass<T,VT>(VSQ,Vel,n);
  }

  template <typename T>
  void _UpdateFuncLgVVerletVSQInitGMass(Unique64Bit& VSQ) {
    _UpdateFuncCEVVerletVSQInitGMass<T>(VSQ);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletVSQInitAMass(Unique64Bit& VSQ) {
    _UpdateFuncCEVVerletVSQInitAMass<T,VT>(VSQ);
  }

  template <typename T>
  void _UpdateFuncLgVVerletKEnergyGMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    _UpdateFuncCEVVerletKEnergyGMass<T>(KE,Mass,VelSQ);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletKEnergyAMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    _UpdateFuncCEVVerletKEnergyAMass<T,VT>(KE,Mass,VelSQ);
  }

}

#endif

