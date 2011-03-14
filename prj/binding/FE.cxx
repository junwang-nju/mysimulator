
#include "data/basic/console-output.h"
#include  <cmath>
using namespace std;

double f1(double d, double r) {
  if(d>r) return -pow(d,-2.);
  else    return (pow(r/d,12.)-2)*pow(r,-2);
}

double f(double d) {
  return -pow(d,-6.);
}

double S(double n, double d) {
  return pow(d/sqrt(n)-1,2.);
}

int main() {
  const unsigned int N1=50;
  const unsigned int N2=50;
  const unsigned int Nm=20;

  const double e1=0;
  const double e2=0;

  double d,d1,d2;
  double w,w1,w2;
  double r,r1,r2;
  double R;

  return 0;
}

