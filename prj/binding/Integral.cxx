
#include "data/basic/console-output.h"
#include <cmath>
using namespace std;

long double f(long double x) {
  return -powl(x,-2.);
}

long double g(long double x) {
  return expl(-f(x));
}

long double gg(long double x) {
  return f(x)*expl(-f(x));
}

int main() {
  long double sG,sGG;
  const long double delta=0.001;
  const double x0=0.35;
  long double x=x0;
  sG=sGG=0.;
  printf("%20.16Lf\t\t%20.16Lf\t\t%20.16Lf\n",x,sG*delta,sGG*delta);
  sG=g(x)*0.5;
  sGG=gg(x)*0.5;
  x+=delta;
  for(;x<1.5+delta*0.5;x+=delta) {
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
    if(x>0.35-delta*0.5)
      printf("%20.16Lf\t\t%20.16Lf\t\t%20.16Lf\n",x,sG*delta,sGG*delta);
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
  }
  for(;x<100+delta*0.5;x+=delta) {
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
    printf("%20.16Lf\t\t%20.16Lf\t\t%20.16Lf\n",x,sG*delta,sGG*delta);
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
  }
  return 0;
}

