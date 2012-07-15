
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
      8,          //  His
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
      23,         //  ctArg
      24,         //  ctAsn
      25,         //  ctAsp
      26,         //  ctCys
      27,         //  ctGln
      28,         //  ctGlu
      29,         //  ctGly
      30,         //  ctHis
      32,         //  ctIle
      33,         //  ctLeu
      34,         //  ctLys
      36,         //  ctMet
      37,         //  ctPhe
      38,         //  ctPro
      39,         //  ctSer
      40,         //  ctThr
      41,         //  ctTrp
      42,         //  ctTyr
      43,         //  ctVal
      44,         //  ntAla
      45,         //  ntArg
      46,         //  ntAsn
      47,         //  ntAsp
      48,         //  ntCys
      49,         //  ntGln
      50,         //  ntGlu
      51,         //  ntGly
      52,         //  ntHis
      54,         //  ntIle
      55,         //  ntLeu
      56,         //  ntLys
      57,         //  ntMet
      58,         //  ntPhe
      -1,         //  ntPro
      59,         //  ntSer
      60,         //  ntThr
      61,         //  ntTrp
      62,         //  ntTyr
      63          //  ntVal
  };

}

#include "pdb-residue/key-library.h"
#include <cassert>

namespace mysimulator {

  bool IsMatchResidue(PDBResidueName RN, const unsigned int* key) {
    assert(key!=NULL);
    const unsigned int *mask=ResidueKeyLibrary[DefaultKeyID[RN]];
    bool isCover;
    isCover=true;
    for(unsigned int i=0;i<NumberResidueKey;++i)
      if((key[i]|mask[i])^mask[i]) { isCover=false; break; }
    return isCover;
  }

}

#endif

