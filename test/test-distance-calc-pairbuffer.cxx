
#include "operation/geometry/distance-calc-pairbuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  DistanceBufferPairStorage<double> DEW;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(DEW,5,3);
  cout<<DEW.DisplaceVec.size<<endl;
  cout<<DEW.DsqMat.property[MatrixDimension]<<endl;
  cout<<DEW.state<<endl;
  cout<<endl;

  cout<<"Test -- evaluate"<<endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  copy(va,1.);    va[2]=-15.; va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  FreeSpace FS;
  cout<<Distance(va,vb,0,1,FS,DEW);
  cout<<DEW.DisplaceVec<<endl;
  cout<<DEW.DistanceSquare()<<endl;
  cout<<endl;

  cout<<"Test -- assign from another DistanceEavl With Storage"<<endl;
  DistanceBufferPairStorage<double> DEW2;
  allocate(DEW2,4,5);
  copy(DEW2,DEW);
  cout<<DEW2.DisplaceVec<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(DEW2);
  cout<<DEW2.state<<endl;
  cout<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(DEW2,DEW);
  cout<<DEW2.DisplaceVec<<endl;
  cout<<DEW2.DistanceSquare()<<endl;
  cout<<endl;

  cout<<"Test -- update"<<endl;
  DEW.renew();
  cout<<DEW.DisplaceVec<<endl;
  cout<<DEW.DistanceSquare()<<endl;
  cout<<endl;

  cout<<"Test -- whether it is Distance Evaluate Method"<<endl;
  cout<<IsDistanceBuffer(DEW2)<<endl;
  cout<<IsDistanceBuffer(DEW.DistanceSquare())<<endl;
  cout<<endl;

  return 1;
}

