
#include "operation/geometry/distance-calc.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  Vector<double> va,vb,v;
  allocate(va,5);
  allocate(vb,5);
  allocate(v,5);
  copy(va,3);
  copy(vb,5); vb[2]=9;
  FreeSpace  FS;

  COut<<"Test -- distance and displacement for array"<<Endl;
  COut<<Distance(va(),vb(),v(),3,FS,0,1,0,2,1,1)<<Endl;
  COut<<v<<Endl;
  COut<<Endl;

  COut<<"Test -- distance and displacement for vector"<<Endl;
  COut<<Distance(va,vb,v,FS)<<Endl;
  COut<<v<<Endl;
  COut<<Endl;

  return 1;
}

