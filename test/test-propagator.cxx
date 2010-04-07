
#include "propagator.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include "var-property-list.h"
#include <iostream>
using namespace std;

int main() {
  Propagator<DistanceEvalDirect,FreeSpace>  P;
  varVector<unsigned int> uMode(5);
  uMode=ParticleType;
  P.allocate(ConstE_VelocityVerlet,uMode);

  varPropertyList<double>::Type IvMass;
  varPropertyList<double>::Type dMask;
  varVector<unsigned int> Sz(5);
  Sz=2;
  IvMass.allocate(Sz);
  dMask.allocate(Sz);
  IvMass=0.5;
  IvMass[2]=10;
  dMask=1;
  P.synchronize(IvMass,dMask);

  P.SetTimeStep(0.002);
  P.SetStartTime(100);
  P.SetTotalTime(10000);
  P.SetOutputInterval(0.01);

  varPropertyList<double>::Type CoorSeq,VelSeq,GradSeq;
  CoorSeq.allocate(Sz);
  VelSeq.allocate(Sz);
  GradSeq.allocate(Sz);

  Propagator<DistanceEvalDirect,FreeSpace>  P1;
  P1=P;

  return 1;
}

