
#include "data/basic/console-output.h"
#include "overlap.h"
#include <cmath>
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d,double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R, double d0, double epsilon,double T,
            double RA,double RB, double d1,double d2, double RC) {
  static const int ncth=1000;
  static const double Dcth=1./ncth;
  static const unsigned int nphi=1000;
  static const double Dphi=2.*M_PI/nphi;
  static const int nzcth=1000;
  static const double DZcth=1./nzcth;
  static Vector<double> vS(3);
  static Vector<double> vA(3),vB(3);
  copy(vS,0.);
  copy(vA,0.);
  copy(vB,0.);
  double zcth,zsth,cth,sth,phi,cphi,sphi;
  double szfac,sfac;
  double sum,sum1,sum2;
  double dA,dB,Func;
  double tmdA,tmdB,tmd1,tmd2,tmd3;
  double tmxL1,tmyL1;
  double tmxAL2,tmyAL2,tmxBL2,tmyBL2;
  tmdA=RA+d1;
  tmdB=RB+d2;
  sum=0;
  zcth=1;
  zsth=0;
  for(int zi=nzcth;zi>=-nzcth;--zi) {
    szfac=((zi==ncth)||(zi==-ncth)?0.5:1);
    tmxL1=R*zcth;
    tmyL1=R*zsth;
    sum1=0.;
    cth=1.;
    sth=0;
    for(int i=ncth;i>=-ncth;--i) {
      sfac=((i==ncth)||(i==-ncth)?0.5:1);
      tmd1=cth*zcth;
      tmd2=cth*zsth;
      tmxAL2=tmxL1-tmdA*tmd1;
      tmyAL2=tmyL1-tmdA*tmd2;
      tmxBL2=tmxL1+tmdB*tmd1;
      tmyBL2=tmyL1+tmdB*tmd2;
      sum2=0;
      phi=0;
      for(unsigned int pi=0;pi<nphi;++pi) {
        cphi=cos(phi);
        sphi=sin(phi);
        tmd1=sth*cphi;
        tmd2=tmd1*zcth;
        tmd1*=zsth;
        tmd3=sth*sphi;
        vA[0]=tmxAL2-tmdA*tmd1;
        vA[1]=tmyAL2+tmdA*tmd2;
        vA[2]=tmdA*tmd3;
        vB[0]=tmxBL2+tmdB*tmd1;
        vB[1]=tmyBL2-tmdB*tmd2;
        vB[2]=-tmdB*tmd3;
        dA=norm(vA);
        dB=norm(vB);
        if((vA[0]<=RA)||(vB[0]<=RB))      Func=0;
        else if((dA<RC+RA)||(dB<RC+RB))   Func=0;
        else if(LineSphereOverlap(vA,vB,vS,RC))   Func=0;
        else Func=ExpF1T(dA,d0,epsilon,T);
        sum2+=Func*Dphi;
        phi+=Dphi;
      }
      sum1+=sum2*sfac*Dcth;
      cth-=Dcth;
      sth=1-cth*cth;
      sth=sqrt(sth>0?sth:0);
    }
    sum+=sum1*szfac*DZcth;
    zcth-=DZcth;
    zsth=1-zcth*zcth;
    zsth=sqrt(zsth>0?zsth:0);
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
  
  R=6;
  d=0.1;
  
  r=0;
  r1=r2=0;
  //for(d=0.001;d<Nm;d+=0.001) {
  d=8.769; {
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

