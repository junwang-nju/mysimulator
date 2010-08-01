
#include "vector.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void f(const double& u, const double& v, const Vector<double>& a,
       double& tu, double& tv) {
  double p,q;
  tu=0;   tv=0;
  for(int i=a.size-1;i>=0;--i) {
    p=tu*u-tv*v;    q=tu*v+tv*u;
    tu=p+a[i];      tv=q;
  }
}

void iteration(const Vector<double>& u, const Vector<double>& v,
               const Vector<double>& a,
               const unsigned int I, double& tu, double& tv) {
  assert(u.size==v.size);
  unsigned int n=u.size;
  double ru,rv,p,q=0;
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
  f(ru,rv,a,p,q);
  ru=tu*p-tv*q;   rv=tu*q+tv*p;
  tu=ru;          tv=rv;
}

int main() {
  Vector<double> a;
  Vector<double> u,v;
  double fu,fv;
  
  ifstream ifs("16.e.f0");
  unsigned int NE;
  ifs>>NE;
  allocate(a,NE+1);
  allocate(u,NE);
  allocate(v,NE);
  for(unsigned int i=0;i<=NE;++i)   ifs>>a[i]>>a[i];
  for(unsigned int i=0;i<=NE;++i)  a[i]/=a[NE];
  double ma=1.;
  for(unsigned int i=0;i<NE;++i)  if(a[i]>ma) ma=a[i];

  for(unsigned int i=0;i<NE;++i) {
    u[i]=sqrt(ma)*cos(2*M_PI/NE*i);    v[i]=sqrt(ma)*sin(2*M_PI/NE*i);
  }

  unsigned int z=0;
  double d;

  do {
    d=0.;
    for(unsigned int i=0;i<3;++i) {
      iteration(u,v,a,i,fu,fv);
      d+=fabs(fu)+fabs(fv);
      u[i]-=fu;    v[i]-=fv;
    }
    cout<<z<<"\t"<<d<<endl;
    ++z;
  } while(d>1e-4);
  
  for(unsigned int i=0;i<u.size;++i) cout<<u[i]<<"\t"<<v[i]<<endl;

  cout<<"============"<<endl;
  for(unsigned int i=0;i<u.size;++i) {
    f(u[i],v[i],a,fu,fv);
    cout<<fu<<"\t"<<fv<<endl;
  }

  return 0;
}

