
#include "data/basic/console-output.h"
#include "overlap.h"
#include <cmath>
#include "vector/interface.h"
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d,double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R, double d0, double epsilon,double T,
            double RA,double RB, double d1,double d2, double RC) {
  //static const int ncth=1000;
  //static const double Dcth=1./(ncth+0.);
  //static Vector<double> vS(3);
  //static Vector<double> vA(3),vB(3);
  //copy(vS,0.);
  //copy(vA,0.);
  //copy(vB,0.);
  //double cth,sth,tmdA,tmdB,thdA,thdB,sum,sfac,dA,dB,Func;
  double tmdA,tmdB,thdA,thdB;
  double sum1,sum2,sum,sfac;
  tmdA=RA+d1;
  tmdB=RB+d2;
  thdA=RC+RA;
  thdB=RC+RB;
  double thU,thL,thUc,thLc,tmd;
  thU=(R*R+tmdA*tmdA-thdA*thdA)/(2*R*tmdA);
  thL=(R*R+tmdB*tmdB-thdB*thdB)/(2*R*tmdB);
  tmd=sqrt(R*R-RC*RC);
  thUc=(tmd<d1?tmd/R:1.0001);
  thLc=(tmd<d2?tmd/R:1.0001);
  thU=(thU>1?1:thU);
  thL=(thL>1?1:thL);
  thU=(thUc>thU?thU:thUc);
  thL=(thLc>thL?thL:thLc);
  int nth=1000;
  double dthL,dthU;
  dthL=thL/nth;
  dthU=thU/nth;
  sum1=0;
  sum1=0.5*exp(epsilon/T*exp(-sqrt(2*R*tmdA*nth*dthL+R*R+tmdA*tmdA)/d0));
  for(int i=-nth+1;i<0;++i) {
    sum1+=exp(epsilon/T*exp(-sqrt(-2*R*tmdA*i*dthL+R*R+tmdA*tmdA)/d0));
  }
  sum1+=0.5*exp(epsilon/T*exp(-sqrt(R*R+tmdA*tmdA)/d0));
  sum1*=dthL;
  sum2=0;
  sum2+=0.5*exp(epsilon/T*exp(-sqrt(R*R+tmdA*tmdA)/d0));
  for(int i=1;i<nth;++i) {
    sum2+=exp(epsilon/T*exp(-sqrt(-2*R*tmdA*i*dthU+R*R+tmdA*tmdA)/d0));
  }
  sum2+=0.5*exp(epsilon/T*exp(-sqrt(-2*R*tmdA*nth*dthU+R*R+tmdA*tmdA)/d0));
  sum2*=dthU;
  sum=sum1+sum2;
  return sum;
}

double f(double d) {
  return -exp(-d/0.2)*10;
}

double S(double n, double d) { return 2*log(d)-d*d/n; }

double SG(double r) { return 2*log(r); }

int main(int argc, char** argv) {
  if(argc<3)  { CErr<<"binding-sphere.run <R-Value>"<<Endl<<Endl; return 1; }
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;
  
  const double e1=0;
  const double e2=0;
  //const double T=1.48;
  const double T=1.07;
  
  double d0=1;
  d0=atof(argv[1]);
  //const double epsilon=200*exp(pow(N1,1./3.)*(1./d0-1./2.));
  const double epsilon=800.;
  const double rc=1;
  
  double d,d1,d2;
  unsigned int r,r1,r2;
  double R,RA,RB;
  double FL;
  unsigned int NA,NB,Nd;
  double C;

  const double dstep=0.0002;
  const unsigned int MaxND=50000;
  unsigned int nd;
  Vector<double> dv(MaxND);
  
  R=atof(argv[2]);
  if(R>12)  R=12;

  bool fg;
  int nmin;

  fg=false;
  //for(;R>5;R-=0.01) {
  d=0.25;
  
  r=0;
  r1=r2=0;
  NA=N1+r1;
  NB=N2+r2;
  Nd=Nm-r;
  RA=pow(NA,1./3.);
  RB=pow(NB,1./3.);
  nd=5;
  nd=284;
  d=nd*dstep;
  //for(unsigned int g=nd;g<MaxND;++g) {
  for(R=20;R>5;R-=0.01) {
    d1=(-RA*NA+(RB+d)*NB+d/2.*Nd)/(N+0.);
    d2=d-d1;
    
    C=(f(d)-T*S(Nd,d))-e1*r1-e2*r2-T*SG(R);
    FL=Intg(R,d0,epsilon,T,RA,RB,d1,d2,rc);
    FL=C-T*log(FL);
    //COut<<R<<"\t"<<-T*log(FL)<<Endl;
    //COut<<d<<"\t"<<-T*log(FL)<<Endl;
    COut<<R<<"\t"<<FL<<"\t"<<"aaaaaa"<<Endl;
    //dv[g]=FL;
    //d+=dstep;
  }

  /*
  nmin=0;
  COut.precision(8);
  for(unsigned int g=nd+1;g<MaxND-1;++g) {
    if((dv[g]-dv[g-1])*(dv[g]-dv[g+1])>0) {
      //COut<<R<<"\t"<<g*dstep<<"\t"<<dv[g]<<"\t";
      if(dv[g]>dv[g-1]) {} //COut<<"Max"<<Endl;
      else              { nmin++; } //COut<<"Min"<<Endl;
    }
  }
  //COut<<R<<"\t"<<nd*dstep<<"\t"<<dv[nd]<<"\t";
  if(dv[nd]<dv[nd+1]) {nmin++;} //COut<<"Min"<<Endl;
  else                {} //COut<<"Max"<<Endl;
  //COut<<R<<"\t"<<(MaxND-1)*dstep<<"\t"<<dv[MaxND-1]<<"\t";
  if(dv[MaxND-1]<dv[MaxND-2]) {nmin++;} //COut<<"Min"<<Endl;
  else                        {} //COut<<"Max"<<Endl;
  COut<<R<<"\t"<<nmin<<Endl;
  if(nmin==1)   { fg=true; COut<<R<<Endl; break; }
  }

  COut<<d0<<"\t";
  if(fg)    COut<<"Yes"<<Endl;
  else      COut<<"No"<<Endl;
  */
   
  return 0;
}

