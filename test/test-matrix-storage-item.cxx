
#include "matrix-storage-item.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- initialize"<<endl;
  MatrixStorageItem<double> MSI;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(MSI);
  cout<<endl;

  cout<<"Test -- access"<<endl;
  MSI()=23.4567;
  *(MSI.status)=12;
  cout<<MSI<<endl;
  cout<<endl;

  cout<<"Test -- assign from another Item"<<endl;
  MatrixStorageItem<double> MSI2;
  allocate(MSI2);
  assign(MSI2,MSI);
  cout<<MSI2<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(MSI2);
  cout<<endl;

  cout<<"Test -availability check"<<endl;
  cout<<IsAvailable(MSI)<<endl;
  cout<<IsAvailable(MSI2)<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(MSI2,MSI);
  cout<<endl;

  return 1;
}

