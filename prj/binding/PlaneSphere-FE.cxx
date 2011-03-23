
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
  static const unsigned int ncth=1000;
  static const double Dcth=1./ncth;
  static const unsigned int nphi=1000;
  static const double Dphi=2.*M_PI/nphi;
  static const unsigned int nzcth=1000;
  static const double DZcth=1./nzcth;
  static Vector<double> vS(3);
  static Vector<double> vA(3),vB(3);
  copy(vS,0.);
  copy(vA,0.);
  copy(vB,0.);
  double zcth,zsth,cth,sth,phi,cphi,sphi;
  double szfac,sfac;
  double sum,sum1,sum2;
  double rA,rB,zA,zB,sum,sumtp,sump,szfac,sfac,Func;
  double tmdA,tmdB,tmdAA,tmdBB,tmcphi;
  sum=0;
  zcth=1;
  zsth=0;
  for(unsigned int zi=nzcth;zi>=-nzcth;--zi) {
    szfac=((zi==ncth)||(zi==-ncth)?0.5:1);
    vA[0]=R*zcth;
    vA[1]=R*zsth;
    vA[2]=0.;
    copy(vB,vA);
    sum1=0.;
    cth=1.;
    sth=0;
    for(unsigned int i=ncth;i>=-ncth;--i) {
      sfac=((i==ncth)||(i==-ncth)?0.5:1);
      vA[0]-=(RA+d1)*cth*zcth;
      vA[1]-=(RA+d1)*cth*zsth;
      vB[0]+=(RB+d2)*cth*zcth;
      vB[1]+=(RB+d2)*cth*zsth;
      sum2=0;
      phi=0;
      for(unsigned int pi=0;pi<nphi;++pi) {
        cphi=cos(phi);
        sphi=sin(phi);
        vA[0]-=(RA+d1)*sth*cphi*zsth;
        vA[1]+=(RA+d1)*sth*cphi*zcth;
        vA[2]+=(RA+d1)*sth*sphi;
        vB[0]+=(RB+d2)*sth*cphi*zsth;
        vB[1]-=(RB+d2)*sth*cphi*zcth;
        vB[1]-=(RB+d2)*sth*sphi;
        dA=norm(vA);
        dB=norm(vB);
        if((vA[0]<=0)||(vB[0]<=0))        Func=0;
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
        if((zA<=0)||(zB<=0)||(rA<RC+RA)||(rB<RC+RB)||((R*R*(1-cth*cth)<RC*RC)&&((RA+d1>R*cth)&&(RB+d2>-R*cth))))
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

