
#include "data/basic/unique-parameter.h"
#include "operation/basic/console-output.h"
#include <iostream>
using namespace std;

int main() {
  COut<<"Test -- create"<<Endl;
  UniqueParameter up;
  COut<<Endl;

  COut<<"Test -- assign and read"<<Endl;
  copy(up,1.5);
  COut<<up.d<<"\t\t"<<up.ull<<Endl;
  copy(up,1U);
  COut<<up.u<<"\t\t"<<up.ull<<Endl;
  copy(up,-1);
  COut<<up.i<<"\t\t"<<up.ull<<Endl;
  double p=9.6;
  COut<<&p<<Endl;
  copy(up,&p);
  COut<<up.ptr<<"\t\t"<<up.ull<<Endl;
  COut<<Endl;

  COut<<"Test - assign from another unique parameter"<<Endl;
  UniqueParameter up2;
  copy(up2,up);
  COut<<up2.ull<<Endl;
  COut<<Endl;

  COut<<"Test -- read from istream"<<Endl;
  cin>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d<<Endl;
  COut<<"\t"<<up.u<<Endl;
  COut<<"\t"<<up.i<<Endl;
  COut<<"\t"<<up.ptr<<Endl;
  cin>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d<<Endl;
  COut<<"\t"<<up.u<<Endl;
  COut<<"\t"<<up.i<<Endl;
  COut<<"\t"<<up.ptr<<Endl;
  cin>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d<<Endl;
  COut<<"\t"<<up.u<<Endl;
  COut<<"\t"<<up.i<<Endl;
  COut<<"\t"<<up.ptr<<Endl;
  cin>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d<<Endl;
  COut<<"\t"<<up.u<<Endl;
  COut<<"\t"<<up.i<<Endl;
  COut<<"\t"<<up.ptr<<Endl;
  cin>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d<<Endl;
  COut<<"\t"<<up.u<<Endl;
  COut<<"\t"<<up.i<<Endl;
  COut<<"\t"<<up.ptr<<Endl;
  COut<<Endl;

  COut<<"Test -- read method"<<Endl;
  COut<<up.value<double>()<<Endl;
  COut<<Endl;

  return 1;
}

