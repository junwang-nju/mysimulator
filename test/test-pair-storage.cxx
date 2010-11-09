
#include "data/derived/pair-information.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- Initialize"<<endl;
  PairStorage<double> MS;
  cout<<endl;

  cout<<"Test --Allocate"<<endl;
  allocate(MS,5);
  cout<<endl;

  cout<<"Test -- access the data"<<endl;
  cout<<IsUptodate(MS,1,3)<<endl;
  MS.updateItem(1,3,3.45);
  cout<<IsUptodate(MS,1,3)<<endl;
  MS.refresh();
  cout<<IsUptodate(MS,1,3)<<endl;
  MS.updateItem(1,3,3.45);
  cout<<IsUptodate(MS,1,3)<<endl;
  MS.refresh(1);
  cout<<IsUptodate(MS,1,3)<<endl;
  MS.updateItem(1,3,3.45);
  cout<<IsUptodate(MS,1,3)<<endl;
  MS.refreshItem(1,3);
  cout<<IsUptodate(MS,1,3)<<endl;
  cout<<endl;

  cout<<"Test -- assign from another Matrix Storage"<<endl;
  PairStorage<double> MS2;
  allocate(MS2,4);
  copy(MS2,MS);
  cout<<MS2(1,3).status<<endl;
  cout<<*(MS2.gstatus)<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(MS2);
  cout<<MS2.state<<endl;
  cout<<endl;

  cout<<"Test -- check availability"<<endl;
  cout<<IsAvailable(MS)<<endl;
  cout<<IsAvailable(MS2)<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(MS2,MS);
  cout<<MS2(1,3).status<<endl;
  cout<<*(MS2.gstatus)<<endl;
  cout<<endl;

  return 1;
}

