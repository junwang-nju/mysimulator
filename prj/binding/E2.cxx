
#include "data/basic/console-output.h"
#include "vector/interface.h"
#include <cmath>
using namespace std;

double f1(double d, double d0, double epsilon) { return -epsilon*exp(-d/d0); }

double ExpF1T(double d,double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

double Intg(double R, double d0, double epsilon,double T,
            double RA,double RB, double d1,double d2, double RC) {
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
  for(int i=-nth;i<=0;++i) {
    if((i==-nth)||(i==0)) sfac=0.5;
    else sfac=1.;
    tmd=sqrt(R*R+tmdA*tmdA-2*R*tmdA*i*dthL);
    sum1+=sfac*ExpF1T(tmd,d0,epsilon,T);
    //sum1+=sfac*exp(epsilon/T*exp(-sqrt(-2*R*tmdA*i*dthL+R*R+tmdA*tmdA)/d0));
  }
  sum1*=dthL;
  sum2=0;
  for(int i=0;i<=nth;++i) {
    if((i==nth)||(i==0)) sfac=0.5;
    else sfac=1.;
    tmd=sqrt(R*R+tmdA*tmdA-2*R*tmdA*i*dthU);
    sum2+=sfac*ExpF1T(tmd,d0,epsilon,T);
    //sum2+=sfac*exp(epsilon/T*exp(-sqrt(-2*R*tmdA*i*dthU+R*R+tmdA*tmdA)/d0));
  }
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
  if(argc<2)  { CErr<<"binding-sphere.run <R-Value>"<<Endl<<Endl; return 1; }
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;
  
  const double e1=0;
  const double e2=0;
  //const double T=1.48;
  const double T=1.28324;
  
  const double d0=8;
  const double rc=1;
  //const double epsilon=100;
  const double epsilon=100*exp((pow(N1,1./3.)+rc)*(1./d0-1./2.));
  
  double d,d1,d2;
  unsigned int r,r1,r2;
  double R,RA,RB;
  double FL;
  unsigned int NA,NB,Nd;
  double C;
  
  R=atof(argv[1]);
  d=0.25;
  
  r=0;
  r1=r2=0;
  NA=N1+r1;
  NB=N2+r2;
  Nd=Nm-r;
  RA=pow(NA,1./3.);
  RB=pow(NB,1./3.);
  const double dstep=0.0002;
  const unsigned int MaxND=50000;
  unsigned int nd=5;
  Vector<double> dv(MaxND);
  d=nd*dstep;

  for(unsigned int g=nd;g<MaxND;++g) {
    d1=(-RA*NA+(RB+d)*NB+d/2.*Nd)/(N+0.);
    d2=d-d1;
    
    C=(f(d)-T*S(Nd,d))-e1*r1-e2*r2-T*SG(R);
    FL=Intg(R,d0,epsilon,T,RA,RB,d1,d2,rc);
    FL=C-T*log(FL);
    //COut<<f1(pow(NA,1./3.)+rc,d0,epsilon)<<Endl;
    //getchar();
    dv[g]=FL;
    d+=dstep;
  }

  COut.precision(8);
  for(unsigned int g=nd+1;g<MaxND-1;++g) {
    if((dv[g]-dv[g-1])*(dv[g]-dv[g+1])>0) {
      COut<<R<<"\t"<<g*dstep<<"\t"<<dv[g]<<"\t";
      if(dv[g]>dv[g-1]) COut<<"Max"<<Endl;
      else              COut<<"Min"<<Endl;
    }
  }
  COut<<R<<"\t"<<nd*dstep<<"\t"<<dv[nd]<<"\t";
  if(dv[nd]<dv[nd+1]) COut<<"Min"<<Endl;
  else                COut<<"Max"<<Endl;
  COut<<R<<"\t"<<(MaxND-1)*dstep<<"\t"<<dv[MaxND-1]<<"\t";
  if(dv[MaxND-1]<dv[MaxND-2]) COut<<"Min"<<Endl;
  else                        COut<<"Max"<<Endl;

   
  return 0;
}

