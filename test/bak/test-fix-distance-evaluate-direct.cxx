
#include "fix-distance-evaluate-direct.h"
#include "var-free-space.h"
#include <iostream>
using namespace std;

int main() {
  fixDistanceEvalDirect<3> fDED;

  cout<<"Test -- calculate distance"<<endl;
  fixVector<double,3> va,vb;
  va=1;
  vb=3; vb[2]=4.5;
  varFreeSpace FS;
  fDED.Evaluate(va,vb,0,1,FS);
  cout<<fDED.DistanceSQ()<<endl;
  cout<<fDED.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable direct evaluator for Distance Square"<<endl;
  fixDistanceEvalDirect<4> fDED2;
  fDED2=fDED;
  cout<<fDED2.DistanceSQ()<<endl;
  cout<<fDED2.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  fDED.clear();
  cout<<fDED.DistanceSQVec().IsAvailable()<<endl;
  cout<<fDED.Displacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

