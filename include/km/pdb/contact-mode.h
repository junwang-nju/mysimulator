
#ifndef _PDB_Contact_Mode_Name_H_
#define _PDB_Contact_Mode_Name_H_

namespace mysimulator {

  enum PDBContactAnalysisMode {
    BaseCAlpha,
    BaseHeavyAtoms
  };

  enum PDBContactSourceMode {
    UseFirstModel,
    UseAverage
  };

}

#endif

