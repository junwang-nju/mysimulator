
#define _DBL_RADIX    2

#include "vector.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <complex>
#include <fstream>
#include <cfloat>
using namespace std;

typedef complex<double> dcomplex;

void quadratic(const unsigned int n, const Vector<double>& a,
               Vector<dcomplex>& res) {
  double r;
  if(n==2) {
    if(a[1]==0) {
      r=-a[2]/a[0];
      if(r<0) {
        res[1]=dcomplex(0.,sqrt(-r));
        res[2]=dcomplex(0.,-res[1].imag());
      } else {
        res[1]=dcomplex(sqrt(r),0.);
        res[2]=dcomplex(-res[1].real(),0.);
      }
    } else {
      r=1-4*a[0]*a[2]/(a[1]*a[1]);
      double d;
      d=a[1]/(a[0]*2);
      if(r<0) {
        res[1]=dcomplex(-d,d*sqrt(-r));
        res[2]=dcomplex(res[1].real(),-res[1].imag());
      } else {
        res[1]=dcomplex(-d*(1+sqrt(r)),0.);
        res[2]=dcomplex(a[2]/(a[0]*res[1].real()),0.);
      }
    }
  } else if(n==1) {
    res[1]=dcomplex(-a[1]/a[0],0.);
  }
}

double norm(const dcomplex& z) { return z.real()*z.real()+z.imag()*z.imag(); }

double feval(const unsigned int n, const Vector<double>& a,
             const dcomplex& z, dcomplex& fz) {
  double p,q,r,s,t;
  p=-(z.real()+z.real());
  q=norm(z);
  s=0;
  r=a[0];
  for(unsigned int i=1;i<n;++i) {
    t=a[i]-p*r-q*s;
    s=r;
    r=t;
  }
  fz=dcomplex(a[n]+z.real()*r-q*s,z.imag()*r);
  return norm(fz);
}

double startpoint(const unsigned int n, const Vector<double>& a) {
  double r,u,min;
  r=log(fabs(a[n]));
  min=exp((r-log(fabs(a[0])))/n);
  for(unsigned int i=1;i<n;++i)
    if(a[i]!=0) {
      u=exp((r-log(fabs(a[i])))/(n-i));
      if(u<min) min=u;
    }
  return min;
}

double upperbound(const unsigned int n, const Vector<double>& a,
                  const dcomplex& z) {
  double p,q,r,s,t,u,e;
  p=-(z.real()+z.real());
  q=norm(z);
  u=sqrt(q);
  s=0.0;  r=a[0]; e=fabs(r)*(3.5/4.5);
  for(unsigned int i=1;i<n;++i) {
    t=a[i]-p*r-q*s;
    s=r;
    r=t;
    e=u*e+fabs(t);
  }
  t=a[n]+z.real()*r-q*s;
  e=u*e+fabs(t);
  e=(9.0*e-7.0*(fabs(t)+fabs(r)*u)+fabs(z.real())*fabs(r)*2.0)*
    pow(_DBL_RADIX,-DBL_MANT_DIG+1);
  return e*e;
}

void alterdirection(dcomplex& dz, const double& m) {
  double x,y;
  x=(dz.real()*0.6-dz.imag()*0.8)*m;
  y=(dz.real()*0.8+dz.imag()*0.6)*m;
  dz=dcomplex(x,y);
}

int realdeflation(const unsigned int n, Vector<double>& a, const double& x) {
  double r=0;
  for(unsigned int i=0;i<n;++i) a[i]=r=r*x+a[i];
  return n-1;
}

int complexdeflation(const unsigned int& n, Vector<double>& a,
                     const dcomplex& z) {
  double r,u;

  r=-(z.real()+z.real());
  u=norm(z);
  a[1]-=r*a[0];
  for(unsigned int i=2;i<n-1;++i) a[i]-=r*a[i-1]+u*a[i-2];
  return n-2;
}

