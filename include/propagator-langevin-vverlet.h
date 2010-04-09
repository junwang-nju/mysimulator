
#ifndef _Propagator_Langevin_VelocityVerlet_H_
#define _Propagator_Langevin_VelocityVerlet_H_

#include "propagator.h"
#include "interaction-4listset.h"

namespace std {

  void LV_Allocate(varVector<PropagatorDataElementType>& GPrm) {
    GPrm.allocate(NumberParamLV);
  }

  void LV_Synchronize(
      const VectorBase<refVector<double> >& IvMass,
      const VectorBase<refVector<double> >&,
      VectorBase<PropagatorDataElementType>& GParam) {
    GParam[LV_TemperatureDeltaT]=GParam[LV_Temperature].d
                                *GParam[DeltaTime].d;
  }

  void LV_SetTemperature(
      VectorBase<PropagatorDataElementType>& GParam, const void* pd) {
    GParam[LV_Temperature]=*reinterpret_cast<const double*>(pd);
  }

  void LV_SetViscosity(
      VectorBase<PropagatorDataElementType>& GParam, const void* pd) {
    GParam[LV_ViscosityCoef]=*reinterpret_cast<const double*>(pd);
  }

  void LV_SetGaussianRNGPointer(
      VectorBase<PropagatorDataElementType>& GParam, const void* pd) {
    GParam[LV_GaussianRNGPointer].vptr=pd;
  }

}

#endif

