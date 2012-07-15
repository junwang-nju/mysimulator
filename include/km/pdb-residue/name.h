
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
      1,          //  Arg
      2,          //  Asn
      3,          //  Asp
      4,          //  Cys
      5,          //  Gln
      6,          //  Glu
      7,          //  Gly
      9,          //  His
      10,         //  Ile
      11,         //  Leu
      12,         //  Lys
      14,         //  Met
      15,         //  Phe
      16,         //  Pro
      17,         //  Ser
      18,         //  Thr
      19,         //  Trp
      20,         //  Tyr
      21,         //  Val
      22,         //  ctAla
      -1,         //  ctArg
      23,         //  ctAsn
      -1,         //  ctAsp
      -1,         //  ctCys
      -1,         //  ctGln
      24,         //  ctGlu
      25,         //  ctGly
      -1,         //  ctHis
      -1,         //  ctIle
      -1,         //  ctLeu
      26,         //  ctLys
      -1,         //  ctMet
      -1,         //  ctPhe
      -1,         //  ctPro
      -1,         //  ctSer
      -1,         //  ctThr
      -1,         //  ctTrp
      -1,         //  ctTyr
      -1,         //  ctVal
      -1,         //  ntAla
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
      27,         //  ntMet
      -1,         //  ntPhe
      -1,         //  ntPro
      -1,         //  ntSer
      28,         //  ntThr
      -1,         //  ntTrp
      -1,         //  ntTyr
      -1          //  ntVal
  };

}

#endif

