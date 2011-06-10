
#include "operation/basic/matrix-io.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  Matrix<double> dM;
  allocate(dM,RectangleMatrix,4,5,COrder,NoTranspose);
  COut<<IsAvailable(dM)<<Endl;
  release(dM);
  COut<<IsAvailable(dM)<<Endl;
  allocate(dM,TriangleMatrix,5,COrder,NoTranspose,UpperTriangle,true,false);
  COut<<"========="<<Endl;
  *(dM.ptrOther)=0;
  COut<<"========="<<Endl;
  Matrix<double> dM2;
  refer(dM2,dM);
  long n=5;
  double d=3;
  dcopy_(&n,&d,const_cast<long*>(&lZero),dM2.data,const_cast<long*>(&lOne));
  COut<<dM<<Endl;
  COut<<dM(2,2)<<Endl;

  Matrix<double> dM3;
  allocate(dM3,RectangleMatrix,4,3,COrder,NoTranspose);
  copy(dM3,dM);
  COut<<dM3<<Endl;

  Matrix<double> dM4;
  allocate(dM4,RectangleMatrix,4,3,COrder,NoTranspose);
  ecopy(dM4,dM3);
  COut<<dM4<<Endl;

  return 1;
}

