
#include "operation/pdb/pdb-info-op.h"
using namespace std;

int main() {
  PDBInfo PI;
  ImportPDBInfo(PI,"/home/jwang/Work/mysimulator/test/2CI2.pdb");
  return 0;
}

