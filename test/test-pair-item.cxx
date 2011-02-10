
#include "data/derived/pair-information-item.h"
#include "operation/basic/console-output.h"
#include <iostream>
using namespace std;

int main() {

  COut<<"Test -- initialize"<<Endl;
  PairItem<double> MSI;
  COut<<Endl;

  COut<<"Test -- access"<<Endl;
  MSI()=23.4567;
  MSI.status=12;
  COut<<MSI<<Endl;
  COut<<Endl;

  COut<<"Test -- assign from another Item"<<Endl;
  PairItem<double> MSI2;
  copy(MSI2,MSI);
  COut<<MSI2<<Endl;
  COut<<Endl;

  return 1;
}

