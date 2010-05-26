
#ifndef _Propagator_Langevin_VelocityVerlet_H_
#define _Propagator_Langevin_VelocityVerlet_H_

#include "propagator-parameter-name-langevin-vverlet.h"
#include "propagator-set-common.h"
#include "interaction-4listset.h"
#include "monomer-propagator.h"

namespace std {

  void LVSynchronize(const Vector<double>* ivMass, const Vector<double>*,
                     const Vector<double>*,
                     const unsigned int nunit, UniqueParameter* GPrm) {
    GPrm[LV_TemperatureDeltaT]=GPrm[LV_Temperature].d*
                               GPrm[DeltaTime].d;
  }

  void LVSet_Temperature(UniqueParameter* GPrm, const void* pt) {
    GPrm[LV_Temperature]=*reinterpret_cast<const double*>(pt);
  }

  void LVSet_Viscosity(UniqueParameter* GPrm, const void* pv) {
    GPrm[LV_Viscosity]=*reinterpret_cast<const double*>(pv);
  }

  void LVSet_GaussianRNGPointer(UniqueParameter* GPrm, const void* pg) {
    GPrm[LV_GaussianRNGPointer]=const_cast<void*>(pg);
  }

  template <typename DistEvalMethod, typename GeomType>
  void LVStep(InteractionMethod<DistEvalMethod,GeomType>* IMLst,
              Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
              const Vector<double>* Mass, const Vector<double>* dMask,
              const Vector<unsigned int>* IdxLst,
              const Vector<UniqueParameter>* PrmLst,
              UniqueParameter* GPrm, MonomerPropagator* Unit,
              const unsigned int nunit, const unsigned int nlst,
              DistEvalMethod& DEval, const GeomType& Geo) {
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[LV_BeforeG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                               Coor[i].size,GPrm,Unit[i].MParam());
    update(DEval);
    for(unsigned int i=0;i<nunit;++i) assign(Grad[i],0.);
    GFunc(Coor,IdxLst,PrmLst,IMLst,nlst,DEval,Geo,Grad);
    for(unsigned int i=0;i<nunit;++i) scale(Grad[i],dMask[i]);
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[LV_AfterG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                              Coor[i].size,GPrm,Unit[i].MParam());
  }

  template <typename DistEvalMethod, typename GeomType>
  void LVStep(InteractionMethod<DistEvalMethod,GeomType>* IMLst,
              Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
              const Vector<double>* Mass, const Vector<double>* dMask,
              const Vector<Vector<unsigned int> >* IdxLst,
              const Vector<Vector<UniqueParameter> >* PrmLst,
              UniqueParameter* GPrm, MonomerPropagator* Unit,
              const unsigned int nunit, const unsigned int nlst,
              DistEvalMethod& DEval, const GeomType& Geo) {
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[LV_BeforeG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                               Coor[i].size,GPrm,Unit[i].MParam());
    update(DEval);
    for(unsigned int i=0;i<nunit;++i) assign(Grad[i],0.);
    GFunc(Coor,IdxLst,PrmLst,IMLst,nlst,DEval,Geo,Grad);
    for(unsigned int i=0;i<nunit;++i) scale(Grad[i],dMask[i]);
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[LV_AfterG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                              Coor[i].size,GPrm,Unit[i].MParam());
  }

}

#include "propagator.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void SetAsLV(Propagator<DistEvalMethod,GeomType>& P) {
    assert(IsAvailable(P));
    P.GSync=LVSynchronize;
    allocate(P.GSet,NumberSetLV);
    AssignCommonSet4Propagator(P.GSet());
    P.GSet[TemperatureLV]=LVSet_Temperature;
    P.GSet[ViscosityLV]=LVSet_Viscosity;
    P.GSet[GaussianRNGPointerLV]=LVSet_GaussianRNGPointer;
    P.FStep=LVStep<DistEvalMethod,GeomType>;
    P.HStep=LVStep<DistEvalMethod,GeomType>;
    allocate(P.GParam,NumberParameterLV);
  }

}

#endif

