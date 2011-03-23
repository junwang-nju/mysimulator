
#include "data/basic/console-output.h"
#include <cmath>
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d, double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

bool CheckOverlap(double x1,double y1,double z1,
                  double x2,double y2,double z2,
                  double xc,double yc,double zc,double rc) {
  double lx,ly,lz,l;
  double rx,ry,rz,rcth,rsth;
  lx=x2-x1;
  ly=y2-y1;
  lz=z2-z1;
  l=sqrt(lx*lx+ly*ly+lz*lz);
  lx/=l;
  ly/=l;
  lz/=l;
  rx=xc-x1;
  ry=yc-y1;
  rz=zc-z1;
  rcth=rx*lx+ry*ly+rz*lz;
  rsth=sqrt(rx*rx+ry*ry+rz*rz-rcth*rcth);
  return (rsth<rc)&&(l>rcth);
}

double Intg(double R,double d0,double epsilon,double T,
            double RA1,double RB1,double RA2,double RB2,
            double d11,double d21,double d12,double d22) {
  static const double Dcth=0.01;
  static const double Dphi=0.01*2*M_PI;
  double Func,sum,sum1,sum2,sum3,sfac1,sfac2;
  double xA1,yA1,zA1;
  double xB1,yB1,zB1;
  double xA2,yA2,zA2;
  double xB2,yB2,zB2;
  double dAA,dAB,dBA,dBB;
  double tmd;
  sum=0;
  for(double cth1=1,sth1;cth1>-1-0.5*Dcth;cth1-=Dcth) {
    sth1=(fabs(cth1)>1-0.5*Dcth?0:sqrt(1-cth1*cth1));
    sfac1=(fabs(cth1)>1-0.5*Dcth?0.5:1);
    sum1=0;
    for(double cth2=1,sth2;cth2>-1-0.5*Dcth;cth2-=Dcth) {
      sth2=(fabs(cth2)>1-0.5*Dcth?0:sqrt(1-cth2*cth2));
      sfac2=(fabs(cth2)>1-0.5*Dcth?0.5:1);
      sum2=0;
      for(double phi1=0;phi1<2*M_PI;phi1+=Dphi) {
        sum3=0;
        for(double phi2=0;phi2<2*M_PI;phi2+=Dphi) {
          xA1=R*0.5-(RA1+d11)*cth1;
          xB1=R*0.5+(RB1+d21)*cth1;
          xA2=-R*0.5+(RA2+d12)*cth2;
          xB2=-R*0.5-(RB2+d22)*cth2;
          tmd=xA1-xA2;    dAA=tmd*tmd;
          tmd=xB1-xB2;    dBB=tmd*tmd;
          tmd=xA1-xB2;    dAB=tmd*tmd;
          tmd=xB1-xA2;    dBA=tmd*tmd;
          yA1=(RA1+d11)*sth1*cos(phi1);
          yB1=-(RB1+d21)*sth1*cos(phi1);
          yA2=-(RA2+d12)*sth2*cos(phi2);
          yB2=(RB2+d22)*sth2*cos(phi2);
          tmd=yA1-yA2;    dAA+=tmd*tmd;
          tmd=yB1-yB2;    dBB+=tmd*tmd;
          tmd=yA1-yB2;    dAB+=tmd*tmd;
          tmd=yB1-yA2;    dBA+=tmd*tmd;
          zA1=(RA1+d11)*sth1*sin(phi1);
          zB1=-(RB1+d21)*sth1*sin(phi1);
          zA2=-(RA2+d12)*sth2*sin(phi2);
          zB2=(RB2+d22)*sth2*sin(phi2);
          tmd=zA1-zA2;    dAA+=tmd*tmd;
          tmd=zB1-zB2;    dBB+=tmd*tmd;
          tmd=zA1-zB2;    dAB+=tmd*tmd;
          tmd=zA2-zB1;    dBA+=tmd*tmd;
          dAA=sqrt(dAA);
          dBB=sqrt(dBB);
          dAB=sqrt(dAB);
          dBA=sqrt(dBA);
          if((dAA<RA1+RA2)||(dBB<RB1+RB2)||(dAB<RA1+RB2)||(dBA<RB1+RA2))
            Func=0;
          else if(CheckOverlap(xA1,yA1,zA1,xB1,yB1,zB1,xA2,yA2,zA2,RA2))
            Func=0;
          else if(CheckOverlap(xA1,yA1,zA1,xB1,yB1,zB1,xB2,yB2,zB2,RB2))
            Func=0;
          else if(CheckOverlap(xA2,yA2,zA2,xB2,yB2,zB2,xA1,yA1,zA1,RA1))
            Func=0;
          else if(CheckOverlap(xA2,yA2,zA2,xB2,yB2,zB2,xB1,yB1,zB1,RB1))
            Func=0;
          else  Func=ExpF1T(dAA,d0,epsilon,T);
          sum3+=Dphi;
        }
        sum2+=sum3*Dphi;
      }
      sum1+=sum2*Dcth*sfac2;
    }
    sum+=sum1*Dcth*sfac1;
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

