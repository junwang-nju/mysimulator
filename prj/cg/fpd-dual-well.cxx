
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
  Vector<double> prob1,prob2,nprob;
  allocate(prob1,401);
  allocate(prob2,401);
  allocate(nprob,401);
  assign(prob1,0.);
  assign(prob2,0.);
  assign(nprob,0.);
  prob1[-100+zI]=100;
  prob2[+150+zI]=100;

  double h=0.01;
  double dt=1e-6;
  double T=1.;
  double gamma=5.;
  double rsize=sqrt(2*T/gamma);

  double d,d1,d2;

  for(unsigned int z=0;z<9000000;++z) {
    if(z%100==0) {
      d=0;
      for(unsigned int i=1;i<400;++i)
        d+=fabs(prob1[i]-prob2[i]);
      d*=h;
      d1=0;
      for(unsigned int i=1;i<400;++i)
        d1+=fabs(prob1[i]);
      d1*=h;
      d2=0;
      for(unsigned int i=1;i<400;++i)
        d2+=fabs(prob1[i]);
      d2*=h;
      cout<<z*dt<<"\t"<<d<<"\t"<<d1<<"\t"<<d2<<endl;
    }
    for(unsigned int i=2;i<399;++i) {
      d=(gradient((i+1)*0.01-2.)*prob1[i+1]-gradient((i-1)*0.01-2.)*prob1[i-1])*0.5/h;
      d+=T*(prob1[i-1]+prob1[i+1]-2*prob1[i])/(h*h);
      nprob[i]=prob1[i]+d*rsize*dt;
    }
    d=(gradient(2*0.01-2.)*prob1[2]+gradient(0.01-2.)*prob1[1])*0.5/h;
    d+=(prob1[2]-prob1[1])/(h*h);
    nprob[1]=prob1[1]+d*rsize*dt;
    d=(-gradient(399*0.01-2.)*prob1[399]-gradient(398*0.01-2.)*prob1[398])*0.5/h;
    d+=(prob1[398]-prob1[399])/(h*h);
    nprob[399]=prob1[399]+d*rsize*dt;
    prob1=nprob;
    for(unsigned int i=2;i<399;++i) {
      d=(gradient((i+1)*0.01-2.)*prob2[i+1]-gradient((i-1)*0.01-2.)*prob2[i-1])*0.5/h;
      d+=T*(prob2[i-1]+prob2[i+1]-2*prob2[i])/(h*h);
      nprob[i]=prob2[i]+d*rsize*dt;
    }
    d=(gradient(2*0.01-2.)*prob2[2]+gradient(0.01-2.)*prob2[1])*0.5/h;
    d+=(prob2[2]-prob2[1])/(h*h);
    nprob[1]=prob2[1]+d*rsize*dt;
    d=(-gradient(399*0.01-2.)*prob2[399]-gradient(398*0.01-2.)*prob2[398])*0.5/h;
    d+=(prob2[398]-prob2[399])/(h*h);
    nprob[399]=prob2[399]+d*rsize*dt;
    prob2=nprob;
  }
  d=0;
  for(unsigned int i=1;i<400;++i)
    d+=fabs(prob1[i]-prob2[i]);
  d*=h;
  cout<<9000000*dt<<"\t"<<d<<endl;
  return 0;
}

