
#include "buffer/distance/simple/allocate.h"
#include "buffer/distance/simple/copy.h"
#include "buffer/distance/pair/allocate.h"
#include "buffer/distance/pair/copy.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  cout<<endl;
  SimpleDistanceBuffer<double> SB,SB1;
  cout<<"Before Allocation: status of displace-vector is:\t";
  cout<<IsValid(SB.DisplaceVector)<<endl;
  allocate(SB,3,5);
  cout<<"After Allocation: status of displace-vector is:\t";
  cout<<IsValid(SB.DisplaceVector)<<endl;
  imprint(SB1,SB);
  cout<<"After Imprint: status of displace-vector is:\t";
  cout<<IsValid(SB1.DisplaceVector)<<endl;
  release(SB1);
  cout<<"After Release: status of displace-vector is:\t";
  cout<<IsValid(SB1.DisplaceVector)<<endl;
  SB.renew();
  cout<<"Renew of Simple buffer do nothing"<<endl;

  cout<<endl;
  imprint(SB1,SB);
  copy(SB1,SB);
  cout<<"After Copy: the status of displace-vector is:\t";
  cout<<IsValid(SB1.DisplaceVector)<<endl;

  cout<<endl;
  PairDistanceBuffer<double> PB,PB1;
  cout<<"Before Allocation: status of displace-vector is:\t";
  cout<<IsValid(PB.DisplaceVector)<<endl;
  allocate(PB,3,6);
  cout<<"After Allocation: status of displace-vector is:\t";
  cout<<IsValid(PB.DisplaceVector)<<endl;
  imprint(PB1,PB);
  cout<<"After Imprint: status of displace-vector is:\t";
  cout<<IsValid(PB1.DisplaceVector)<<endl;
  release(PB1);
  cout<<"After Release: status of displace-vector is:\t";
  cout<<IsValid(PB1.DisplaceVector)<<endl;
  PB.renew();
  cout<<"global status of distance matrix is buffer is:\t";
  cout<<PB.DSqMat.status()<<endl;

  cout<<endl;
  imprint(PB1,PB);
  copy(PB1,PB);
  cout<<"Copy Buffer with Matrix Storage"<<endl;
  return 0;
}

