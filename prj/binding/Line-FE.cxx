
#include "data/basic/console-output.h"
#include <cmath>
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d,double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R, double d0, double epsilon,double T,
            double RA,double RB, double d1,double d2, double RC) {
  static const double Dcth=0.001;
  static const double Dphi=0.001*2*M_PI;
  double xA,xB,tmd,sum,sump,sfac,Func;
  sum=0;
  for(double cth=1,sth;cth>=-1;cth-=Dcth) {
    if(fabs(cth)>1-0.5*Dcth) { sth=0; sfac=0.5; }
    else { sth=sqrt(1-cth*cth); sfac=1; }
    sump=0;
    for(double phi=0;phi<2*M_PI;phi+=Dphi) {
      tmd=R-(RA+d1)*cth;
      xA=tmd*tmd;
      tmd=(RA+d1)*sth*sin(phi);
      xA+=tmd*tmd;
      xA=sqrt(xA);
      tmd=R+(RB+d2)*cth;
      xB=tmd*tmd;
      tmd=(RB+d2)*sth*sin(phi);
      xB+=tmd*tmd;
      xB=sqrt(xB);
      if((xA<RC)||(xB<RC)||(R*sth<RC)) Func=0;
      else Func=ExpF1T(xA,d0,epsilon,T);
      sump+=Func*Dphi;
    }
    sum+=sump*Dcth*sfac;
  }
  return sum;
}

double f(double d) {
  return -exp(-d/0.5)*10;
}

double S(double n, double d) { return 2*log(d)-d*d/n; }

double SG(double r) { return log(r); }

int main() {
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;
  
  const double e1=0;
  const double e2=0;
  const double epsilon=100;
  const double T=1.48;
  
  const double d0=2;
  const double rc=2;
  
  double d,d1,d2;
  unsigned int r,r1,r2;
  double R,RA,RB;
  double FL;
  unsigned int NA,NB,Nd;
  double C;
  
  R=8.;
  d=0.1;
  
  r=0;
  r1=r2=0;
  for(d=0.001;d<Nm;d+=0.001) {
    NA=N1+r1;
    NB=N2+r2;
    Nd=Nm-r;
    RA=pow(NA,-1./3.);
    RB=pow(NB,-1./3.);
    d1=(-RA*NA+(RB+d)*NB+d/2.*Nd)/(N+0.);
    d2=d-d1;
    
    C=(f(d)-T*S(Nd,d))-e1*r1-e2*r2-T*SG(R);
    FL=exp(-C/T)*Intg(R,d0,epsilon,T,RA,RB,d1,d2,rc);
    COut<<d<<"\t"<<-T*log(FL)<<Endl;
  }
   
  return 0;
}

