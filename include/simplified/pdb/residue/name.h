
#ifndef _PDB_Residue_Name_H_
#define _PDB_Residue_Name_H_

namespace mysimulator {

  enum class PDBResidueName : unsigned int {
    Ala     = 0,
    Arg,
    Asn,
    Asp,
    Cys,
    Gln,
    Glu,
    Gly,
    His,
    Ile,
    Leu,
    Lys,
    Met,
    Phe,
    Pro,
    Ser,
    Thr,
    Trp,
    Tyr,
    Val,
    ctAla,
    ctArg,
    ctAsn,
    ctAsp,
    ctCys,
    ctGln,
    ctGlu,
    ctGly,
    ctHis,
    ctIle,
    ctLeu,
    ctLys,
    ctMet,
    ctPhe,
    ctPro,
    ctSer,
    ctThr,
    ctTrp,
    ctTyr,
    ctVal,
    ntAla,
    ntArg,
    ntAsn,
    ntAsp,
    ntCys,
    ntGln,
    ntGlu,
    ntGly,
    ntHis,
    ntIle,
    ntLeu,
    ntLys,
    ntMet,
    ntPhe,
    ntPro,
    ntSer,
    ntThr,
    ntTrp,
    ntTyr,
    ntVal,
    NumberResidueName,
    Unknown
  };

  PDBResidueName RegularResidueName(PDBResidueName RN) {
    if(RN<=PDBResidueName::ntVal)
      return PDBResidueName(((unsigned int)RN)-40);
    else if(RN<PDBResidueName::ctVal)
      return PDBResidueName(((unsigned int)RN)-20);
    else
      return RN;
  }

  PDBResidueName NTerminusResidueName(PDBResidueName RN) {
    if(RN<=PDBResidueName::Val)
      return PDBResidueName(((unsigned int)RN)+40);
    else if(RN<PDBResidueName::ctVal)
      return PDBResidueName(((unsigned int)RN)+20);
    else
      return RN;
  }

  PDBResidueName CTerminusResidueName(PDBResidueName RN) {
    if(RN<=PDBResidueName::Val)
      return PDBResidueName(((unsigned int)RN)+20);
    else if(RN<PDBResidueName::ntVal)
      return PDBResidueName(((unsigned int)RN)-20);
    else
      return RN;
  }

}

#endif

