
#ifndef _PDB_Residue_Name_H_
#define _PDB_Residue_Name_H_

namespace mysimulator {

  enum PDBResidueName {
    Ala = 0,
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
    UnknownResidue
  };

  int DefaultKeyID[] = {
      0,          //  Ala
      4,          //  Arg
      6,          //  Asn
      8,          //  Asp
      10,         //  Cys
      11,         //  Gln
      13,         //  Glu
      17,         //  Gly
      20,         //  His
      22,         //  Ile
      24,         //  Leu
      26,         //  Lys
      30,         //  Met
      35,         //  Phe
      37,         //  Pro
      39,         //  Ser
      41,         //  Thr
      43,         //  Trp
      45,         //  Tyr
      47,         //  Val
      2,          //  ctAla
      -1,         //  ctArg
      -1,         //  ctAsn
      -1,         //  ctAsp
      -1,         //  ctCys
      -1,         //  ctGln
      15,         //  ctGlu
      19,         //  ctGly
      -1,         //  ctHis
      -1,         //  ctIle
      -1,         //  ctLeu
      28,         //  ctLys
      -1,         //  ctMet
      -1,         //  ctPhe
      -1,         //  ctPro
      -1,         //  ctSer
      -1,         //  ctThr
      -1,         //  ctTrp
      -1,         //  ctTyr
      -1,         //  ctVal
      -1,          //  ntAla
      -1,         //  ntArg
      -1,         //  ntAsn
      -1,         //  ntAsp
      -1,         //  ntCys
      -1,         //  ntGln
      -1,         //  ntGlu
      -1,         //  ntGly
      -1,         //  ntHis
      -1,         //  ntIle
      -1,         //  ntLeu
      -1,         //  ntLys
      33,         //  ntMet
      -1,         //  ntPhe
      -1,         //  ntPro
      -1,         //  ntSer
      -1,         //  ntThr
      -1,         //  ntTrp
      -1,         //  ntTyr
      -1,         //  ntVal
  };

}

#endif

