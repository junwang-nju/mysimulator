
#include "monomer-propagator.h"

#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- create a monomer propagator"<<endl;
  MonomerPropagator MP;
  cout<<endl;

  cout<<"Test -- allocate as particle with motion of constant E and velocity-verlet"<<endl;
  MP.allocate(ParticleType,ConstE_VelocityVerlet);
  cout<<endl;

  cout<<"Test -- copy to another monomer propagator"<<endl;
  MonomerPropagator MP1;
  MP1=MP;
  cout<<endl;

  cout<<"Test -- synchronize parameter"<<endl;
  varVector<double> IvMass(3);
  IvMass=3.;
  varVector<PropagatorDataElementType> GPrm(NumberParamEV);
  GPrm[DeltaTime]=0.01;
  GPrm[HalfDeltaTime]=0.5*GPrm[DeltaTime].d;
  MP1.synchronize(IvMass,GPrm);
  cout<<MP1.Param<<endl;
  cout<<endl;
  return 1;
}