int newton_real(const unsigned int m, const Vector<double>& coef,
                Vector<dcomplex>& res) {
  unsigned int n=m;
  Vector<double> a,a1;
  allocate(a,n+1);
  allocate(a1,n);
  a=coef;

  int err=0;
  for(;a[n]==0.0;--n) res[n]=dcomplex(0.);

  double u,r,r0,eps;
  double f,f0,ff,f2,fw;
  dcomplex z,z0,dz,fz,fwz,wz,fz0,fz1;
  unsigned int stg,iter;
  
  while(n>2) {
    for(unsigned int i=0;i<n;++i) a1[i]=a[i]*(n-i);
    u=startpoint(n,a);
    z0=dcomplex(0);
    f0=ff=2.0*a[n]*a[n];
    fz0=dcomplex(a[n-1],0);
    z=dcomplex((a[n-1]==0.0?1:-a[n]/a[n-1]),0.);
    z=dcomplex(z.real()*u*0.5/fabs(z.real()),0.);
    dz=z;
    f=feval(n,a,z,fz);
    r0=2.5*u;
    r=sqrt(norm(dz));
    eps=4*n*n*f0*pow(_DBL_RADIX,-DBL_MANT_DIG*2);
    for(stg=1,iter=0;(z+dz!=z)&&(f>eps)&&(iter<50);++iter) {
      u=feval(n-1,a1,z,fz1);
      if(u==0.0)  alterdirection(dz,5.0);
      else {
        dz=dcomplex((fz.real()*fz1.real()+fz.imag()*fz1.imag())/u,
                    (fz.imag()*fz1.real()-fz.real()*fz1.imag())/u);
        fwz=fz0-fz1;
        wz=z0-z;
        f2=norm(fwz)/norm(wz);
        stg=(f2/u>u/f/4)||(f!=ff);
        r=sqrt(norm(dz));
        if(r>r0)  alterdirection(dz,r0/r);
        r0=r*5;
      }
      z0=z;
      f0=f;
      fz0=fz;
iter2:
      z=z0-dz;
      ff=f=feval(n,a,z,fz);
      if(stg) {
        wz=z;
        for(unsigned int i=1,div2=(f>f0);i<=n;++i) {
          if(div2) {
            dz*=dcomplex(0.5);
            wz=z0-dz;
          } else
            wz-=dz;
          fw=feval(n,a,wz,fwz);
          if(fw>=f) break;
          f=fw;
          fz=fwz;
          z=wz;
          if(div2&&(i==2)) {
            alterdirection(dz,0.5);
            z=z0-dz;
            f=feval(n,a,z,fz);
            break;
          }
        }
      } else
        eps=upperbound(n,a,z);
      if((r<sqrt(norm(z))*pow(_DBL_RADIX,-DBL_MANT_DIG/2))&&(f>=f0)) {
        z=z0;
        alterdirection(dz,0.5);
        if(z+dz!=z)  goto iter2;
      }
    }
    if(iter>=50)  err--;
    z0=dcomplex(z.real(),0);
    if(feval(n,a,z0,fz)<=f) {
      res[n]=z0;
      n=realdeflation(n,a,z.real());
    } else {
      res[n]=z;
      res[n-1]=dcomplex(z.real(),-z.imag());
      n=complexdeflation(n,a,z);
    }
  }
  quadratic(n,a,res);
  release(a1);
  release(a);
  return err;
}

int main() {
  Vector<double> a;
  Vector<dcomplex> res;

  ifstream ifs("16.e.f0");
  unsigned int n,m;
  ifs>>n;
  allocate(a,n+1);
  allocate(res,n+1);
  for(unsigned int i=0;i<=n;++i) {
    ifs>>m;
    ifs>>a[n-m];
  }
  for(unsigned int i=1;i<=n;++i)  a[i]/=a[0];
  a[0]=1.;

  newton_real(n,a,res);
  cout<<res<<endl;

  for(unsigned int i=1;i<=n;++i)
    cout<<feval(n,a,res[1],res[0])<<endl;

  return 0;
}


