
#include "ref-pair-storage.h"
#include "var-pair-storage.h"
#include "fix-pair-storage.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- init"<<endl;
  refPairStorage<double>::Type rPS;
  cout<<endl;

  cout<<"Test -- refer to various storage of pair information"<<endl;
  varPairStorage<double>::Type vPS(5);
  fixPairStorage<double,5>::Type fPS;
  rPS.refer(vPS);
  rPS.refer(fPS);
  cout<<endl;

  cout<<"Test -- output item"<<endl;
  cout<<rPS(1,2)<<endl;
  cout<<endl;

  cout<<"Test -- number of units as dimension"<<endl;
  cout<<rPS.NumUnits()<<endl;
  cout<<endl;

  cout<<"Test -- read global state"<<endl;
  cout<<rPS.GlobalStatus()<<endl;
  cout<<endl;

  cout<<"test -- test state related to updation"<<endl;
  cout<<rPS.IsUpdated(1,2)<<endl;
  cout<<endl;

  cout<<"Test -- update a certain item"<<endl;
  rPS.Update(1,2,23.45);
  cout<<rPS(1,2)<<endl;
  cout<<rPS.IsUpdated(1,2)<<endl;
  cout<<endl;

  cout<<"Test -- test inc operation for item, line or all"<<endl;
  rPS.Inc(1,2);
  cout<<rPS.IsUpdated(1,2)<<endl;
  rPS.Update(1,2,123.45);
  rPS.Inc(1);
  cout<<rPS.IsUpdated(1,2)<<endl;
  rPS.Update(1,2,12.5);
  rPS.Inc();
  cout<<rPS.IsUpdated(1,2)<<endl;
  cout<<endl;
  return 1;
}

