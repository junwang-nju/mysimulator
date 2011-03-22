
#include "data/basic/console-output.h"
#include <cmath>
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d, double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R,double d0,double epsilon,double T,
            double RA1,double RB1,double RA2,double RB2,
            double d11,double d21,double d12,double d22) {
  static const double Dcth=0.001;
  static const double Dphi=0.001*2*M_PI;
  double Func,sum;
  double dAA,dAB,dBA,dBB;
  double tmd;
  sum=0;
  for(double cth1=1,sth1;cth1=-1-0.5*Dcth;cth1-=Dcth) {
    sth1=(fabs(cth1)>1-0.5*Dcth?0:sqrt(1-cth1*cth1));
    for(double cth2=1,sth2;cth2=-1-0.5*Dcth;cth2-=Dcth) {
      sth2=(fabs(cth2)>1-0.5*Dcth?0:sqrt(1-cth2*cth2));
      for(double phi1=0;phi1<2*M_PI;phi1+=Dphi) {
        for(double phi2=0;phi2<2*M_PI;phi2+=Dphi) {
          tmd=R-(RA1+d11)*cth1-(RA2+d12)*cth2;
          dAA=tmd*tmd;
          tmd=R+(RB1+d21)*cth1+(RB2+d22)*cth2;
          dBB=tmd*tmd;
          tmd=R-(RA1+d11)*cth1+(RB2+d22)*cth2;
          dAB=tmd*tmd;
          tmd=R+(RB1+d21)*cth1-(RA2+d12)*cth2;
          dBA=tmd*tmd;
          tmd=(RA1+d11)*sth1*cos(phi1)+(RA2+d12)*sth2*cos(phi2);
          dAA+=tmd*tmd;
          tmd=-(RB1+d21)*sth1*cos(phi1)-(RB2+d22)*sth2*cos(phi2);
          dBB+=tmd*tmd;
          tmd=(RA1+d11)*sth1*cos(phi1)-(RB2+d22)*sth2*cos(phi2);
          dAB+=tmd*tmd;
          tmd=-(RB1+d21)*sth1*cos(phi1)+(RA2+d12)*sth2*cos(phi2);
          dBA+=tmd*tmd;
          tmd=(RA1+d11)*sth1*sin(phi1)+(RA2+d12)*sth2*sin(phi2);
          dAA+=tmd*tmd;
          tmd=-(RB1+d21)*sth1*sin(phi1)-(RB2+d22)*sth2*sin(phi2);
          dBB+=tmd*tmd;
          tmd=(RA1+d11)*sth1*sin(phi1)-(RB2+d22)*sth2*sin(phi2);
          dAB+=tmd*tmd;
          tmd=-(RB1+d21)*sth1*sin(phi1)+(RA2+d12)*sth2*sin(phi2);
          dBA+=tmd*tmd;
          dAA=sqrt(dAA);
          dBB=sqrt(dBB);
          dAB=sqrt(dAB);
          dBA=sqrt(dBA);
          if((dAA<RA1+RA2)||(dBB<RB1+RB2)||(dAB<RA1+RB2)||(dBA<RB1+RA2))
            Func=0;
          else  Func=ExpF1T(rAA,d0,epsilon,T);
        }
      }
    }
  }
}

int main() {
  return 0;
}

