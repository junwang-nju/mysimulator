
#include "ref-distance-evaluate-direct.h"
#include "var-distance-evaluate-direct.h"
#include "fix-distance-evaluate-direct.h"
#include "var-free-space.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- refer to var and fix distance square evaluation"<<endl;
  refDistanceEvalDirect rDED;
  varDistanceEvalDirect vDED;
  vDED.allocate(3);
  rDED.refer(vDED);
  refDistanceEvalDirect rDED2;
  fixDistanceEvalDirect<3> fDED;
  rDED2.refer(fDED);
  cout<<endl;

  cout<<"Test -- calculate distance"<<endl;
  varVector<double> va(3),vb(3);
  va=1;
  vb=3; vb[2]=4.5;
  varFreeSpace FS;
  rDED.Evaluate(va,vb,0,1,FS);
  cout<<rDED.DistanceSQ()<<endl;
  cout<<rDED.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable direct evaluator for Distance Square"<<endl;
  rDED2=rDED;
  cout<<rDED2.DistanceSQ()<<endl;
  cout<<rDED2.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  rDED.clear();
  cout<<rDED.DistanceSQVec().IsAvailable()<<endl;
  cout<<rDED.Displacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

