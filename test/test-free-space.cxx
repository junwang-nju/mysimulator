
#include "data/geometry/free-space.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  COut<<"Test -- initiate"<<Endl;
  FreeSpace FS;
  COut<<Endl;

  COut<<"Test -- assign from another Free Space"<<Endl;
  FreeSpace FS2;
  copy(FS2,FS);
  COut<<Endl;

  COut<<"Test -- refer another Free Space"<<Endl;
  refer(FS2,FS);
  COut<<Endl;

  COut<<"Test -- type id"<<Endl;
  COut<<FS.Name<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(FS2);
  COut<<Endl;

  COut<<"Test -- Displacement Calculation"<<Endl;
  Vector<double> va,vb,v;
  allocate(va,5);
  allocate(vb,5);
  allocate(v,6);
  copy(va,3);
  copy(vb,5); vb[2]=9;
  Displacement(va,vb,v,FS);
  COut<<v<<Endl;
  COut<<Endl;

  COut<<"Test -- check whether it is a geometry"<<Endl;
  COut<<IsGeometry(FS)<<Endl;
  COut<<IsGeometry(va)<<Endl;
  COut<<Endl;

  return 1;
}

