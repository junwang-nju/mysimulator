
#include "minimizer-line-base.h"
#include <iostream>
using namespace std;

void efunc(const double& x, double& e, double& prm) {
  e+=prm*x*x;
}

void gfunc(const double& x, double& g, double& prm) {
  g+=2*prm*x;
}

void bfunc(const double& x, double& g, double& e, double& prm) {
  e+=prm*x*x;
  g+=2*prm*x;
}

int main() {
  cout<<"Test -- initialize"<<endl;
  LineMinimizerBase<double,double> LM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(LM);
  LM.MinEFunc=efunc;
  LM.MinGFunc=gfunc;
  LM.MinBFunc=bfunc;
  *(LM.MinCoor)=5;
  *(LM.MinParam)=10;
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  LineMinimizerBase<double,double> LM2;
  allocate(LM2);
  assign(LM2,LM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(LM2);
  cout<<endl;

  cout<<"Test -- check availability"<<endl;
  cout<<IsAvailable(LM)<<endl;
  cout<<IsAvailable(LM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(LM2,LM);
  cout<<endl;

  cout<<"Test -- generate new location"<<endl;
  double dirc=1;
  double step=0.5;
  GenerateNewLocation(LM2,*(LM.MinCoor),dirc,step,
                      *(LM.RunCoor),*(LM.RunEnergy),*(LM.RunGrad),
                      *(LM.RunProject));
  cout<<*(LM.RunCoor)<<"\t"<<*(LM2.RunEnergy)<<"\t";
  cout<<*(LM.RunGrad)<<"\t"<<*(LM.RunProject)<<endl;
  cout<<endl;

  return 1;
}

