
#include "data/basic/console-output.h"
#include  <cmath>
using namespace std;

double f1(double d,double d0,double epsilon) {
  return -epsilon*exp(-d/d0);
}

double ExpF1T(double d,double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R, double d0, double epsilon,double T,
            double RA, double RB, double d1, double d2) {
  static const int ncth=1000;
  static const double Dcth=1./(ncth+0.);
  double cth,sth,sfac,Func,sum;
  double dA,dB;
  double tmdA,tmdB;
  tmdA=RA+d1;
  tmdB=RB+d2;
  sum=0;
  cth=1;
  sth=0;
  for(int i=ncth;i>=-ncth;--i) {
    sfac=((i==ncth)||(i==-ncth)?0.5:1);
    dA=R-tmdA*cth;
    dB=R+tmdB*cth;
    if((dA<RA)&&(dB<RB))  Func=0;
    else Func=ExpF1T(dA,d0,epsilon,T);
    sum+=Func*Dcth*sfac;
    cth-=Dcth;
    sth=1-cth*cth;
    sth=sqrt(sth>0?sth:0);
  }
  return sum;
}
      
double f(double d) {
  return -exp(-d/0.5)*10;
}

double S(double n, double d) {
  return 2*log(d)-d*d/n;
}

int main(int argc, char** argv) {
  if(argc<2)  { CErr<<"binding-plane.run <R-Value>"<<Endl<<Endl; }
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;

  const double e1=0;
  const double e2=0;
  const double epsilon=100;
  const double d0=2;

  const double T=1.48;

  double d,d1,d2;
  unsigned int r,r1,r2;
  double R,RA,RB;
  double FL;
  unsigned int NA,NB,Nd;
  double C;

  R=atof(argv[1]);
  d=6;

  r=0;
  r1=r2=0;
  for(d=0.001;d<Nm;d+=0.0002) {
    NA=N1+r1;
    NB=N2+r2;
    Nd=Nm-r;
    RA=pow(NA,1./3.);
    RB=pow(NB,1./3.);
    d1=(-RA*NA+(RB+d)*NB+d/2.*Nd)/(N+0.);
    d2=d-d1;
    
    C=(f(d)-T*S(Nd,d))-e1*r1-e2*r2;
    FL=exp(-C/T)*Intg(R,d0,epsilon,T,RA,RB,d1,d2);
    COut<<d<<"\t"<<-T*log(FL)<<Endl;
  }


  return 0;
}

