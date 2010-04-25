
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initiate"<<endl;
  FreeSpace FS;
  cout<<endl;

  cout<<"Test -- assign from another Free Space"<<endl;
  FreeSpace FS2;
  FS2=FS;
  cout<<endl;

  cout<<"Test -- refer another Free Space"<<endl;
  refer(FS2,FS);
  cout<<endl;

  cout<<"Test -- type id"<<endl;
  cout<<FS.TypeID<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(FS2);
  cout<<endl;

  cout<<"Test -- Displacement Calculation"<<endl;
  Vector<double> va,vb,v;
  allocate(va,5);
  allocate(vb,5);
  allocate(v,6);
  assign(va,3);
  assign(vb,5); vb[2]=9;
  DisplacementFunc(va,vb,v,FS);
  cout<<v<<endl;
  cout<<endl;

  return 1;
}

