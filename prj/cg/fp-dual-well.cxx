
#include "vector.h"
#include <iostream>
using namespace std;

double potential(const double& x) {
  double d;
  d=x*x;
  return d*d-2*d-0.3*x;
}

double gradient(const double& x) {
  double d;
  d=x*x;
  return 4*(d-1)*x-0.3;
}

int main() {
  int zI=2000;
  Vector<double> prob,oprob;
  allocate(prob,4001);
  allocate(oprob,4001);
  assign(prob,0.);
  prob[-1000+zI]=1000;
  return 0;
}

