
#include "propagator/regular/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

namespace mysimulator {

  class OutTest : public PropagatorOutput<double,FreeSpace,
                                          BoxMuller<MersenneTwisterStandard> > {
    public:
      virtual void Write(const double& now,System<double,FreeSpace>& S,
                         Propagator<double,FreeSpace,
                                    BoxMuller<MersenneTwisterStandard> >* P) {
      }
  };

}

int main() {
  Propagator<double,FreeSpace>* P=new PropagatorRegular<double,FreeSpace>;

  P->SetMassFlag(UniqueMass);
  P->SetFrictionFlag(UniqueFriction);

  Array2D<StepPropagatorName>   SPN;
  SPN.Allocate(1,1);
  SPN[0][0]=VelVerletConstE;
  P->Allocate(SPN);

  P->InitNowTime(0);
  P->SetTime(0.001,10.);

  return 0;
}

