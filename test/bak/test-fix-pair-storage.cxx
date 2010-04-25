
#include "fix-pair-storage.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- init"<<endl;
  fixPairStorage<double,5> vPS;
  cout<<endl;

  cout<<"Test -- output item"<<endl;
  cout<<vPS(1,2)<<endl;
  cout<<endl;

  cout<<"Test -- number of units as dimension"<<endl;
  cout<<vPS.NumUnits()<<endl;
  cout<<endl;

  cout<<"Test -- read global state"<<endl;
  cout<<vPS.GlobalStatus()<<endl;
  cout<<endl;

  cout<<"test -- test state related to updation"<<endl;
  cout<<vPS.IsUpdated(1,2)<<endl;
  cout<<endl;

  cout<<"Test -- update a certain item"<<endl;
  vPS.Update(1,2,23.45);
  cout<<vPS(1,2)<<endl;
  cout<<vPS.IsUpdated(1,2)<<endl;
  cout<<endl;

  cout<<"Test -- test inc operation for item, line or all"<<endl;
  vPS.Inc(1,2);
  cout<<vPS.IsUpdated(1,2)<<endl;
  vPS.Update(1,2,123.45);
  vPS.Inc(1);
  cout<<vPS.IsUpdated(1,2)<<endl;
  vPS.Update(1,2,12.5);
  vPS.Inc();
  cout<<vPS.IsUpdated(1,2)<<endl;
  cout<<endl;
  return 1;
}

