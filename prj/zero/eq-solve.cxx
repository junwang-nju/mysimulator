
#include "vector.h"
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

void f(const double& u, const double& v, double& tu, double& tv) {
  double p,q;
  tu=u*u-v*v;       tv=2*u*v;
  p=tu*u-tv*v;      q=tu*v+u*tv;
  tu=p-1.;          tv=q;
}

void iteration(const Vector<double>& u, const Vector<double>& v,
               const unsigned int I, double& tu, double& tv) {
  assert(u.size==v.size);
  unsigned int n=u.size;
  double ru,rv,p,q;
  ru=u[I];  rv=v[I];
  tu=1;   tv=0;
  for(unsigned int i=0;i<n;++i) {
    if(i==I)  continue;
    p=tu*(ru-u[i])-tv*(rv-v[i]);
    q=tu*(rv-v[i])+tv*(ru-u[i]);
    tu=p;
    tv=q;
  }
  p=1./(tu*tu+tv*tv);
  tu*=p;
  tv*=-p;
  f(ru,rv,p,q);
  ru=tu*p-tv*q;   rv=tu*q+tv*p;
  tu=ru;          tv=rv;
}

int main() {
  Vector<double> a;
  Vector<double> u,v;
  double fu,fv;

  allocate(a,4);
  allocate(u,3);
  allocate(v,3);

  u[0]=1;     v[0]=0;
  u[1]=0.4;   v[1]=0.9;
  u[2]=-0.65; v[2]=0.72;

  double d;

  do {
    d=0.;
    iteration(u,v,0,fu,fv);
    d+=fabs(fu)+fabs(fv);
    u[0]-=fu;    v[0]-=fv;
    iteration(u,v,1,fu,fv);
    d+=fabs(fu)+fabs(fv);
    u[1]-=fu;    v[1]-=fv;
    iteration(u,v,2,fu,fv);
    d+=fabs(fu)+fabs(fv);
    u[2]-=fu;    v[2]-=fv;
    cout<<d<<"\t"<<fu<<"\t"<<fv<<endl;
  } while(d>1e-6);
  
  cout<<u<<endl;
  cout<<v<<endl;
  return 0;
}

