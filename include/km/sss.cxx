
#include "propagator/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

namespace mysimulator {

  class OutTest : public PropagatorOutput<double,FreeSpace> {
    public:
      virtual void Allocate() {}
      virtual void Write(const double& now,System<double,FreeSpace>& S,
                         Propagator<double,FreeSpace>* P) {
        S.UpdateE(0);
        P->UpdateKineticEnergy();
        std::cout<<now<<"\t"<<S.Energy()<<"\t"<<P->KineticEnergy()<<endl;
      }
  };

}

int main() {
  Propagator<double,FreeSpace>* P=NULL;
  Introduce(P,MolecularDynamics);
  P->AllocateOutput<OutTest>();

  Array<StepPropagatorName> SPN;
  SPN.Allocate(2);
  SPN[0]=VelVerletConstE;
  SPN[1]=FixPosition;
  P->Allocate(SPN,UniqueMass,BoxMullerRNG,MTStandardRNG);

  P->Time(MDTime_NowTime)=0;
  P->IntTime(MDTime_NowStep)=0;
  P->Time(MDTime_TimeStep)=0.001;
  P->Time(MDTime_TotalPeriod)=10.;
  P->Time(MDTime_OutputInterval)=0.001;
  P->UpdateTime(Step_Total_OInterval);

  *Pointer<double>(P->Parameter(PropagatorMD_Mass))=1.;
  P->Update();

  return 0;
}

