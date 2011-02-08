
#include "data/derived/pair-information.h"
#include "operation/basic/console-output.h"
#include <iostream>
using namespace std;

int main() {

  COut<<"Test -- Initialize"<<Endl;
  PairStorage<double> MS;
  COut<<Endl;

  COut<<"Test --Allocate"<<Endl;
  allocate(MS,5);
  COut<<Endl;

  COut<<"Test -- access the data"<<Endl;
  COut<<IsUptodate(MS,1,3)<<Endl;
  MS.updateItem(1,3,3.45);
  COut<<IsUptodate(MS,1,3)<<Endl;
  MS.refresh();
  COut<<IsUptodate(MS,1,3)<<Endl;
  MS.updateItem(1,3,3.45);
  COut<<IsUptodate(MS,1,3)<<Endl;
  MS.refresh(1);
  COut<<IsUptodate(MS,1,3)<<Endl;
  MS.updateItem(1,3,3.45);
  COut<<IsUptodate(MS,1,3)<<Endl;
  MS.refreshItem(1,3);
  COut<<IsUptodate(MS,1,3)<<Endl;
  COut<<Endl;

  COut<<"Test -- assign from another Matrix Storage"<<Endl;
  PairStorage<double> MS2,MS3;
  allocate(MS2,4);
  copy(MS2,MS);
  COut<<MS2(1,3).status<<Endl;
  allocate(MS3,5);
  ecopy(MS3,MS);
  COut<<MS3(1,3).status<<Endl;
  COut<<*(MS2.gstatus)<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(MS2);
  COut<<MS2.state<<Endl;
  COut<<Endl;

  COut<<"Test -- check availability"<<Endl;
  COut<<IsAvailable(MS)<<Endl;
  COut<<IsAvailable(MS2)<<Endl;
  COut<<Endl;

  COut<<"Test -- refer operation"<<Endl;
  refer(MS2,MS);
  COut<<MS2(1,3).status<<Endl;
  COut<<*(MS2.gstatus)<<Endl;
  COut<<Endl;

  return 1;
}

