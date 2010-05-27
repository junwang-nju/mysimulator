
#ifndef _System_Operation_H_
#define _System_Operation_H_

#include "property-list.h"

namespace std {

  double KineticEnergy(const Vector<double>* Vel, const Vector<double>* Mass,
                       const unsigned int nunit, Vector<double>* kEnergy) {
    double ke=0.;
    for(unsigned int i=0;i<nunit;++i) {
      assign(kEnergy[i],Vel[i]);
      scale(kEnergy[i],Vel[i]);
      scale(kEnergy[i],Mass[i]);
      scale(kEnergy[i],0.5);
      ke+=asum(kEnergy[i]);
    }
    return ke;
  }

  double KineticEnergySimple(
      const Vector<double>* Vel, const Vector<double>* Mass,
      const unsigned int nunit) {
    double ke=0.;
    for(unsigned int i=0;i<nunit;++i) ke+=Mass[i][0]*normSQ(Vel[i]);
    return 0.5*ke;
  }

  void MassCenter(const Vector<double>* Coor, const unsigned int nunit,
                  Vector<double>& COM) {
    assign(COM,0.);
    for(unsigned int i=0;i<nunit;++i) shift(COM,dOne,Coor[i]);
    scale(COM,1./nunit);
  }

  void MassCenter(const Vector<double>* Coor, const unsigned int* idx,
                  const unsigned int nidx, Vector<double>& COM) {
    assign(COM,0.);
    for(unsigned int i=0;i<nidx;++i) shift(COM,dOne,Coor[idx[i]]);
    scale(COM,1./nidx);
  }

}

#endif

