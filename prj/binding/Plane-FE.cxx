
#include "data/basic/console-output.h"
#include "vector/interface.h"
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
  //static const int ncth=50000;
  //static const double Dcth=1./(ncth+0.);
  double sum1,sum2,sum;
  //double dA,dB;
  double tmdA,tmdB;
  tmdA=RA+d1;
  tmdB=RB+d2;
  double thU,thL;
  thU=(R-RA)/tmdA;
  thU=(thU>1?1:thU)*tmdA/d0;
  thL=(R-RB)/tmdB;
  thL=(thL>1?1:thL)*tmdA/d0;
  int nth=1000;
  double dthL,dthU;
  dthL=thL/nth;
  dthU=thU/nth;
  double pdL,pdU,dpdL,dpdU;
  sum1=0;
  pdL=epsilon/T*exp(-nth*dthL-R/d0);
  dpdL=exp(dthL);
  sum1+=0.5*exp(pdL);
  for(int i=-nth+1;i<0;++i) {
    pdL*=dpdL;
    sum1+=exp(pdL);
  }
  pdL*=dpdL;
  sum1+=0.5*exp(pdL);
  sum1*=dthL;
  sum2=0;
  pdU=epsilon/T*exp(-R/d0);
  dpdU=exp(dthU);
  sum2+=0.5*exp(pdU);
  for(int i=1;i<nth;++i) {
    pdU*=dpdU;
    sum2+=exp(pdU);
  }
  pdU*=dpdU;
  sum2+=0.5*exp(pdU);
  sum2*=dthU;
  sum=(sum1+sum2)*d0/tmdA;
  return sum;
}
      
double f(double d) {
  return -exp(-d/0.2)*10;
}

double S(double n, double d) {
  return 2*log(d)-d*d/n;
}

int main(int argc, char** argv) {
  if(argc<3)  { CErr<<"binding-plane.run <d0> <R-Value>"<<Endl<<Endl; return 1; }
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;

  const double e1=0;
  const double e2=0;
  const double epsilon=600;
  double d0=2;

  //const double T=1.48;    //Tf
  //const double T=1.036;
  const double T=1.07;    //Tf

  double d,d1,d2;
  unsigned int r,r1,r2;
  double R,RA,RB;
  double FL;
  unsigned int NA,NB,Nd;
  double C;

  d0=atof(argv[1]);
  R=atof(argv[2]);
  d=6;

  r=0;
  r1=r2=0;
  NA=N1+r1;
  NB=N2+r2;
  Nd=Nm-r;
  RA=pow(NA,1./3.);
  RB=pow(NB,1./3.);
  const double dstep=0.0002;
  const unsigned int MaxND=50000;
  unsigned nd=5;
  Vector<double> dv(MaxND);
  d=nd*dstep;
  //for(d=0.001;d<Nm;d+=0.0002) {
  for(unsigned int g=nd;g<MaxND;++g) {
    d1=(-RA*NA+(RB+d)*NB+d/2.*Nd)/(N+0.);
    d2=d-d1;
    
    C=(f(d)-T*S(Nd,d))-e1*r1-e2*r2;
    FL=Intg(R,d0,epsilon,T,RA,RB,d1,d2);
    FL=C-T*log(FL);
    //COut<<d<<"\t"<<C<<"\t"<<FL<<"\t11111111"<<Endl;
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

