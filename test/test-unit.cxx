
#include "operation/unit/name-op.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  loadAminoAcid("/home/jwang/Work/mysimulator/include/data/unit");
  COut<<*getUnitID("AlaNine")<<Endl;
  COut<<*getUnitID("CyS")<<Endl;
  COut<<*getUnitName(12)<<Endl;
  COut<<*getUnitSimpleName("ProLine")<<Endl;
  COut<<*getUnitSimpleName(14)<<Endl;
  COut<<*getUnitCode(5)<<Endl;
  COut<<*getUnitCode("Leucine")<<Endl;
  return 0;
}

