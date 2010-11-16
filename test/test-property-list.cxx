
#include "data/basic/property-list.h"
#include <iostream>
using namespace std;

int main() {
  PropertyList<double> dPL;
  cout<<IsAvailable(dPL)<<endl;
  Vector<unsigned int> sz;
  allocate(sz,5);
  cout<<"======"<<endl;
  copy(sz,3);
  cout<<sz<<endl;
  allocate(dPL,sz(),sz.size);
  cout<<IsAvailable(dPL)<<endl;
  //double d;
  //d=2.3;
  //dcopy_(reinterpret_cast<long*>(&(dPL.size)),dPL.data,
  //       const_cast<long*>(&lOne),
  //       const_cast<double*>(&d),const_cast<long*>(&lZero));
  copy(static_cast<Vector<double>&>(dPL),2.3);
  //copy(dPL.data,2.3,dPL.size);
  cout<<dPL<<endl;
  PropertyList<double> dPL2;
  allocate(sz,4);
  copy(sz,5);
  allocate(dPL2,sz(),sz.size);
  copy(dPL2,dPL);
  cout<<dPL2<<endl;
  PropertyList<double> dPL3;
  refer(dPL3,dPL2);
  cout<<dPL3<<endl;
  cout<<"---------------"<<endl;
  swap(dPL,dPL2);
  cout<<"---------------"<<endl;
  cout<<dPL2<<endl;
  cout<<"---------------"<<endl;
  cout<<dPL3<<endl;
  cout<<"---------------"<<endl;
  return 1;
}

