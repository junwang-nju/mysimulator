
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  DistanceEvalDirect DED;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(DED,5,8);
  cout<<DED.displacementvec.size<<endl;
  cout<<DED.state<<endl;
  cout<<endl;

  cout<<"Test -- evaluate"<<endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  copy(va,1.);    va[2]=-15.;   va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  FreeSpace FS;
  Evaluate(DED,va,vb,0,1,FS);
  cout<<DED.displacementvec<<endl;
  cout<<DED()<<endl;
  cout<<endl;

  cout<<"Test -- assign from another DistanceEvalDirect"<<endl;
  DistanceEvalDirect DED2;
  allocate(DED2,4,7);
  assign(DED2,DED);
  cout<<DED2.displacementvec<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(DED2);
  cout<<DED2.state<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(DED2,DED);
  cout<<DED2.displacementvec<<endl;
  cout<<DED2()<<endl;
  cout<<endl;

  cout<<"Test -- update"<<endl;
  update(DED);
  cout<<DED.displacementvec<<endl;
  cout<<DED()<<endl;
  cout<<endl;

  cout<<"Test -- whether it is Distance Evaluate Method"<<endl;
  cout<<IsDistanceEvalMethod(DED2)<<endl;
  cout<<IsDistanceEvalMethod(DED())<<endl;
  cout<<endl;

  return 1;
}

