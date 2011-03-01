
#include "operation/pdb/pdb-info-op.h"
using namespace std;

int main() {
  InitAminoAcidNumberAtoms();
  InitNameLibrary();
  InitHeavyAtomProperty();
  InitAminoAcidBonds();
  PDBInfo PI;
  COut<<get(UnitAtomNameLibrary,"ALA H3 ")<<Endl;
  COut<<get(UnitAtomNameLibrary,"ALA H3Z")<<Endl;
  ImportPDBInfo(PI,"/home/jwang/Work/mysimulator/test/2CI2.pdb");
  ImportPDBInfo(PI,"/home/jwang/Work/mysimulator/test/1ARR.pdb");
  return 0;
}

