
#include "vector.h"
#include <iostream>
#include <cmath>
#include "random-generator.h"
using namespace std;

double potential(const double& x, const double& y) {
  double r2=x*x+y*y;
  double r4=r2*r2;
  double r8=r4*r4;
  return -exp(-r8)+0.01*r4;
}

void gradient(const double& x, const double& y, double& gx, double& gy) {
  double r2=x*x+y*y;
  double r4=r2*r2;
  double r8=r4*r4;
  double f=exp(-r8)*8*r2*r4+4*r2;
  gx=-f*x;
  gy=-f*y;
}

int main() {

  GaussianRNG grng;
  allocate(grng);
  initWithTime(grng);

  double x,y,fx,fy,tx,ty,tfx,tfy;
  double dt=0.001;
  double gamma=5,igamma=1./gamma;
  double T=1.7;
  double rsize=sqrt(2*gamma*T*dt);

  x=-3.;  y=0.;
  gradient(x,y,fx,fy);

  for(unsigned int i=0;i<10000;++i) {
    tx=x+igamma*fx*dt+rsize*rand(grng);
    ty=y+igamma*fy*dt+rsize*rand(grng);
    gradient(tx,ty,tfx,tfy);
    x+=igamma*0.5*(fx+tfx)*dt+rsize*rand(grng);
    y+=igamma*0.5*(fy+tfy)*dt+rsize*rand(grng);
    gradient(x,y,fx,fy);
    cout<<i<<"\t"<<x<<"\t"<<y<<"\t"<<sqrt(x*x+y*y)<<endl;
  }
  return 0;
}

