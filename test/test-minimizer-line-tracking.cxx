
#include "minimizer-line-tracking.h"
#include "constant.h"
#include <iostream>
using namespace std;

void efunc(const double& x, double& e, double& prm) {
  e+=prm*x*x;
}

void gfunc(const double& x, double& g, double& prm) {
  g+=2*prm*x;
}

void bfunc(const double& x, double& e, double& g, double& prm) {
  e+=prm*x*x;
  g+=2*prm*x;
}

double minimalstep(const TrackingLineMinimizer<double,double>& TLM,
                   const double Orig, const double Dirc) {
  double tmd=fabs(Orig);
  tmd=(tmd<1.?Dirc:Dirc/tmd);
  double mstep=tmd*tmd;
  return DRelDelta*sqrt(1./mstep);
}

int main() {

  cout<<"Test -- initialize"<<endl;
  TrackingLineMinimizer<double,double> TLM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(TLM);
  TLM.MinEFunc=efunc;
  TLM.MinGFunc=gfunc;
  TLM.MinBFunc=bfunc;
  *(TLM.MinCoor)=5;
  *(TLM.MinParam)=10;
  *(TLM.TrackingFac)=0.1;
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  TrackingLineMinimizer<double,double> TLM2;
  allocate(TLM2);
  assign(TLM2,TLM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(TLM2);
  cout<<endl;

  cout<<"Test - check availability"<<endl;
  cout<<IsAvailable(TLM)<<endl;
  cout<<IsAvailable(TLM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(TLM2,TLM);
  cout<<endl;

  cout<<"Test -- minimize"<<endl;
  GenerateNewLocation(TLM2,*(TLM2.MinCoor),-1.,0,*(TLM2.MinCoor),
                      *(TLM2.MinEnergy),*(TLM2.MinGrad),*(TLM2.MinProject));
  cout<<TLM2.Minimize<StrongWolfe>(-1.)<<endl;
  cout<<*(TLM2.MinEnergy)<<endl;
  cout<<*(TLM2.MinCoor)<<endl;
  cout<<endl;
  
  return 0;
}

