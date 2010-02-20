
#include "ref-distance-square-evaluate-direct.h"
#include "var-distance-square-evaluate-direct.h"
#include "fix-distance-square-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- refer to var and fix distance square evaluation"<<endl;
  refDistanceSqEvalDirect<> rDED;
  varDistanceSqEvalDirect vDED;
  vDED.allocate(3);
  rDED.refer(vDED);
  refDistanceSqEvalDirect<fixDistanceSq<3>,refVector> rDED2;
  fixDistanceSqEvalDirect<3> fDED;
  rDED2.refer(fDED);
  cout<<endl;

  cout<<"Test -- calculate distance"<<endl;
  varVector<double> va(3),vb(3);
  va=1;
  vb=3; vb[2]=4.5;
  FreeSpace FS;
  cout<<rDED.Distance(va,vb,0,1,FS)<<endl;
  cout<<rDED.distanceSq()<<endl;
  cout<<rDED.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- calculate distance and displacement"<<endl;
  cout<<rDED.DistanceDisplacement(va,vb,0,1,FS)<<endl;
  cout<<rDED.distanceSq()<<endl;
  cout<<rDED.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable direct evaluator for Distance Square"<<endl;
  rDED2=rDED;
  cout<<rDED2.distanceSq()<<endl;
  cout<<rDED2.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  rDED.clear();
  cout<<rDED.runDistanceSqVec().IsAvailable()<<endl;
  cout<<rDED.runDisplacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

