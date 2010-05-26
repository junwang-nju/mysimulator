
#ifndef _Propagator_ConstantE_VelocityVerlet_H_
#define _Propagator_ConstantE_VelocityVerlet_H_

#include "propagator-parameter-name-conste-vverlet.h"
#include "propagator-set-common.h"
#include "interaction-4listset.h"
#include "monomer-propagator.h"

namespace std {

  void EVSynchronize(const Vector<double>*, const Vector<double>*,
                     const Vector<double>*,
                     const unsigned int, UniqueParameter*) {}

  template <typename DistEvalMethod, typename GeomType>
  void EVStep(InteractionMethod<DistEvalMethod,GeomType>* IMLst,
              Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
              const Vector<double>* Mass, const Vector<double>* dMask,
              const Vector<unsigned int>* IdxLst,
              const Vector<UniqueParameter>* PrmLst,
              UniqueParameter* GPrm, MonomerPropagator* Unit,
              const unsigned int nunit, const unsigned int nlst,
              DistEvalMethod& DEval, const GeomType& Geo) {
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[EV_BeforeG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                               Coor[i].size,GPrm,Unit[i].MParam());
    update(DEval);
    for(unsigned int i=0;i<nunit;++i) assign(Grad[i],0.);
    GFunc(Coor,IdxLst,PrmLst,IMLst,nlst,DEval,Geo,Grad);
    for(unsigned int i=0;i<nunit;++i) scale(Grad[i],dMask[i]);
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[EV_AfterG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                              Coor[i].size,GPrm,Unit[i].MParam());
  }

  template <typename DistEvalMethod, typename GeomType>
  void EVStep(InteractionMethod<DistEvalMethod,GeomType>* IMLst,
              Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
              const Vector<double>* Mass, const Vector<double>* dMask,
              const Vector<Vector<unsigned int> >* IdxLst,
              const Vector<Vector<UniqueParameter> >* PrmLst,
              UniqueParameter* GPrm, MonomerPropagator* Unit,
              const unsigned int nunit, const unsigned int nlst,
              DistEvalMethod& DEval, const GeomType& Geo) {
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[EV_BeforeG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                               Coor[i].size,GPrm,Unit[i].MParam());
    update(DEval);
    for(unsigned int i=0;i<nunit;++i) assign(Grad[i],0.);
    GFunc(Coor,IdxLst,PrmLst,IMLst,nlst,DEval,Geo,Grad);
    for(unsigned int i=0;i<nunit;++i) scale(Grad[i],dMask[i]);
    for(unsigned int i=0;i<nunit;++i)
      Unit[i].Move[EV_AfterG](Coor[i](),Vel[i](),Grad[i](),dMask[i](),
                              Coor[i].size,GPrm,Unit[i].MParam());
  }

}

#include "propagator.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void SetAsEV(Propagator<DistEvalMethod,GeomType>& P) {
    assert(IsAvailable(P));
    P.GSync=EVSynchronize;
    allocate(P.GSet,NumberSetEV);
    AssignCommonSet4Propagator(P.GSet());
    P.FStep=EVStep<DistEvalMethod,GeomType>;
    P.HStep=EVStep<DistEvalMethod,GeomType>;
    allocate(P.GParam,NumberParameterEV);
  }

}

#endif

