
#ifndef _Propagator_Berendsen_VelocityVerlet_H_
#define _Propagator_Berendsen_VelocityVerlet_H_

#include "propagator-parameter-name-berendsen-vverlet.h"
#include "propagator-set-common.h"
#include "interaction-4listset.h"
#include "monomer-propagator.h"

namespace std {

  void BVSynchronize(const Vector<double>*, const Vector<double>* dMask,
                     const unsigned int nunit, UniqueParameter* GPrm) {
    double dof=0;
    for(unsigned int i=0;i<nunit;++i) dof+=asum(dMask[i]);
    GPrm[BV_DegreeFreedom]=dof;
    GPrm[BV_DeltaTIvRelaxT]=GPrm[DeltaTime].d/GPrm[BV_RelaxTime].d;
  }

  void BVSet_Temperature(UniqueParameter* GPrm, const void* pt) {
    GPrm[BV_Temperature]=*reinterpret_cast<const double*>(pt);
  }

  void BVSet_RelaxTime(UniqueParameter* GPrm, const void* pr) {
    GPrm[BV_RelaxTime]=*reinterpret_cast<const double*>(pr);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BVStep(InteractionMethod<DistEvalMethod,GeomType>* IMLst,
              Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
              const Vector<double>* Mass, const Vector<unsigned int>* IdxLst,
              const Vector<UniqueParameter>* PrmLst,
              UniqueParameter* GPrm, MonomerPropagator* Unit,
              const unsigned int nunit, const unsigned int nlst,
              DistEvalMethod& DEval, const GeomType& Geo) {
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[BV_BeforeG](Coor[i](),Vel[i](),Grad[i](),Coor[i].size,
                               GPrm,Unit[i].MParam());
    update(DEval);
    for(unsigned int i=0;i<nunit;++i) assign(Grad[i],0.);
    GFunc(Coor,IdxLst,PrmLst,IMLst,nlst,DEval,Geo,Grad);
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[BV_AfterG](Coor[i](),Vel[i](),Grad[i](),Coor[i].size,
                              GPrm,Unit[i].MParam());
    double fac=0.;
    for(unsigned int i=0;i<nunit;++i) fac+=normSQ(Vel[i])*Mass[i][0];
    fac=GPrm[BV_Temperature].d*GPrm[BV_DegreeFreedom].d/fac;
    GPrm[BV_ScaleFactor]=sqrt(GPrm[BV_DeltaTIvRelaxT].d*(fac-1.));
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[BV_PostProcess](Coor[i](),Vel[i](),Grad[i](),Coor[i].size,
                                   GPrm,Unit[i].MParam());
  }

  template <typename DistEvalMethod, typename GeomType>
  void BVStep(InteractionMethod<DistEvalMethod,GeomType>* IMLst,
              Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
              const Vector<double>* Mass,
              const Vector<Vector<unsigned int> >* IdxLst,
              const Vector<Vector<UniqueParameter> >* PrmLst,
              UniqueParameter* GPrm, MonomerPropagator* Unit,
              const unsigned int nunit, const unsigned int nlst,
              DistEvalMethod& DEval, const GeomType& Geo) {
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[BV_BeforeG](Coor[i](),Vel[i](),Grad[i](),Coor[i].size,
                               GPrm,Unit[i].MParam());
    update(DEval);
    for(unsigned int i=0;i<nunit;++i) assign(Grad[i],0.);
    GFunc(Coor,IdxLst,PrmLst,IMLst,nlst,DEval,Geo,Grad);
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[BV_AfterG](Coor[i](),Vel[i](),Grad[i](),Coor[i].size,
                              GPrm,Unit[i].MParam());
    double fac=0.;
    for(unsigned int i=0;i<nunit;++i) fac+=normSQ(Vel[i])*Mass[i][0];
    fac=GPrm[BV_Temperature].d*GPrm[BV_DegreeFreedom].d/fac;
    GPrm[BV_ScaleFactor]=sqrt(GPrm[BV_DeltaTIvRelaxT].d*(fac-1.));
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[BV_PostProcess](Coor[i](),Vel[i](),Grad[i](),Coor[i].size,
                                   GPrm,Unit[i].MParam());
  }

}

#include "propagator.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void SetAsBV(Propagator<DistEvalMethod,GeomType>& P) {
    P.GSync=BVSynchronize;
    allocate(P.GSet,NumberSetBV);
    AssignCommonSet4Propagator(P.GSet());
    P.GSet[TemperatureBV]=BVSet_Temperature;
    P.GSet[RelaxTimeBV]=BVSet_RelaxTime;
    P.FStep=BVStep<DistEvalMethod,GeomType>;
    P.HStep=BVStep<DistEvalMethod,GeomType>;
    allocate(P.GParam,NumberParameterBV);
  }

}

#endif

