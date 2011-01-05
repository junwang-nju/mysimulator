
#include "operation/lattice/bond-library-op.h"
using namespace std;

int main(int argc, char** argv) {
  if(argc<2)  myError("please input ROOT directory");
  initLib<SquareLattice,2>(argv[1]);
  cout<<BondLibSquare2D.BondMapper<<endl;
  return 0;
}

