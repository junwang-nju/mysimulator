
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

static const double x0=0.1;

double F(double x, double T) {
  return -10*exp(-x/x0)-T*(2*log(x)-x*x/10);
}

double f(double x, double T) {
  return 10/x0*exp(-x/x0)-T*(2/x-2*x/10.);
}

double df(double x, double T) {
  return -10/(x0*x0)*exp(-x/x0)-T*(-2/x/x-2/10.);
}

int main(int argc, char** argv) {
  cout.precision(20);
  double T=1.48;
  double Th=1.0, Tl=0.8;
  double x,d,x1,x2;
  bool fg;

  do{ 
  T=0.5*(Tl+Th);
  x=0.01;
  fg=true;
  do {
    d=f(x,T)/df(x,T);
    if(fabs(d)<1e-8)  fg=false;
    x-=d;
  }while(fg);
  x1=x;
  x=sqrt(10);
  fg=true;
  do {
    d=f(x,T)/df(x,T);
    if(fabs(d)<1e-8)  fg=false;
    x-=d;
  }while(fg);
  x2=x;
  if(F(x1,T)<F(x2,T)) Tl=T;
  else                Th=T;
  } while(Th-Tl>1e-10);
  T=0.5*(Th+Tl);
  cout<<x0<<"\t"<<T<<"\t";
  cout<<x1<<"\t"<<F(x1,T)<<"\t";
  cout<<x2<<"\t"<<F(x2,T)<<"\t";

  x=(x2-x1)*0.01;
  x1+=x;
  x2-=x;
  do {
    x=(x1+x2)*0.5;
    if(f(x,T)*f(x1,T)>0)  x1=x;
    else                  x2=x;
  } while(x2-x1>1e-8);
  x=(x1+x2)*0.5;
  cout<<x<<"\t"<<F(x,T)<<endl;
  return 0;
}

