
#include "data/basic/console-output.h"
#include "overlap.h"
#include <cmath>
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d, double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R,double d0,double epsilon,double T,
            double RA1,double RB1,double RA2,double RB2,
            double d11,double d21,double d12,double d22) {
  static const int ncth=100;
  static const double Dcth=1./ncth;
  static const unsigned int nphi=100;
  static const double Dphi=2*M_PI/nphi;
  static Vector<double> vA1(3),vB1(3),vA2(3),vB2(3),tmV(3);
  double Func,sum,sum1,sum2,sum3,sfac1,sfac2;
  double cth1,sth1,cth2,sth2,phi1,phi2;
  double dAA,dAB,dBA,dBB;
  double halfR,rA1,rB1,rA2,rB2,rAA,rBB,rAB,rBA;
  halfR=0.5*R;
  rA1=RA1+d11;
  rA2=RA2+d12;
  rB1=RB1+d21;
  rB2=RB2+d22;
  rAA=RA1+RA2;
  rAB=RA1+RB2;
  rBA=RB1+RA2;
  rBB=rB1+RB2;
  double xA1,xB1,xA2,xB2,cphi1,sphi1,cphi2,sphi2;
  double SrA1,SrB1,SrA2,SrB2;
  double yA1,yB1,zA1,zB1;
  sum=0;
  cth1=0;
  sth1=0;
  for(int i1=ncth;i1>=-ncth;--i1) {
    sfac1=((i1==ncth)||(i1==-ncth)?0.5:1);
    xA1=halfR-rA1*cth1;
    xB1=halfR-rB1*cth1;
    SrA1=rA1*sth1;
    SrB1=rB1*sth1;
    sum1=0;
    cth2=1;
    sth2=0;
    for(int i2=ncth;i2>=-ncth;--i2) {
      sfac2=((i2==ncth)||(i2==-ncth)?0.5:1);
      xA2=-halfR+rA2*cth2;
      xB2=-halfR-rB2*cth2;
      SrA2=rA2*sth2;
      SrB2=rB2*sth2;
      sum2=0;
      phi1=0;
      for(unsigned int pi1=0;pi1<nphi;++pi1) {
        cphi1=cos(phi1);
        sphi1=sin(phi1);
        yA1=SrA1*cphi1;
        yB1=-SrB1*cphi1;
        zA1=SrA1*sphi1;
        zB1=-SrB1*sphi1;
        sum3=0;
        phi2=0;
        for(unsigned int pi2=0;pi2<nphi;++pi2) {
          cphi2=cos(phi2);
          sphi2=sin(phi2);
          vA1[0]=xA1;
          vB1[0]=xB1;
          vA2[0]=xA2;
          vB2[0]=xB2;
          vA1[1]=yA1;
          vB1[1]=yB1;
          vA2[1]=-SrA2*cphi2;
          vB2[1]=SrB2*cphi2;
          vA1[2]=zA1;
          vB1[2]=zB1;
          vA2[2]=-SrA2*sphi2;
          vB2[2]=SrB2*sphi2;
          copy(tmV,vA1);  shift(tmV,-dOne,vA2);   dAA=norm(tmV);
          copy(tmV,vA1);  shift(tmV,-dOne,vB2);   dAB=norm(tmV);
          copy(tmV,vB1);  shift(tmV,-dOne,vA2);   dBA=norm(tmV);
          copy(tmV,vB1);  shift(tmV,-dOne,vB2);   dBB=norm(tmV);
          if((dAA<rAA)||(dBB<rBB)||(dAB<rAB)||(dBA<rBA))
            Func=0;
          else if(LineSphereOverlap(vA1,vB1,vA2,RA2))   Func=0;
          else if(LineSphereOverlap(vA1,vB1,vB2,RB2))   Func=0;
          else if(LineSphereOverlap(vA2,vB2,vA1,RA1))   Func=0;
          else if(LineSphereOverlap(vA2,vB2,vB1,RB1))   Func=0;
          else  Func=ExpF1T(dAA,d0,epsilon,T);
          sum3+=Dphi;
          phi2+=Dphi;
        }
        sum2+=sum3*Dphi;
        phi1+=Dphi;
      }
      sum1+=sum2*Dcth*sfac2;
      cth2+=Dcth;
      sth2=1-cth2*cth2;
      sth2=(sth2>0?sqrt(sth2):0);
    }
    sum+=sum1*Dcth*sfac1;
    cth1+=Dcth;
    sth1=1-cth1*cth1;
    sth1=(sth1>0?sqrt(sth1):0);
  }
  return sum;
}

double f(double d) { return -exp(-d/0.5)*10.; }

double S(double n,double d) { return 2*log(d)-d*d/n; }

double SG(double r) { return 2*log(r); }

int main() {
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;

  const double e1=0.;
  const double e2=0.;
  const double epsilon=100;
  const double T=1.48;

  const double d0=2;

  double d1,d2,d11,d21,d12,d22;
  unsigned int r1,r2,r11,r21,r12,r22;
  double R,RA1,RB1,RA2,RB2;
  double FL;
  unsigned int NA1,NB1,Nd1,NA2,NB2,Nd2;
  double C;

  R=20;
  d1=d2=0.1;
  r1=r2=0;
  r11=r21=r12=r22=0;
  for(d1=0.001;d1<Nm;d1+=0.001)
  for(d2=0.001;d2<Nm;d2+=0.001) {
    NA1=N1+r11;
    NB1=N2+r21;
    NA2=N1+r12;
    NB2=N2+r22;
    Nd1=Nm-r1;
    Nd2=Nm-r2;
    RA1=pow(NA1,-1./3.);
    RB1=pow(NB1,-1./3.);
    RA2=pow(NA2,-1./3.);
    RB2=pow(NB2,-1./3.);
    d11=(-RA1*NA1+(RB1+d1)*NB1+d1/2.*Nd1)/(N+0.);
    d21=d1-d11;
    d12=(-RA2*NA2+(RB2+d2)*NB2+d2/2.*Nd2)/(N+0.);
    d22=d2-d12;

    C=(f(d1)-T*S(Nd1,d1))+(f(d2)-T*S(Nd2,d2))-e1*r11-e2*r21-e1*r12-e2*r22-T*SG(R);
    FL=exp(-C/T)*Intg(R,d0,epsilon,T,RA1,RB1,RA2,RB2,d11,d21,d12,d22);
    COut<<d1<<"\t"<<d2<<"\t"<<-T*log(FL)<<Endl;
  }
  return 0;
}

