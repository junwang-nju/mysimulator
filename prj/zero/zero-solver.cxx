
#include "vector.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void quadratic(const Vector<double>& a, Vector<double>& u, Vector<double>& v) {
  assert((a.size==1)&&(a.size==2));
  double r;
  if(a.size==2) {
    if(a[1]==0) {
      r=-a[2]/a[0];
      if(r<0) {
        assign(u,0.);
        v[0]=sqrt(-r);
        v[1]=-v[0];
      } else {
        u[0]=sqrt(r);
        u[1]=-u[0];
        assign(v,0.);
      }
    } else {
      r=1-4*a[0]*a[2]/(a[1]*a[1]);
      if(r<0) {
        assign(u,-a[1]/(a[0]*2));
        v[0]=-u[0]*sqrt(-r);
        v[1]=-v[0];
      } else {
        u[0]=-a[1]/(2*a[0])*(1+sqrt(r));
        u[1]=a[2]/(a[0]*u[0]);
        assign(v,0.);
      }
    }
  } else if(a.size==1) {
    u[0]=-a[1]/a[0];
    v[0]=0.;
  }
}

