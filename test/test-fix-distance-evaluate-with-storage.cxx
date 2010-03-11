
#include "fix-distance-evaluate-with-storage.h"
#include "var-free-space.h"
#include <iostream>
using namespace std;

int main() {
  fixDistanceEvalWStorage<3,4> fDEWS;

  cout<<"Test -- calculate distance"<<endl;
  fixVector<double,3> va,vb;
  va=1;
  vb=3; vb[2]=4.5;
  varFreeSpace FS;
  fDEWS.Evaluate(va,vb,0,1,FS);
  cout<<fDEWS.DistanceSQ()<<endl;
  cout<<fDEWS.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable direct evaluator for Distance Square"<<endl;
  fixDistanceEvalWStorage<3,4> fDEWS2;
  fDEWS2=fDEWS;
  cout<<fDEWS2.DistanceSQ()<<endl;
  cout<<fDEWS2.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  fDEWS.clear();
  cout<<fDEWS.DistanceSQVec().IsAvailable()<<endl;
  cout<<fDEWS.Displacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

