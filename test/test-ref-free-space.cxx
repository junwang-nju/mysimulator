
#include "ref-free-space.h"
#include "var-free-space.h"
#include "fix-free-space.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {
  refFreeSpace FS,FS1;
  varFreeSpace vFS;
  vFS.allocate(3);
  fixFreeSpace<3> vFS1;
  cout<<"Test -- refer to var and fix version of free-space object"<<endl;
  FS.refer(vFS);
  FS1.refer(vFS1);
  cout<<endl;

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

  cout<<"Test -- clear"<<endl;
  FS.clear();

  return 1;
}

