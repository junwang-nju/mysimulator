
#include "var-distance-square.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  varDistanceSq vDS;
  cout<<"Test -- allocate"<<endl;
  vDS.allocate(3);
  cout<<endl;

  cout<<"Test -- calc distance and displacement"<<endl;
  FreeSpace FS;
  varVector<double> va(3),vb(3);
  va=3;
  vb=5; vb[2]=9;
  cout<<vDS.Calc(va,vb,FS)<<endl;
  cout<<vDS.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- calc displacement only"<<endl;
  va=5;
  vDS.CalcDisplacement(vb,va,FS);
  cout<<vDS.displacement()<<endl;
  cout<<endl;
  return 1;
}

