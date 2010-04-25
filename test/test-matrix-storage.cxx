
#include "matrix-storage.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- Initialize"<<endl;
  MatrixStorage<double> MS;
  cout<<endl;

  cout<<"Test --Allocate"<<endl;
  allocate(MS,5);
  cout<<endl;

  cout<<"Test -- access the data"<<endl;
  cout<<IsUpToDate(MS,1,3)<<endl;
  update(MS,1,3,3.45);
  cout<<IsUpToDate(MS,1,3)<<endl;
  refresh(MS);
  cout<<IsUpToDate(MS,1,3)<<endl;
  update(MS,1,3,3.45);
  cout<<IsUpToDate(MS,1,3)<<endl;
  refresh(MS,1);
  cout<<IsUpToDate(MS,1,3)<<endl;
  update(MS,1,3,3.45);
  cout<<IsUpToDate(MS,1,3)<<endl;
  refresh(MS,1,3);
  cout<<IsUpToDate(MS,1,3)<<endl;
  cout<<endl;

  cout<<"Test -- assign from another Matrix Storage"<<endl;
  MatrixStorage<double> MS2;
  allocate(MS2,4);
  assign(MS2,MS);
  cout<<MS2(1,3)()<<endl;
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
  cout<<MS2(1,3)()<<endl;
  cout<<*(MS2.gstatus)<<endl;
  cout<<endl;

  return 1;
}

