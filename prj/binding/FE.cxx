
#include "data/basic/console-output.h"
#include  <cmath>
using namespace std;

double f1(double d, double r) {
  if(d>r) return -pow(d,-2.);
  else    return (pow(r/d,12.)-2)*pow(r,-2);
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
  const unsigned int Nm=20;

  const double e1=0;
  const double e2=0;

  double theta;
  double d,d1,d2;
  double w,w1,w2;
  double r,r1,r2;
  double R,R1,R2;
  double F,T;

  T=2;
  d=0.1;

  r=0;
  r1=r2=0;
  R1=pow(N1+r1,-1./3.);
  R2=pow(N2+r2,-1./3.);
  for(double d=0.01;d<10;d+=0.01) {
    F=f(R1+R2+d)-T*S(Nm-r,d);
    COut<<d<<"\t"<<F<<Endl;
  }

  return 0;
}

