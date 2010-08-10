
#include "vector.h"
#include "random-generator.h"
#include <iostream>
#include <cmath>
#include <cstdio>
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
  double x,v,f,tx,tf;

  x=-1.;
  v=0.;
  f=-gradient(x);

  double dt=0.001;
  double gamma=5,igamma=1./gamma;
  double T=1.;
  double rsize;
  rsize=sqrt(2*gamma*T*dt);

  GaussianRNG grng;
  allocate(grng);
  initWithTime(grng);

  for(unsigned int i=0;i<10000;++i) {
    tx=x+igamma*f*dt+rsize*rand(grng);
    tf=-gradient(tx);
    x=x+(tx-x)*0.5+igamma*(tf*dt+rsize*rand(grng))*0.5;
    f=-gradient(x);
    cout<<i<<"\t"<<x<<endl;
  }

  return 0;
}

