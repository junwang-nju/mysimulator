
#include "minimizer-base.h"
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

int main() {
  cout<<"Test -- initialize"<<endl;
  MinimizerKernelBase<double,double> MB;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(MB);
  MB.MinEFunc=efunc;
  MB.MinGFunc=gfunc;
  MB.MinBFunc=bfunc;
  *(MB.MinCoor)=5;
  *(MB.MinParam)=10;
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  MinimizerKernelBase<double,double> MB2;
  allocate(MB2);
  assign(MB2,MB);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(MB2);
  cout<<endl;

  cout<<"Test -- check avaialability"<<endl;
  cout<<IsAvailable(MB)<<endl;
  cout<<IsAvailable(MB2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(MB2,MB);
  cout<<endl;

  cout<<"Test -- Generate new Location"<<endl;
  double dest,desty,destg,destp;
  double dirc=1;
  double step=0.5;
  GenerateNewLocation(MB2,*(MB.MinCoor),dirc,step,dest,desty,destg,destp);
  cout<<dest<<"\t"<<desty<<"\t"<<destg<<"\t"<<destp<<endl;
  cout<<endl;

  return 1;
}

