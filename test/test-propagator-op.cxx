
#include "propagator-op.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  Propagator<DistanceEvalDirect,FreeSpace> P;
  allocate(P);

  cout<<"Test -- Set as Constant-E velocity-verlet"<<endl;
  Set(P,ConstantE_VelocityVerlet);
  cout<<*(P.MoveMode)<<endl;
  cout<<P.GSet.size<<endl;
  cout<<P.GParam.size<<endl;
  cout<<endl;

  cout<<"Test -- Set as Berendsen velocity-verlet"<<endl;
  Set(P,Berendsen_VelocityVerlet);
  cout<<*(P.MoveMode)<<endl;
  cout<<P.GSet.size<<endl;
  cout<<P.GParam.size<<endl;
  cout<<endl;

  cout<<"Test -- Set as Langevin velocity-verlet"<<endl;
  Set(P,Langevin_VelocityVerlet);
  cout<<*(P.MoveMode)<<endl;
  cout<<P.GSet.size<<endl;
  cout<<P.GParam.size<<endl;
  cout<<endl;

  return 0;
}

