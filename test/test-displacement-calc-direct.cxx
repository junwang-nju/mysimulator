
#include "operation/geometry/displacement-calc-direct.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  Vector<double> Va,Vb,Vc;
  allocate(Va,10);
  allocate(Vb,10);
  allocate(Vc,10);
  copy(Va,3);
  for(int i=0;i<10;++i) Vb[i]=i;
  Displacement(Va,Vb,Vc);
  COut<<Va<<Endl;
  COut<<Vb<<Endl;
  COut<<Vc<<Endl;

  Vector<int> Vi;
  allocate(Vi,10);
  copy(Vi,3);
  Displacement(Vi,Vb,Vc);
  COut<<Vc<<Endl;

  Displacement(Vi.data,Vb.data,Vc.data,4,1,1,1,2,2,2);
  COut<<Vi<<Endl;
  COut<<Vb<<Endl;
  COut<<Vc<<Endl;

  return 0;
}

