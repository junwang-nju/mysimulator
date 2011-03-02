
#include "operation/pdb/pdb-info-op.h"
#include "operation/pdb/pdb2contact.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {
  PDBInfo PI;
  ImportPDBInfo(PI,"/home/jwang/Work/mysimulator/test/2CI2.pdb");

  ContactCalcMode<UsingHeavyAtoms> M;
  allocate(M);
  M.ModelID()=0;
  M.CutoffDistance()=5.0;
  ContactMap CM;
  PdbInfo2ContactMap(PI,CM,M);
  COut<<CM.size<<Endl;
  return 0;
}

