
#include "var-distance-evaluate-with-storage.h"
#include "var-free-space.h"
#include <iostream>
using namespace std;

int main() {
  varDistanceEvalWStorage vDEWS;
  
  cout<<"Test -- allocate"<<endl;
  vDEWS.allocate(3,4);
  cout<<endl;

  cout<<"Test -- calculate distance"<<endl;
  varVector<double> va(3),vb(3);
  va=1.;
  vb=3;   vb[2]=4.5;
  varFreeSpace  FS;
  vDEWS.Evaluate(va,vb,1,2,FS);
  cout<<vDEWS.DistanceSQ()<<endl;
  cout<<vDEWS.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another variable evaluator with storage for Distance Square"<<endl;
  varDistanceEvalWStorage vDEWS2(3,4);
  vDEWS2=vDEWS;
  cout<<vDEWS2.DistanceSQ()<<endl;
  cout<<vDEWS2.Displacement()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  vDEWS.clear();
  cout<<vDEWS.DistanceSQVec().IsAvailable()<<endl;
  cout<<vDEWS.Displacement().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

