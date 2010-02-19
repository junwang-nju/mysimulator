
#include "free-space.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {
  FreeSpace FS,FS1;
  FS=FS1;
  cout<<FS.Type<<endl;
  varVector<double> va(3),vb(3),v(3);
  va=5;
  vb=7; vb[2]=9;
  CalcDisplacement(va,vb,v,FS);
  cout<<v<<endl;
  return 1;
}

