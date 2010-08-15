
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
  Vector<double> *prob,prob1,prob2,nprob;
  prob=new Vector<double>[90001];
  for(unsigned int i=0;i<=90000;++i)
    allocate(prob[i],401);
  allocate(prob1,401);
  allocate(prob2,401);
  allocate(nprob,401);

  double h=0.01;
  double dt=1e-6;
  double T=1.;
  double gamma=5.;
  double rsize=sqrt(2*T/gamma);

  double d,s;

  for(int p=-180;p<180;p+=10) {
    assign(prob1,0.);
    prob1[p+zI]=100;
    assign(nprob,0.);
    for(unsigned int z=0;z<90000;z++) {
      prob[z]=prob1;
      for(unsigned int u=0;u<100;++u) {
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
      }
    }
    prob[90000]=prob1;
    for(int q=p+10;q<=180;q+=10) {
      assign(prob2,0.);
      assign(nprob,0.);
      prob2[q+zI]=100;

      s=-2*dt*0.5*100;
      for(unsigned int z=0;z<90000;++z) {
        d=0;
        for(unsigned int i=1;i<400;++i)
          d+=fabs(prob[z][i]-prob2[i]);
        d*=h;
        s+=d*dt*100;
        for(unsigned int u=0;u<100;++u) {
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
      }
      d=0;
      for(unsigned int i=1;i<400;++i)
        d+=fabs(prob[90000][i]-prob2[i]);
      d*=h;
      s+=0.5*d*dt*100;
      cout<<p*0.01<<"\t"<<q*0.01<<"\t"<<s<<endl;
    }
  }
  return 0;
}

