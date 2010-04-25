
#include "distance-displacement-calc.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  Vector<double> va,vb,v;
  double d;
  allocate(va,5);
  allocate(vb,5);
  allocate(v,5);
  assign(va,3);
  assign(vb,5); vb[2]=9;
  FreeSpace  FS;

  cout<<"Test -- distance and displacement for array"<<endl;
  DistanceDisplacementFunc(va(),vb(),3,v(),d,FS,0,1,0,2,1,1);
  cout<<v<<endl;
  cout<<d<<endl;
  cout<<endl;

  cout<<"Test -- distance and displacement for vector"<<endl;
  DistanceDisplacementFunc(va,vb,v,d,FS);
  cout<<v<<endl;
  cout<<d<<endl;
  cout<<endl;

  return 1;
}

