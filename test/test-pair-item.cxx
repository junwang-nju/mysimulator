
#include "data/derived/pair-information-item.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- initialize"<<endl;
  PairItem<double> MSI;
  cout<<endl;

  cout<<"Test -- access"<<endl;
  MSI()=23.4567;
  MSI.status=12;
  cout<<MSI<<endl;
  cout<<endl;

  cout<<"Test -- assign from another Item"<<endl;
  PairItem<double> MSI2;
  copy(MSI2,MSI);
  cout<<MSI2<<endl;
  cout<<endl;

  return 1;
}

