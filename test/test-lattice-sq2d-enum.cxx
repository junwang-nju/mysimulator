
#include "operation/lattice/bond-library-op.h"
#include "operation/lattice/enumerate.h"
using namespace std;

int main(int argc, char** argv) {
  if(argc<2)  LoadBondLibrary<SquareLattice,2>();
  else        LoadBondLibrary<SquareLattice,2>(argv[1]);
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
  for(unsigned int i=0;i<LC.size;++i)  cout<<static_cast<int>(LC[i])<<"\t";
  cout<<endl;
  enumerate<SquareLattice,2>(20,cout);
  UnloadBondLibrary<SquareLattice,2>();
  return 0;
}

