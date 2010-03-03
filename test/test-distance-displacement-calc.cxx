
#include "distance-displacement-calc.h"
#include "var-free-space.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {
  varVector<double> va(3),vb(3),v(3);
  double d;
  varFreeSpace vFS;
  va=3;
  vb=5; vb[2]=9;
  DistanceDisplacementFunc(va,vb,v,d,vFS);
  cout<<d<<endl;
  cout<<v<<endl;
  cout<<endl;
}

