
#include "operation/geometry/distance-calc.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include <iostream>
using namespace std;

int main() {
  Vector<double> va,vb,v;
  allocate(va,5);
  allocate(vb,5);
  allocate(v,5);
  copy(va,3);
  copy(vb,5); vb[2]=9;
  FreeSpace  FS;

  cout<<"Test -- distance and displacement for array"<<endl;
  cout<<Distance(va(),vb(),v(),3,FS,0,1,0,2,1,1)<<endl;
  cout<<v<<endl;
  cout<<endl;

  cout<<"Test -- distance and displacement for vector"<<endl;
  cout<<Distance(va,vb,v,FS)<<endl;
  cout<<v<<endl;
  cout<<endl;

  return 1;
}

