
#include "monomer-propagator-op.h"
#include <iostream>
using namespace std;

int main() {
  MonomerPropagator MP;
  allocate(MP);
  cout<<"Test -- Set as Constant-E velocity verlet"<<endl;
  Set(MP,ParticleType,ConstantE_VelocityVerlet);
  cout<<*(MP.UnitKind)<<"\t"<<*(MP.MoveMode)<<endl;
  cout<<MP.Move.size<<endl;
  cout<<MP.MSet.size<<endl;
  cout<<MP.MParam.size<<endl;
  cout<<endl;

  cout<<"Test -- set as Berendsen velocity verlet"<<endl;
  Set(MP,ParticleType,Berendsen_VelocityVerlet);
  cout<<*(MP.UnitKind)<<"\t"<<*(MP.MoveMode)<<endl;
  cout<<MP.Move.size<<endl;
  cout<<MP.MSet.size<<endl;
  cout<<MP.MParam.size<<endl;
  cout<<endl;

  cout<<"Test -- set as Langevin velocity verlet"<<endl;
  Set(MP,ParticleType,Langevin_VelocityVerlet);
  cout<<*(MP.UnitKind)<<"\t"<<*(MP.MoveMode)<<endl;
  cout<<MP.Move.size<<endl;
  cout<<MP.MSet.size<<endl;
  cout<<MP.MParam.size<<endl;
  cout<<endl;

  return 0;
}


