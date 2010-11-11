
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  DistanceBufferSimple<double> DED;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(DED,5,8);
  cout<<DED.DisplaceVec.size<<endl;
  cout<<DED.state<<endl;
  cout<<endl;

  cout<<"Test -- evaluate"<<endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  copy(va,1.);    va[2]=-15.;   va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  FreeSpace FS;
  cout<<Distance(va,vb,0,1,FS,DED)<<endl;
  cout<<DED.DisplaceVec<<endl;
  cout<<DED.DistanceSquare()<<endl;
  cout<<endl;

  cout<<"Test -- assign from another DistanceEvalDirect"<<endl;
  DistanceBufferSimple<double> DED2;
  allocate(DED2,4,7);
  copy(DED2,DED);
  cout<<DED2.DisplaceVec<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(DED2);
  cout<<DED2.state<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(DED2,DED);
  cout<<DED2.DisplaceVec<<endl;
  cout<<DED2.DistanceSquare()<<endl;
  cout<<endl;

  cout<<"Test -- update"<<endl;
  DED.renew();
  cout<<DED.DisplaceVec<<endl;
  cout<<DED.DistanceSquare()<<endl;
  cout<<endl;

  cout<<"Test -- whether it is Distance Evaluate Method"<<endl;
  cout<<IsDistanceBuffer(DED2)<<endl;
  cout<<IsDistanceBuffer(DED.DistanceSquare())<<endl;
  cout<<endl;

  return 1;
}

