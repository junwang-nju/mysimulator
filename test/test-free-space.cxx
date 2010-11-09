
#include "data/geometry/free-space.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initiate"<<endl;
  FreeSpace FS;
  cout<<endl;

  cout<<"Test -- assign from another Free Space"<<endl;
  FreeSpace FS2;
  copy(FS2,FS);
  cout<<endl;

  cout<<"Test -- refer another Free Space"<<endl;
  refer(FS2,FS);
  cout<<endl;

  cout<<"Test -- type id"<<endl;
  cout<<FS.Name<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(FS2);
  cout<<endl;

  cout<<"Test -- Displacement Calculation"<<endl;
  Vector<double> va,vb,v;
  allocate(va,5);
  allocate(vb,5);
  allocate(v,6);
  copy(va,3);
  copy(vb,5); vb[2]=9;
  Displacement(va,vb,v,FS);
  cout<<v<<endl;
  cout<<endl;

  cout<<"Test -- check whether it is a geometry"<<endl;
  cout<<IsGeometry(FS)<<endl;
  cout<<IsGeometry(va)<<endl;
  cout<<endl;

  return 1;
}

