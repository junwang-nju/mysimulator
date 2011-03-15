
#include "data/basic/console-output.h"
#include <cmath>
using namespace std;

long double f(long double x) {
  return -powl(x,-2.);
}

long double g(long double x) {
  return expl(f(x));
}

long double gg(long double x) {
  return f(x)*expl(f(x));
}

int main() {
  long double sG,sGG;
  const long double delta=0.001;
  long double x=delta;
  sG=sGG=0.;
  for(;x<0.5+delta*0.5;x+=delta) {
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
  }
  for(;x<50+delta*0.5;x+=delta) {
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
    printf("%20.16Lf\t\t%20.16Lf\t\t%20.16Lf\n",x,sG*delta,sGG*delta);
    sG+=0.5*g(x);
    sGG+=0.5*gg(x);
  }
  return 0;
}

