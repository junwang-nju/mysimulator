
#include "operation/unit/name-op.h"
#include "operation/unit/composition-op.h"
#include "operation/unit/connectivity-op.h"
#include "operation/unit/property-op.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main(int argc, char** argv) {
  if(argc<2)  Error("test-unit.run <ROOT of Data>");
  loadAminoAcidName(argv[1]);
  COut<<*getUnitID("AlaNine")<<Endl;
  COut<<*getUnitID("CyS")<<Endl;
  COut<<*getUnitName(12)<<Endl;
  COut<<*getUnitSimpleName("ProLine")<<Endl;
  COut<<*getUnitSimpleName(14)<<Endl;
  COut<<*getUnitCode(5)<<Endl;
  COut<<*getUnitCode("Leucine")<<Endl;
  COut<<"========================"<<Endl;

  loadAminoAcidComposition(argv[1]);
  COut<<*getCompositionID("Ala-C-Beta")<<Endl;
  COut<<*getCompositionID("phe"," cg ")<<Endl;
  COut<<*getCompositionName(178)<<Endl;
  COut<<*getCompositionName("arg"," cd ")<<Endl;
  COut<<*getCompositionPDBName(212)<<Endl;
  COut<<*getCompositionPDBName("met-s-delta")<<Endl;
  COut<<"========================"<<Endl;

  loadAminoAcidConnectivity(argv[1]);
  COut<<IsHaveConnectivity(0,1)<<Endl;
  COut<<IsHaveConnectivity("Cys-C-Beta","Cys-S-Gamma")<<Endl;
  COut<<"========================"<<Endl;

  loadAminoAcidHeavyAtomFlag(argv[1]);
  COut<<IsHeavyAtom("Arg-C-Alpha")<<Endl;
  COut<<IsHeavyAtom("Phe-H-Zeta")<<Endl;
  COut<<IsHeavyAtom(178)<<Endl;
  COut<<IsHeavyAtom("Arg-N-Alpha")<<Endl;
  COut<<"========================"<<Endl;
  return 0;
}

