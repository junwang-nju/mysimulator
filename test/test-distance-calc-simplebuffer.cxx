
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  COut<<"Test -- initialize"<<Endl;
  DistanceBufferSimple<double> DED;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(DED,5,8);
  COut<<DED.DisplaceVec.size<<Endl;
  COut<<DED.state<<Endl;
  COut<<Endl;

  COut<<"Test -- evaluate"<<Endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  copy(va,1.);    va[2]=-15.;   va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  FreeSpace FS;
  COut<<Distance(va,vb,0,1,FS,DED)<<Endl;
  COut<<DED.DisplaceVec<<Endl;
  COut<<DED.DistanceSquare()<<Endl;
  COut<<Endl;

  COut<<"Test -- assign from another DistanceEvalDirect"<<Endl;
  DistanceBufferSimple<double> DED2;
  allocate(DED2,4,7);
  copy(DED2,DED);
  COut<<DED2.DisplaceVec<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(DED2);
  COut<<DED2.state<<Endl;
  COut<<Endl;

  COut<<"Test -- refer operation"<<Endl;
  refer(DED2,DED);
  COut<<DED2.DisplaceVec<<Endl;
  COut<<DED2.DistanceSquare()<<Endl;
  COut<<Endl;

  COut<<"Test -- update"<<Endl;
  DED.renew();
  COut<<DED.DisplaceVec<<Endl;
  COut<<DED.DistanceSquare()<<Endl;
  COut<<Endl;

  COut<<"Test -- whether it is Distance Evaluate Method"<<Endl;
  COut<<IsDistanceBuffer(DED2)<<Endl;
  COut<<IsDistanceBuffer(DED.DistanceSquare())<<Endl;
  COut<<Endl;

  return 1;
}

