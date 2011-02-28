
#include "operation/pdb/pdb-info-op.h"
using namespace std;

int main() {
  InitAminoAcidNumberAtoms();
  //InitHeavyAtomProperty();
  //InitAminoAcidBonds();
  PDBInfo PI;
  ImportPDBInfo(PI,"/home/jwang/Work/mysimulator/test/2CI2.pdb");
  ImportPDBInfo(PI,"/home/jwang/Work/mysimulator/test/1ARR.pdb");
  return 0;
}

