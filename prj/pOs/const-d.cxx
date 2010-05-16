
#include "property-list.h"
#include "random-generator-boxmuller.h"
#include "random-generator-generic.h"
#include <iostream>
#include <fstream> 
#include <cmath>
using namespace std;

double repE(const Vector<double>& xa, const Vector<double>& xb,
           Vector<double>& v) {
  v=xa; shift(v,-1.,xb);
  double dsq=normSQ(v);
  if(dsq>1) return 0.;
  double ivd2=1./dsq;
  double ivd6=ivd2*ivd2*ivd2;
  return ivd6*(ivd6-2.)+1;
}

void rep(const Vector<double>& xa, const Vector<double>& xb,
         Vector<double>& ga, Vector<double>& gb, Vector<double>& v) {
  // for monomer pair
  v=xa; shift(v,-1.,xb);
  double dsq=normSQ(v);
  if(dsq>1) return;   // assume radius=1
  double ivd2=1./dsq;
  double ivd6=ivd2*ivd2*ivd2;
  double f=12*ivd6*(1.-ivd6)*ivd2;  //assume strength=1
  shift(ga,+f,v);
  shift(gb,-f,v);
}

double feneE(const Vector<double>& xa, const Vector<double>& xb,
            Vector<double>& v) {
  v=xa; shift(v,-1.,xb);
  double d=norm(v);
  double Dd=d-1.;
  return -0.5*log(1-Dd*Dd*100);
}

void fene(const Vector<double>& xa, const Vector<double>& xb,
          Vector<double>& ga, Vector<double>& gb, Vector<double>& v) {
  v=xa; shift(v,-1.,xb);
  double d=norm(v);
  double Dd=d-1.;
  double f=100/(1-Dd*Dd*100)*Dd/d;
  shift(ga,+f,v);
  shift(gb,-f,v);
}

static const double epsilon=1.0;
static const double sradius=5;

double sphereE(const Vector<double>& x, Vector<double>& v) {
  double d=norm(x);
  double dx=d-sradius;
  double ivd2=1./(dx*dx);
  double ivd6=ivd2*ivd2*ivd2;
  return epsilon*ivd6*(ivd6-2.);
}

void sphere(const Vector<double>& x, Vector<double>& g, Vector<double>& v) {
  double d=norm(x);
  double dx=d-sradius;
  double ivd2=1./(dx*dx);
  double ivd6=ivd2*ivd2*ivd2;
  double f=12*epsilon*ivd6*(1.-ivd6)/(dx*d);
  shift(g,f,x);
}

double RsphereE(const Vector<double>& x, Vector<double>& v) {
  double d=norm(x);
  double dx=d-sradius;
  if(dx>1)  return 0;
  double ivd2=1./(dx*dx);
  double ivd6=ivd2*ivd2*ivd2;
  return epsilon*(ivd6*(ivd6-2.)+1);
}

void Rsphere(const Vector<double>& x, Vector<double>& g, Vector<double>& v) {
  double d=norm(x);
  double dx=d-sradius;
  if(dx>1)  return;
  double ivd2=1./(dx*dx);
  double ivd6=ivd2*ivd2*ivd2;
  double f=12*epsilon*ivd6*(1.-ivd6)/(dx*d);
  shift(g,f,x);
}

static const unsigned int Kcen=10;
static const unsigned int dcen=10;

double centerE(const Vector<double>* x, Vector<double>& v, const unsigned int n){
  assign(v,x[0]);
  for(unsigned int i=1;i<n;++i)  shift(v,x[i]);
  scale(v,1./n);
  double d=norm(v);
  double Dd=d-dcen;
  return Kcen*Dd*Dd;
}

void center(const Vector<double>* x, Vector<double>* g, Vector<double>& v,
            const unsigned int n) {
  assign(v,x[0]);
  for(unsigned int i=1;i<n;++i)  shift(v,x[i]);
  scale(v,1./n);
  double d=norm(v);
  double Dd=d-dcen;
  double f=(Kcen+Kcen)*Dd/(n*d);
  for(unsigned int i=0;i<n;++i)
    shift(g[i],f,v);
}

static const double dragF=1;
             
void drag(const Vector<double>* x, Vector<double>* g, Vector<double>& v,
          unsigned int n) {
  assign(v,x[0]);
  for(unsigned int i=1;i<n;++i)  shift(v,x[i]);
  scale(v,1./n);
  double d=norm(v);
  if(d>dcen)  scale(v,1./d);
  else        scale(v,-1./d);
  for(unsigned int i=0;i<n;++i)
    shift(g[i],dragF/n,v);
}

