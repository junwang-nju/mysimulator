
#include "fix-free-space.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {
  fixFreeSpace<3> FS,FS1;
  cout<<"Test -- assign with another free-space geometry"<<endl;
  FS=FS1;
  cout<<endl;

  cout<<"Test -- type id of geometry"<<endl;
  cout<<FS.TypeID<<endl;
  cout<<endl;

  cout<<"Test -- func to calculate displacement"<<endl;
  varVector<double> va(3),vb(3),v(3);
  va=5;
  vb=7; vb[2]=9;
  DisplacementFunc(va,vb,v,FS);
  cout<<v<<endl;
  cout<<endl;
  return 1;
}

