
#include "fix-distance-square-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  fixDistanceSqEvalDirect<3> fDED;

  cout<<"Test -- calculate distance"<<endl;
  fixVector<double,3> va,vb;
  va=1;
  vb=3; vb[2]=4.5;
  FreeSpace FS;
  cout<<fDED.Distance(va,vb,0,1,FS)<<endl;
  cout<<fDED.distanceSq()<<endl;
  cout<<fDED.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- calculate distance and displacement"<<endl;
  cout<<fDED.DistanceDisplacement(va,vb,0,1,FS)<<endl;
  cout<<fDED.distanceSq()<<endl;
  cout<<fDED.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable direct evaluator for Distance Square"<<endl;
  fixDistanceSqEvalDirect<4> fDED2;
  fDED2=fDED;
  cout<<fDED2.distanceSq()<<endl;
  cout<<fDED2.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  fDED.clear();
  cout<<fDED.runDistanceSqVec().IsAvailable()<<endl;
  cout<<fDED.runDisplacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

