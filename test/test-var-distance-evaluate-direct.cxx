
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include <iostream>
using namespace std;

int main() {
  varDistanceEvalDirect vDED;

  cout<<"Test -- allocate"<<endl;
  vDED.allocate(3);
  cout<<endl;

  cout<<"Test -- calculate distance"<<endl;
  varVector<double> va(3),vb(3);
  va=1;
  vb=3; vb[2]=4.5;
  varFreeSpace FS;
  vDED.Evaluate(va,vb,0,0,FS);
  cout<<vDED.DistanceSQ()<<endl;
  cout<<vDED.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable direct evaluator for Distance Square"<<endl;
  varDistanceEvalDirect vDED2;
  vDED2.allocate(4);
  vDED2=vDED;
  cout<<vDED2.DistanceSQ()<<endl;
  cout<<vDED2.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  vDED.clear();
  cout<<vDED.DistanceSQVec().IsAvailable()<<endl;
  cout<<vDED.Displacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

