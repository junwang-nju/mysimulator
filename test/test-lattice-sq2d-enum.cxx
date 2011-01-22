
#include "operation/lattice/bond-library-op.h"
#include "operation/lattice/enumerate.h"
using namespace std;

int main(int argc, char** argv) {
  if(argc<2)  LoadBondLibrary<SquareLattice,2>();
  else        LoadBondLibrary<SquareLattice,2>(argv[1]);
  cout<<IsAvailable(RunBondLibrary<SquareLattice,2>())<<endl;
  unsigned int g=RunBondLibrary<SquareLattice,2>().MaxBonds;
  cout<<RunBondLibrary<SquareLattice,2>().mapper[g-1][6]<<endl;
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
  cout<<LC[0]<<"\t"<<LC[1]<<endl;
  unsigned int Z;
  Z=enumerateSquare2D(8,cout);
  cout<<Z<<endl;
  /*
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
  cout<<FB<<endl;
  Z=enumerateSquare2DPart(12,FB,cout);
  cout<<Z<<endl;
  */
  UnloadBondLibrary<SquareLattice,2>();
  return 0;
}

