
#include "var-distance-square-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  varDistanceSqEvalDirect vDED;

  cout<<"Test -- allocate"<<endl;
  vDED.allocate(3);
  cout<<endl;

  cout<<"Test -- calculate distance"<<endl;
  varVector<double> va(3),vb(3);
  va=1;
  vb=3; vb[2]=4.5;
  FreeSpace FS;
  cout<<vDED.Distance(va,vb,0,1,FS)<<endl;
  cout<<vDED.distanceSq()<<endl;
  cout<<vDED.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- calculate distance and displacement"<<endl;
  cout<<vDED.DistanceDisplacement(va,vb,0,1,FS)<<endl;
  cout<<vDED.distanceSq()<<endl;
  cout<<vDED.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable direct evaluator for Distance Square"<<endl;
  varDistanceSqEvalDirect vDED2;
  vDED2.allocate(4);
  vDED2=vDED;
  cout<<vDED2.distanceSq()<<endl;
  cout<<vDED2.displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  vDED.clear();
  cout<<vDED.runDistanceSqVec().IsAvailable()<<endl;
  cout<<vDED.runDisplacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

