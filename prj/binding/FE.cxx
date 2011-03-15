
#include "data/basic/console-output.h"
#include  <cmath>
using namespace std;

double f1(double d) {
  return -pow(d,-2.);
}

double IntF1(double d) {
  return pow(d,-1.);
}

double f(double d) {
  return -pow(d,-6.);
}

double S(double n, double d) {
  return 2*log(d)-d*d/n;
}

int main() {
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;

  const double e1=0;
  const double e2=0;

  double theta,cthNear,cthFar;
  double d,d1,d2;
  double w,w1,w2;
  unsigned int r,r1,r2;
  double R,RA,RB;
  double F,T;
  unsigned int NA,NB,Nd;
  double c1,c2,c3;

  T=2;
  R=20;
  d=0.1;

  r=0;
  r1=0;
  r2=r-r1;
  NA=N1+r1;
  NB=N2+r2;
  Nd=Nm-r;
  RA=pow(NA,-1./3.);
  RB=pow(NB,-1./3.);
  d1=(-NA*RA+NB*(RB+d)+Nd*d/2.)/N;
  d2=d-d1;
  cthNear=(R-RA)/(RA+d1);
  if(cthNear>1.)    cthNear=1.;
  cthFar=-(R-RB)/(RB+d2);
  if(cthFar<-1.)    cthFar=-1.;

  F=(IntF1(R-cthFar*(RA+d1))-IntF1(R-cthNear*(RA+d1)))/(RA+d1)+
    (f(RA+RB+d)-T*S(Nd,d))*(cthNear-cthFar);

  COut<<F<<Endl;


  return 0;
}

