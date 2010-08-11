
#include "vector.h"
#include <iostream>
#include <cmath>
using namespace std;

double potential(const double& x) {
  double d;
  d=x*x;
  return d*d-2*d-0.3*x;
}

double gradient(const double& x) {
  double d;
  d=x*x;
  return 4*(d-1)*x-0.3;
}

int main() {
  int zI=200;
  Vector<double> prob,nprob;
  allocate(prob,401);
  allocate(nprob,401);
  assign(prob,0.);
  assign(nprob,0.);
  prob[-150+zI]=100;

  double h=0.01;
  double dt=1e-6;
  double T=1.;
  double gamma=5.;
  double rsize=sqrt(2*T/gamma);

  double d;

  for(unsigned int i=0;i<5000000;++i) {
    if(i%10000==0) {
      for(unsigned int i=0;i<=400;++i)
        cout<<i*0.01-2<<"\t"<<prob[i]<<endl;
      cout<<endl;
    }
    for(unsigned int i=1;i<400;++i) {
      d=(gradient((i+1)*0.01-2.)*prob[i+1]-gradient((i-1)*0.01-2.)*prob[i-1])*0.5/h;
      d+=T*(prob[i-1]+prob[i+1]-2*prob[i])/(h*h);
      nprob[i]=prob[i]+d*rsize*dt;
    }
    prob=nprob;
  }
  for(unsigned int i=0;i<=400;++i)
    cout<<i*0.01-2<<"\t"<<prob[i]<<endl;
  return 0;
}

