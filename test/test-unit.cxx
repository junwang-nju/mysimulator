
#include "operation/unit/name-op.h"
#include "operation/unit/composition-op.h"
#include "operation/unit/connectivity-op.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  loadAminoAcidName("/home/jwang/Code/mysimulator/include/data/unit");
  COut<<*getUnitID("AlaNine")<<Endl;
  COut<<*getUnitID("CyS")<<Endl;
  COut<<*getUnitName(12)<<Endl;
  COut<<*getUnitSimpleName("ProLine")<<Endl;
  COut<<*getUnitSimpleName(14)<<Endl;
  COut<<*getUnitCode(5)<<Endl;
  COut<<*getUnitCode("Leucine")<<Endl;

  loadAminoAcidComposition("/home/jwang/Code/mysimulator/include/data/unit");
  COut<<*getCompositionID("Ala-C-Beta")<<Endl;
  COut<<*getCompositionID("phe"," cg ")<<Endl;
  COut<<*getCompositionName(178)<<Endl;
  COut<<*getCompositionName("arg"," cd ")<<Endl;
  COut<<*getCompositionPDBName(212)<<Endl;
  COut<<*getCompositionPDBName("met-s-delta")<<Endl;

  loadAminoAcidConnectivity("/home/jwang/Code/mysimulator/include/data/unit");
  return 0;
}

