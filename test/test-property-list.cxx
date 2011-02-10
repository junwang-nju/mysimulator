
#include "data/basic/property-list.h"
#include "operation/basic/console-output.h"
#include <iostream>
using namespace std;

int main() {
  PropertyList<double> dPL;
  COut<<IsAvailable(dPL)<<Endl;
  Vector<unsigned int> sz;
  allocate(sz,5);
  COut<<"======"<<Endl;
  copy(sz,3);
  COut<<sz<<Endl;
  allocate(dPL,sz(),sz.size);
  COut<<IsAvailable(dPL)<<Endl;
  //double d;
  //d=2.3;
  //dcopy_(reinterpret_cast<long*>(&(dPL.size)),dPL.data,
  //       const_cast<long*>(&lOne),
  //       const_cast<double*>(&d),const_cast<long*>(&lZero));
  copy(static_cast<Vector<double>&>(dPL),2.3);
  //copy(dPL.data,2.3,dPL.size);
  COut<<dPL<<Endl;
  PropertyList<double> dPL2;
  allocate(sz,4);
  copy(sz,5);
  allocate(dPL2,sz(),sz.size);
  copy(dPL2,dPL);
  COut<<dPL2<<Endl;
  PropertyList<double> dPL3;
  refer(dPL3,dPL2);
  COut<<dPL3<<Endl;
  COut<<"---------------"<<Endl;
  swap(dPL,dPL2);
  COut<<"---------------"<<Endl;
  COut<<dPL2<<Endl;
  COut<<"---------------"<<Endl;
  COut<<dPL3<<Endl;
  COut<<"---------------"<<Endl;
  return 1;
}

