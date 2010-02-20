
#include "fix-distance-square.h"
#include "free-space.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {
  fixDistanceSq<3> fDS;
  cout<<"Test -- calc distance and displacement"<<endl;
  FreeSpace FS;
  varVector<double> va(3),vb(3);
  va=3;
  vb=5; vb[2]=9;
  cout<<fDS.Calc(va,vb,FS)<<endl;
  cout<<fDS.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- calc displacement only"<<endl;
  va=5;
  fDS.CalcDisplacement(vb,va,FS);
  cout<<fDS.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign from another functor"<<endl;
  fixDistanceSq<4> fDS2;
  fDS2=fDS;
  cout<<fDS2.displacement()<<endl;
  cout<<endl;
  return 1;
}

