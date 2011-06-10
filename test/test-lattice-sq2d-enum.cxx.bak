
#include "operation/lattice/bond-library-op.h"
#include "operation/lattice/enumerate.h"
#include "data/basic/console-output.h"
#include "data/basic/null-output.h"
using namespace std;

int main(int argc, char** argv) {
  if(argc<2)  LoadBondLibrary<SquareLattice,2>();
  else        LoadBondLibrary<SquareLattice,2>(argv[1]);
  COut<<IsAvailable(RunBondLibrary<SquareLattice,2>())<<Endl;
  unsigned int g=RunBondLibrary<SquareLattice,2>().MaxBonds;
  COut<<RunBondLibrary<SquareLattice,2>().mapper[g-1][6]<<Endl;
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
  COut<<LC[0]<<"\t"<<LC[1]<<Endl;
  unsigned int Z;
  Z=enumerateSquare2D(8,COut);
  COut<<Z<<Endl;

  PropertyList<unsigned int> FB;
  Vector<unsigned int> sz;
  allocate(sz,5);
  copy(sz,2);
  allocate(FB,sz);
  FB[0][0]=3;   FB[0][1]=1;
  FB[1][0]=5;   FB[1][1]=1;
  FB[2][0]=7;   FB[2][1]=1;
  FB[3][0]=9;   FB[3][1]=1;
  FB[4][0]=10;  FB[4][1]=1;
  COut<<FB<<Endl;
  Z=enumerateSquare2DFixBond(12,FB,COut);
  COut<<Z<<Endl;

  PropertyList<int> FN;
  allocate(sz,6);
  copy(sz,3);
  allocate(FN,sz);
  FN[0][0]=3;
  FN[0][1]=2;   FN[0][2]=1;
  FN[1][0]=6;
  FN[1][1]=3;   FN[1][2]=1;
  FN[2][0]=8;
  FN[2][1]=2;   FN[2][2]=2;
  FN[3][0]=12;
  FN[3][1]=0;   FN[3][2]=4;
  FN[4][0]=16;
  FN[4][1]=2;   FN[4][2]=4;
  FN[5][0]=24;
  FN[5][1]=-1;  FN[5][2]=3;
  NullOutput NO;
  COut<<enumerateSquare2DFixedNode(27,FN,NO)<<Endl;

  UnloadBondLibrary<SquareLattice,2>();
  return 0;
}

