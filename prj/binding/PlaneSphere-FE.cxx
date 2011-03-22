
#include "data/basic/console-output.h"
#include <cmath>
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d,double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R, double d0, double epsilon,double T,
            double RA,double RB, double d1,double d2, double RC) {
  static const double Dcth=0.01;
  static const double Dphi=0.01*2*M_PI;
  static const double DZcth=0.01;
  double rA,rB,zA,zB,sum,sumtp,sump,szfac,sfac,Func;
  double tmdA,tmdB,tmdAA,tmdBB,tmcphi;
  sum=0;
  for(double zcth=1,zsth;zcth>0-0.5*DZcth;zcth-=DZcth) {
    szfac=((zcth>1-DZcth*0.5)||(zcth<0.5*DZcth)?0.5:1);
    zsth=(zcth>1-DZcth*0.5?0:sqrt(1-zcth*zcth));
    sumtp=0.;
    for(double cth=1,sth;cth>-1-0.5*Dcth;cth-=Dcth) {
      sfac=(fabs(cth)>1-0.5*Dcth?0.5:1);
      sth=(fabs(cth)>1-0.5*Dcth?0:sqrt(1-cth*cth));
      tmdAA=RA+d1;
      tmdBB=RB+d2;
      tmdA=tmdAA*cth;
      tmdB=tmdBB*cth;
      rA=sqrt(R*R-2*R*tmdA+tmdAA*tmdAA);
      rB=sqrt(R*R-2*R*tmdB+tmdBB*tmdBB);
      tmcphi=sth*zsth;
      tmdAA*=tmcphi;
      tmdBB*=tmcphi;
      tmdA=(R-tmdA)*zcth;
      tmdB=(R-tmdB)*zcth;
      sump=0.;
      for(double phi=0;phi<2*M_PI;phi+=Dphi) {
        tmcphi=cos(phi);
        zA=tmdA+tmdAA*tmcphi;
        zB=tmdB+tmdBB*tmcphi;
        if((zA<=0)||(zB<=0)||(rA<RC+RA)||(rB<RC+RB)||(R*R*(1-cth*cth)<RC*RC))
          Func=0;
        else Func=ExpF1T(rA,d0,epsilon,T);
        sump+=Func*Dphi;
      }
      sumtp+=sump*sfac*Dcth;
    }
    sum+=sumtp*szfac*DZcth;
  }
  return sum;
}

double f(double d) {
  return -exp(-d/0.5)*10;
}

double S(double n, double d) { return 2*log(d)-d*d/n; }

double SG(double r) { return 2*log(r); }

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
  
  R=20;
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
    CErr<<d<<"\t"<<-T*log(FL)<<Endl;
  }
   
  return 0;
}

