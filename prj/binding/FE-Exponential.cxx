
#include "data/basic/console-output.h"
#include "data/basic/vector.h"
#include "data/basic/file-input.h"
#include  <cmath>
using namespace std;

double f1(double d,double d0,double epsilon) {
  return -epsilon*exp(-d/d0);
}

double ExpF1T(double d,double d0,double epsilon,double T) {
  return exp(-f1(d,d0,epsilon)/T);
}

void GenMesh(Vector<double>& Mesh, double db, double de, double delta,
             double d0,double epsilon,double T) {
  unsigned int n=static_cast<unsigned int>((de-db)/delta+0.5)+1;
  allocate(Mesh,n);
  double s=0,d=db;
  Mesh[0]=0;
  s+=0.5*ExpF1T(d,d0,epsilon,T);
  d+=delta;
  for(unsigned int i=1;i<n;++i) {
    s+=0.5*ExpF1T(d,d0,epsilon,T);
    Mesh[i]=s*delta;
    s+=0.5*ExpF1T(d,d0,epsilon,T);
    d+=delta;
  }
}

double IntFunc(double d, double d0, double delta, const Vector<double>& mesh) {
  if(d<d0) Error("Small");
  unsigned int n=static_cast<unsigned int>((d-d0)/delta);
  double shift=d-d0-n*delta;
  if(n+1>=mesh.size) { Error("Large"); return 0; }
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
  const double r0=2;

  const double T=1.48;

  Vector<double> MeshG;
  const double d0=3.5;
  const double delta=0.001;
  GenMesh(MeshG,d0,100,delta,r0,epsilon,T);

  double cthNear,cthFar;
  double d,d1,d2;
  unsigned int r,r1,r2,rMax;
  double R,RA,RB;
  double FL,SL;
  unsigned int NA,NB,Nd;
  double C,CG;

  R=10;
  d=0.12;

  for(d=0.001;d<Nm;d+=0.0002) {
    rMax=Nm-1;
    SL=0;
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
      CG=IntFunc((R-cthFar*(RA+d1)),d0,delta,MeshG)
        -IntFunc((R-cthNear*(RA+d1)),d0,delta,MeshG);
      FL=exp(-C/T)/(RA+d1)*CG;
    
      SL+=FL;
    }
    COut<<d<<"\t"<<-T*log(SL)<<Endl;
  }


  return 0;
}

