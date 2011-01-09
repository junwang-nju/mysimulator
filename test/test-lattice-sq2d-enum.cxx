
#include "operation/lattice/chain-op.h"
using namespace std;

int main(int argc, char** argv) {
  if(argc<2)  myError("please input ROOT directory");
  cout<<IsAvailable(RunBondLibrary<SquareLattice,2>())<<endl;
  cout<<RunBondLibrary<SquareLattice,2>().Bond(6)<<endl;
  LatticeChain<SquareLattice,2> LC;
  Vector<unsigned int> BV;
  allocate(BV,11);
  BV[0]=0;
  BV[1]=1;
  BV[2]=0;
  BV[3]=2;
  BV[4]=2;
  BV[5]=0;
  BV[6]=1;
  BV[7]=0;
  BV[8]=1;
  BV[9]=1;
  BV[10]=3;
  SetChain(LC,BV);
  return 0;
}