int main() {
  BoxMuller<dSFMT<216091> > gng;
  allocate(gng);
  init(gng,12721849);

  const unsigned int nunit=100;
  PropertyList<double> X,V,G,rV;
  Vector<unsigned int> sz;
  allocate(sz,nunit);
  assign(sz,3);
  allocate(X,sz(),sz.size);
  allocate(V,sz(),sz.size);
  allocate(G,sz(),sz.size);
  allocate(rV,sz(),sz.size);

  for(unsigned int i=0;i<nunit;++i) assign(X,0.);
  for(unsigned int i=0;i<nunit;++i) X[i][0]=i;
  for(unsigned int i=0;i<nunit;++i) X[i][1]=6;
  fillarray(gng,V);
  scale(V,0.01);
  assign(G,0);
  ifstream ifs;
  ifs.open("init-d10");
  ifs>>X;
  ifs.close();

  Vector<double> v;
  allocate(v,3);

  for(unsigned int i=0;i<nunit-1;++i) fene(X[i],X[i+1],G[i],G[i+1],v);
  for(unsigned int i=0;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j)
    rep(X[i],X[j],G[i],G[j],v);
  //for(unsigned int i=0;i<nunit;++i) Rsphere(X[i],G[i],v);
  center(X.structure,G.structure,v,nunit);
  //drag(X.structure,G.structure,v,nunit);
  double e,e1,e2,e3,ke;
  e1=e2=e3=0;
  for(unsigned int i=0;i<nunit-1;++i) e1+=feneE(X[i],X[i+1],v);
  for(unsigned int i=0;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j) e1+=repE(X[i],X[j],v);
  //for(unsigned int i=0;i<nunit;++i)   e2+=RsphereE(X[i],v);
  e3=centerE(X.structure,v,nunit);
  e=e1+e2+e3;
  ke=0.5*normSQ(V);
  assign(v,0.);
  for(unsigned int i=0;i<nunit;++i) shift(v,X[i]);
  scale(v,1./nunit);

  double dt=0.001, hdt=0.5*dt;
  double T=0.1,gamma=0.5;
  double gFac=sqrt(gamma*T*dt);
  double sFac1=1-gamma*hdt;
  double sFac2=1./(1+gamma*hdt);

  cout<<0<<"\t"<<e<<"\t"<<ke<<"\t"<<e1<<"\t"<<e2<<"\t"<<e3<<"\t"<<norm(v)<<endl;
  for(unsigned int rt=0;rt<10000000;++rt) {
    scaleshift(V,sFac1,-hdt,G);
    fillarray(gng,rV);
    shift(V,gFac,rV);
    shift(X,dt,V);
    assign(G,0.);
    for(unsigned int i=0;i<nunit-1;++i) fene(X[i],X[i+1],G[i],G[i+1],v);
    for(unsigned int i=0;i<nunit;++i)
    for(unsigned int j=i+2;j<nunit;++j) rep(X[i],X[j],G[i],G[j],v);
    //for(unsigned int i=0;i<nunit;++i) Rsphere(X[i],G[i],v);
    center(X.structure,G.structure,v,nunit);
    //drag(X.structure,G.structure,v,nunit);
    shift(V,-hdt,G);
    fillarray(gng,rV);
    shift(V,gFac,rV);
    scale(V,sFac2);
    if((rt+1)%1000==0) {
      e1=e2=e3=0;
      for(unsigned int i=0;i<nunit-1;++i) e1+=feneE(X[i],X[i+1],v);
      for(unsigned int i=0;i<nunit;++i)
      for(unsigned int j=i+2;j<nunit;++j) e1+=repE(X[i],X[j],v);
      //for(unsigned int i=0;i<nunit;++i)   e2+=RsphereE(X[i],v);
      e3=centerE(X.structure,v,nunit);
      e=e1+e2+e3;
      ke=0.5*normSQ(V);
      for(unsigned int i=0;i<nunit;++i) shift(v,X[i]);
      scale(v,1./nunit);
      cout<<rt+1<<"\t"<<e<<"\t"<<ke<<"\t"<<e1<<"\t"<<e2<<"\t"<<e3<<"\t"<<norm(v)<<endl;
    }
  }

  cout<<endl;
  cout<<X<<endl;

  release(rV);
  release(G);
  release(V);
  release(X);
  return 0;
}

