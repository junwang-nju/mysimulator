
#include <iostream>
#include <cmath>
using namespace std;

static const double x0=0.2;

double F(double x, double T) {
  return -10*exp(-x/0.2)-T*(2*log(x)-x*x/10);
}

double f(double x, double T,double y, double K) {
  return 10/x0*exp(-x/x0)-T*(2/x-2*x/10.)+2*K*(x-y);
}

double df(double x, double T, double y, double K) {
  return -10/(x0*x0)*exp(-x/x0)-T*(-2/x/x-2/10.)+2*K;
}

int main() {

  double x,y,d;
  bool fg;
  double T=1.06937*0.8;
  double K=10.;


  for(y=0;y<10;y+=0.01) {
  x=0.01;
  fg=true;
  do {
    d=f(x,T,y,K)/df(x,T,y,K);
    if(fabs(d)<1e-8)  fg=false;
    x-=d;
  }while(fg);
  cout<<y<<"\t"<<x<<"\t"<<2*K*(y-x)<<endl;
  }
  return 0;
}

