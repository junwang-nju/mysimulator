
#include "data/basic/console-output.h"
#include "data/basic/vector.h"
#include "data/basic/file-input.h"
#include  <cmath>
using namespace std;

double f1(double d) {
  return -pow(d,-2.);
}

double IntFunc(double d, double d0, double delta, const Vector<double>& mesh,
               const double slope) {
  if(d<d0) Error("Small");
  unsigned int n=static_cast<unsigned int>((d-d0)/delta);
  double shift=d-d0-n*delta;
  if(n+1>=mesh.size)
    return mesh[mesh.size-1]+slope*(d-(d0+(mesh.size-1)*delta));
  return mesh[n]+shift/delta*(mesh[n+1]-mesh[n]);
}

double f(double d) {
  //return -pow(d/8.,-6);
  return -exp(-d/0.5)*10;
}

double S(double n, double d) {
  double tm=2*log(d)-d*d/n;
  if(d<n) return tm;
  else return tm-100*(d-n)*(d-n);
}

int main() {
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=10;
  const unsigned int N=N1+N2+Nm;

  const double e1=0;
  const double e2=0;
  const double epsilon=100;

  const unsigned int NData=99651;
  Vector<double> MeshG, MeshFG;
  const double d0=0.35;
  const double delta=0.001;
  allocate(MeshG,NData);
  allocate(MeshFG,NData);
  FileInput FI;
  allocate(FI,"integral.coulomb-attract");
  for(unsigned int i=0;i<NData;++i) {
    double tmd;
    FI>>tmd>>MeshG[i]>>MeshFG[i];
  }
  release(FI);

  double cthNear,cthFar;
  double d,d1,d2;
  unsigned int r,r1,r2,rMax;
  double R,RA,RB;
  double FU,FL,T,SU,SL;
  unsigned int NA,NB,Nd;
  double C,CFG,CG;

  T=1.48;
  R=4;
  d=0.12;

  //for(R=3.8;R<40;R+=0.1) {
  for(d=0.001;d<Nm;d+=0.0002) {
    //rMax=Nm-(static_cast<unsigned int>(d-d*DRelDelta)+1);
    rMax=Nm-1;
    SU=SL=0;
    r=0;
    //for(r=0;r<=rMax;++r)
    for(r1=0;r1<=r;++r1) {
      r2=r-r1;
      NA=N1+r1;
      NB=N2+r2;
      Nd=Nm-r;
      RA=pow(NA,1./3.);
      RB=pow(NB,1./3.);
      d1=(-RA*NA+(RB+d)*NB+d/2.*Nd)/(N+0.);
      d2=d-d1;
      cthNear=(R-RA)/(RA+d1);
      if(cthNear>1.)    cthNear=1.;
      cthFar=-(R-RB)/(RB+d2);
      if(cthFar<-1.)    cthFar=-1.;
    
      C=(f(d)-T*S(Nd,d))-e1*r1-e2*r2;
      CG=IntFunc((R-cthFar*(RA+d1))*sqrt(T/epsilon),d0,delta,MeshG,1)
        -IntFunc((R-cthNear*(RA+d1))*sqrt(T/epsilon),d0,delta,MeshG,1);
      CFG=IntFunc((R-cthFar*(RA+d1))*sqrt(T/epsilon),d0,delta,MeshFG,0)
        -IntFunc((R-cthNear*(RA+d1))*sqrt(T/epsilon),d0,delta,MeshFG,0);
      FU=exp(-C/T)*sqrt(epsilon/T)/(RA+d1)*(T*CFG+C*CG);
      FL=exp(-C/T)*sqrt(epsilon/T)/(RA+d1)*CG;
    
      SU+=FU;
      SL+=FL;
    }
    //COut<<R<<"\t"<<log(SL)<<"\t"<<SU/SL<<Endl;
    COut<<d<<"\t"<<-T*log(SL)<<Endl;
  }


  return 0;
}

