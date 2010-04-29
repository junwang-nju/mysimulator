
#include "distance-evaluate-with-storage.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  DistanceEvalWStorage DEW;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(DEW,5,3);
  cout<<DEW.displacementvec.size<<endl;
  cout<<DEW.distsqmat.data.property[MatrixDimension]<<endl;
  cout<<DEW.state<<endl;
  cout<<endl;

  cout<<"Test -- evaluate"<<endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  assign(va,1.);    va[2]=-15.; va[3]=87.9;
  assign(vb,57.63); vb[3]=123.45;
  FreeSpace FS;
  Evaluate(DEW,va,vb,0,1,FS);
  cout<<DEW.displacementvec<<endl;
  cout<<DEW()<<endl;
  cout<<endl;

  cout<<"Test -- assign from another DistanceEavl With Storage"<<endl;
  DistanceEvalWStorage DEW2;
  allocate(DEW2,4,5);
  assign(DEW2,DEW);
  cout<<DEW2.displacementvec<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(DEW2);
  cout<<DEW2.state<<endl;
  cout<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(DEW2,DEW);
  cout<<DEW2.displacementvec<<endl;
  cout<<DEW2()<<endl;
  cout<<endl;

  cout<<"Test -- update"<<endl;
  update(DEW);
  cout<<DEW.displacementvec<<endl;
  cout<<DEW()<<endl;
  cout<<endl;

  cout<<"Test -- whether it is Distance Evaluate Method"<<endl;
  cout<<IsDistanceEvalMethod(DEW2)<<endl;
  cout<<IsDistanceEvalMethod(DEW())<<endl;
  cout<<endl;

  return 1;
}

