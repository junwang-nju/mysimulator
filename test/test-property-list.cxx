
#include "property-list.h"
#include <iostream>
using namespace std;

int main() {
  PropertyList<double> dPL;
  cout<<IsAvailable(dPL)<<endl;
  Vector<unsigned int> sz;
  allocate(sz,5);
  assign(sz,3);
  allocate(dPL,sz(),sz.size);
  cout<<IsAvailable(dPL)<<endl;
  assign(dPL.data,2.3,dPL.size);
  cout<<dPL<<endl;
  PropertyList<double> dPL2;
  allocate(sz,4);
  assign(sz,5);
  allocate(dPL2,sz(),sz.size);
  assign(dPL2,dPL);
  cout<<dPL2<<endl;
  PropertyList<double> dPL3;
  refer(dPL3,dPL2);
  cout<<dPL3<<endl;
  swap(dPL,dPL2);
  cout<<dPL2<<endl;
  cout<<dPL3<<endl;
  return 1;
}

