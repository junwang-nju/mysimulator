
#include "operation/geometry/distance-calc-pairbuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  COut<<"Test -- initialize"<<Endl;
  DistanceBufferPairStorage<double> DEW;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(DEW,5,3);
  COut<<DEW.DisplaceVec.size<<Endl;
  COut<<DEW.DsqMat.property[MatrixDimension]<<Endl;
  COut<<DEW.state<<Endl;
  COut<<Endl;

  COut<<"Test -- evaluate"<<Endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  copy(va,1.);    va[2]=-15.; va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  FreeSpace FS;
  COut<<Distance(va,vb,0,1,FS,DEW)<<Endl;
  COut<<DEW.DisplaceVec<<Endl;
  COut<<DEW.DistanceSquare()<<Endl;
  COut<<Endl;

  COut<<"Test -- assign from another DistanceEavl With Storage"<<Endl;
  DistanceBufferPairStorage<double> DEW2;
  allocate(DEW2,4,5);
  copy(DEW2,DEW);
  COut<<DEW2.DisplaceVec<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(DEW2);
  COut<<DEW2.state<<Endl;
  COut<<Endl;
  COut<<Endl;

  COut<<"Test -- refer operation"<<Endl;
  refer(DEW2,DEW);
  COut<<DEW2.DisplaceVec<<Endl;
  COut<<DEW2.DistanceSquare()<<Endl;
  COut<<Endl;

  COut<<"Test -- update"<<Endl;
  DEW.renew();
  COut<<DEW.DisplaceVec<<Endl;
  COut<<DEW.DistanceSquare()<<Endl;
  COut<<Endl;

  COut<<"Test -- whether it is Distance Evaluate Method"<<Endl;
  COut<<IsDistanceBuffer(DEW2)<<Endl;
  COut<<IsDistanceBuffer(DEW.DistanceSquare())<<Endl;
  COut<<Endl;

  return 1;
}

