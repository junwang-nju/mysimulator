
#include "operation/pdb/pdb-info-op.h"
#include "data/basic/console-output.h"
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
  COut<<PI.UnitAtomID[2].size<<Endl;
  ImportPDBInfo(PI,"/home/jwang/Work/mysimulator/test/1ARR.pdb");
  COut<<PI.UnitAtomID[3].size<<Endl;
  return 0;
}

