
#include "ref-distance-square.h"
#include "var-distance-square.h"
#include "fix-distance-square.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- refer to var ot fix distance-sq functor"<<endl;
  refDistanceSq<> rDS;
  varDistanceSq vDS;
  vDS.allocate(3);
  rDS.refer(vDS);
  refDistanceSq<refVector> rDS2;
  fixDistanceSq<3> fDS;
  rDS2.refer(fDS);
  cout<<endl;

  cout<<"Test -- calc distance and displacement"<<endl;
  FreeSpace FS;
  varVector<double> va(3),vb(3);
  va=3;
  vb=5; vb[2]=9;
  cout<<rDS.Calc(va,vb,FS)<<endl;
  cout<<rDS.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- calc displacement only"<<endl;
  va=5;
  rDS2.CalcDisplacement(vb,va,FS);
  cout<<vDS.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign through another ref distance-square functor"<<endl;
  rDS2=rDS;
  cout<<endl;

  return 1;
}

