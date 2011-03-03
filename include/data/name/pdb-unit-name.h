
#ifndef _PDB_Unit_Name_H_
#define _PDB_Unit_Name_H_

namespace std {
  
  enum PDBUnitName {
    AminoAcidAla=0,
    AminoAcidArg,
    AminoAcidAsn,
    AminoAcidAsp,
    AminoAcidCys,
    AminoAcidGln,
    AminoAcidGlu,
    AminoAcidGly,
    AminoAcidHis,
    AminoAcidIle,
    AminoAcidLeu,
    AminoAcidLys,
    AminoAcidMet,
    AminoAcidPhe,
    AminoAcidPro,
    AminoAcidSec,
    AminoAcidSer,
    AminoAcidThr,
    AminoAcidTrp,
    AminoAcidTyr,
    AminoAcidVal,
    NumberAminoAcids,
    AminoAcidALA=AminoAcidAla,
    AminoAcidARG=AminoAcidArg,
    AminoAcidASN=AminoAcidAsn,
    AminoAcidASP=AminoAcidAsp,
    AminoAcidCYS=AminoAcidCys,
    AminoAcidGLN=AminoAcidGln,
    AminoAcidGLU=AminoAcidGlu,
    AminoAcidGLY=AminoAcidGly,
    AminoAcidHIS=AminoAcidHis,
    AminoAcidILE=AminoAcidIle,
    AminoAcidLEU=AminoAcidLeu,
    AminoAcidLYS=AminoAcidLys,
    AminoAcidMET=AminoAcidMet,
    AminoAcidPHE=AminoAcidPhe,
    AminoAcidPRO=AminoAcidPro,
    AminoAcidSEC=AminoAcidSec,
    AminoAcidSER=AminoAcidSer,
    AminoAcidTHR=AminoAcidThr,
    AminoAcidTRP=AminoAcidTrp,
    AminoAcidTYR=AminoAcidTyr,
    AminoAcidVAL=AminoAcidVal,
    AminoAcidA=AminoAcidAla,
    AminoAcidR=AminoAcidArg,
    AminoAcidN=AminoAcidAsn,
    AminoAcidD=AminoAcidAsp,
    AminoAcidC=AminoAcidCys,
    AminoAcidQ=AminoAcidGln,
    AminoAcidE=AminoAcidGlu,
    AminoAcidG=AminoAcidGly,
    AminoAcidH=AminoAcidHis,
    AminoAcidI=AminoAcidIle,
    AminoAcidL=AminoAcidLeu,
    AminoAcidK=AminoAcidLys,
    AminoAcidM=AminoAcidMet,
    AminoAcidF=AminoAcidPhe,
    AminoAcidP=AminoAcidPro,
    AminoAcidU=AminoAcidSec,
    AminoAcidS=AminoAcidSer,
    AminoAcidT=AminoAcidThr,
    AminoAcidW=AminoAcidTrp,
    AminoAcidY=AminoAcidTyr,
    AminoAcidV=AminoAcidVal,
    AminoAcidCSE=AminoAcidSec,
    AminoAcidCse=AminoAcidSec,
  };

  static const char AminoAcidStringName[][4]={
      "ALA","ARG","ASN","ASP","CYS","GLN","GLU","GLY","HIS","ILE","LEU","LYS",
      "MET","PHE","PRO","SEC","SER","THR","TRP","TYR","VAL"};

  enum AminoAcidCommonAtomName {
    CAlpha=0,
    CCarbonyl,
    OCarbonyl,
    OCarboxyl,
    NAmino,
    HAlpha,
    HOCarboxyl,
    H1NAmino,
    H2NAmino,
    AminoAcidNumberCommonAtoms,
  };
  
  enum AminoAcidAlaAtomName {
    AlaCBeta=AminoAcidNumberCommonAtoms,
    AlaH1Beta,
    AlaH2Beta,
    AlaH3Beta,
    AlaH3NAmino,
    AminoAcidAlaNumberAtoms
  };

  enum AminoAcidArgAtomName {
    ArgCBeta=AminoAcidNumberCommonAtoms,
    ArgCGamma,
    ArgCDelta,
    ArgNEpsilon,
    ArgCZeta,
    ArgN1Eta,
    ArgN2Eta,
    ArgH1Beta,
    ArgH2Beta,
    ArgH1Gamma,
    ArgH2Gamma,
    ArgH1Delta,
    ArgH2Delta,
    ArgHEpsilon,
    ArgH1N1Eta,
    ArgH2N1Eta,
    ArgH1N2Eta,
    ArgH2N2Eta,
    ArgH3NAmino,
    AminoAcidArgNumberAtoms
  };

  enum AminoAcidAsnAtomName {
    AsnCBeta=AminoAcidNumberCommonAtoms,
    AsnCCarbonylGamma,
    AsnOCarbonylDelta,
    AsnNDelta,
    AsnH1Beta,
    AsnH2Beta,
    AsnH1NDelta,
    AsnH2NDelta,
    AsnH3NAmino,
    AminoAcidAsnNumberAtoms
  };

  enum AminoAcidAspAtomName {
    AspCBeta=AminoAcidNumberCommonAtoms,
    AspCCarbonylGamma,
    AspO1Delta,
    AspO2Delta,
    AspH1Beta,
    AspH2Beta,
    AspHO1Delta,
    AspHO2Delta,
    AspH3NAmino,
    AminoAcidAspNumberAtoms
  };

  enum AminoAcidCysAtomName {
    CysCBeta=AminoAcidNumberCommonAtoms,
    CysSGamma,
    CysH1Beta,
    CysH2Beta,
    CysHGamma,
    CysH3NAmino,
    AminoAcidCysNumberAtoms
  };
  
  enum AminoAcidGlnAtomName {
    GlnCBeta=AminoAcidNumberCommonAtoms,
    GlnCGamma,
    GlnCCarbonylDelta,
    GlnOCarbonylEpsilon,
    GlnNEpsilon,
    GlnH1Beta,
    GlnH2Beta,
    GlnH1Gamma,
    GlnH2Gamma,
    GlnH1NEpsilon,
    GlnH2NEpsilon,
    GlnH3NAmino,
    AminoAcidGlnNumberAtoms
  };
  
  enum AminoAcidGluAtomName {
    GluCBeta=AminoAcidNumberCommonAtoms,
    GluCGamma,
    GluCCarbonylDelta,
    GluO1Epsilon,
    GluO2Epsilon,
    GluH1Beta,
    GluH2Beta,
    GluH1Gamma,
    GluH2Gamma,
    GluHO1Epsilon,
    GluHO2Epsilon,
    GluH3NAmino,
    AminoAcidGluNumberAtoms
  };
  
  enum AminoAcidGlyAtomName {
    GlyH2Alpha=AminoAcidNumberCommonAtoms,
    GlyH3NAmino,
    AminoAcidGlyNumberAtoms
  };
  
  enum AminoAcidHisAtomName {
    HisCBeta=AminoAcidNumberCommonAtoms,
    HisCRingGamma,
    HisCRingDelta,
    HisNRingDelta,
    HisNRingEpsilonCDelta,
    HisCRingEpsilonNDelta,
    HisH1Beta,
    HisH2Beta,
    HisHCDelta,
    HisHNDelta,
    HisHNEpsilon,
    HisHCEpsilon,
    HisH3NAmino,
    AminoAcidHisNumberAtoms
  };
  
  enum AminoAcidIleAtomName {
    IleCBeta=AminoAcidNumberCommonAtoms,
    IleC1Gamma,
    IleC2Gamma,
    IleCDeltaC1Gamma,
    IleHBeta,
    IleH1C1Gamma,
    IleH2C1Gamma,
    IleH1C2Gamma,
    IleH2C2Gamma,
    IleH3C2Gamma,
    IleH1CDelta,
    IleH2CDelta,
    IleH3CDelta,
    IleH3NAmino,
    AminoAcidIleNumberAtoms
  };
  
  enum AminoAcidLeuAtomName {
    LeuCBeta=AminoAcidNumberCommonAtoms,
    LeuCGamma,
    LeuC1Delta,
    LeuC2Delta,
    LeuH1Beta,
    LeuH2Beta,
    LeuHGamma,
    LeuH1C1Delta,
    LeuH2C1Delta,
    LeuH3C1Delta,
    LeuH1C2Delta,
    LeuH2C2Delta,
    LeuH3C2Delta,
    LeuH3NAmino,
    AminoAcidLeuNumberAtoms
  };
  
  enum AminoAcidLysAtomName {
    LysCBeta=AminoAcidNumberCommonAtoms,
    LysCGamma,
    LysCDelta,
    LysCEpsilon,
    LysNZeta,
    LysH1Beta,
    LysH2Beta,
    LysH1Gamma,
    LysH2Gamma,
    LysH1Delta,
    LysH2Delta,
    LysH1Epsilon,
    LysH2Epsilon,
    LysH1Zeta,
    LysH2Zeta,
    LysH3Zeta,
    LysH3NAmino,
    AminoAcidLysNumberAtoms
  };
  
  enum AminoAcidMetAtomName {
    MetCBeta=AminoAcidNumberCommonAtoms,
    MetCGamma,
    MetSDelta,
    MetCEpsilon,
    MetH1Beta,
    MetH2Beta,
    MetH1Gamma,
    MetH2Gamma,
    MetH1Epsilon,
    MetH2Epsilon,
    MetH3Epsilon,
    MetH3NAmino,
    AminoAcidMetNumberAtoms
  };
  
  enum AminoAcidPheAtomName {
    PheCBeta=AminoAcidNumberCommonAtoms,
    PheCRingGamma,
    PheC1RingDelta,
    PheC2RingDelta,
    PheCRingEpsilonC1Delta,
    PheCRingEpsilonC2Delta,
    PheCRingZeta,
    PheH1Beta,
    PheH2Beta,
    PheHC1Delta,
    PheHC2Delta,
    PheHCEpsilonC1Delta,
    PheHCEpsilonC2Delta,
    PheHCZeta,
    PheH3NAmino,
    AminoAcidPheNumberAtoms
  };
  
  enum AminoAcidProAtomName {
    ProCRingBeta=AminoAcidNumberCommonAtoms,
    ProCRingGammaCBeta,
    ProCRingGammaNAmino,
    ProH1CBeta,
    ProH2CBeta,
    ProH1CGammaCBeta,
    ProH2CGammaCBeta,
    ProH1CGammaNAmino,
    ProH2CGammaNAmino,
    AminoAcidProNumberAtoms,
    ProNRingBeta=NAmino,
    ProH1NBeta=H1NAmino,
    ProH2NBeta=H2NAmino,
    ProCRingGammaNBeta=ProCRingGammaNAmino,
    ProH1CGammaNBeta=ProH1CGammaNAmino,
    ProH2CGammaNBeta=ProH2CGammaNAmino
  };
  
  enum AminoAcidSecAtomName {
    SecCBeta=AminoAcidNumberCommonAtoms,
    SecSeGamma,
    SecH1Beta,
    SecH2Beta,
    SecHGamma,
    SecH3NAmino,
    AminoAcidSecNumberAtoms
  };
  
  enum AminoAcidSerAtomName {
    SerCBeta=AminoAcidNumberCommonAtoms,
    SerOGamma,
    SerH1Beta,
    SerH2Beta,
    SerHGamma,
    SerH3NAmino,
    AminoAcidSerNumberAtoms
  };
  
  enum AminoAcidThrAtomName {
    ThrCBeta=AminoAcidNumberCommonAtoms,
    ThrOGamma,
    ThrCGamma,
    ThrHBeta,
    ThrHOGamma,
    ThrH1CGamma,
    ThrH2CGamma,
    ThrH3CGamma,
    ThrH3NAmino,
    AminoAcidThrNumberAtoms
  };
  
  enum AminoAcidTrpAtomName {
    TrpCBeta=AminoAcidNumberCommonAtoms,
    TrpCGamma,
    TrpC1Delta,
    TrpC2Delta,
    TrpNEpsilonC1Delta,
    TrpC1EpsilonC2Delta,
    TrpC2EpsilonC2Delta,
    TrpCZetaC1Epsilon,
    TrpCZetaC2Epsilon,
    TrpCEta,
    TrpH1Beta,
    TrpH2Beta,
    TrpHC1Delta,
    TrpHNEpsilon,
    TrpHC2Epsilon,
    TrpHCZetaC1Epsilon,
    TrpHCZetaC2Epsilon,
    TrpHCEta,
    TrpH3NAmino,
    AminoAcidTrpNumberAtoms
  };
  
  enum AminoAcidTyrAtomName {
    TyrCBeta=AminoAcidNumberCommonAtoms,
    TyrCRingGamma,
    TyrC1RingDelta,
    TyrC2RingDelta,
    TyrCRingEpsilonC1Delta,
    TyrCRingEpsilonC2Delta,
    TyrCRingZeta,
    TyrOEta,
    TyrH1Beta,
    TyrH2Beta,
    TyrHC1Delta,
    TyrHC2Delta,
    TyrHCEpsilonC1Delta,
    TyrHCEpsilonC2Delta,
    TyrHOEta,
    TyrH3NAmino,
    AminoAcidTyrNumberAtoms
  };
  
  enum AminoAcidValAtomName {
    ValCBeta=AminoAcidNumberCommonAtoms,
    ValC1Gamma,
    ValC2Gamma,
    ValHBeta,
    ValH1C1Gamma,
    ValH2C1Gamma,
    ValH3C1Gamma,
    ValH1C2Gamma,
    ValH2C2Gamma,
    ValH3C2Gamma,
    ValH3NAmino,
    AminoAcidValNumberAtoms
  };

}

#include "data/pdb/unit-name-mapper.h"
#include "operation/basic/vector-op.h"

namespace std {
  
  static Vector<unsigned int> AminoAcidNumberAtoms;
  
  void InitAminoAcidNumberAtoms() {
    allocate(AminoAcidNumberAtoms,NumberAminoAcids);
    AminoAcidNumberAtoms[AminoAcidAla]=AminoAcidAlaNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidArg]=AminoAcidArgNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidAsn]=AminoAcidAsnNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidAsp]=AminoAcidAspNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidCys]=AminoAcidCysNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidGln]=AminoAcidGlnNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidGlu]=AminoAcidGluNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidGly]=AminoAcidGlyNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidHis]=AminoAcidHisNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidIle]=AminoAcidIleNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidLeu]=AminoAcidLeuNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidLys]=AminoAcidLysNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidMet]=AminoAcidMetNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidPhe]=AminoAcidPheNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidPro]=AminoAcidProNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidSec]=AminoAcidSecNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidSer]=AminoAcidSerNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidThr]=AminoAcidThrNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidTrp]=AminoAcidTrpNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidTyr]=AminoAcidTyrNumberAtoms;
    AminoAcidNumberAtoms[AminoAcidVal]=AminoAcidValNumberAtoms;
  }

  static PDBUnitNameMapper  UnitNameLibrary;
  static PDBUnitNameMapper  UnitAtomNameLibrary;
  
  void InitNameLibrary() {
    if(!IsAvailable(AminoAcidNumberAtoms))  InitAminoAcidNumberAtoms();
    allocate(UnitNameLibrary,63);
    Set(UnitNameLibrary, 0,"ALA    ",AminoAcidAla);
    Set(UnitNameLibrary, 1,"Ala    ",AminoAcidAla);
    Set(UnitNameLibrary, 2,"A      ",AminoAcidAla);
    Set(UnitNameLibrary, 3,"ARG    ",AminoAcidArg);
    Set(UnitNameLibrary, 4,"Arg    ",AminoAcidArg);
    Set(UnitNameLibrary, 5,"R      ",AminoAcidArg);
    Set(UnitNameLibrary, 6,"ASN    ",AminoAcidAsn);
    Set(UnitNameLibrary, 7,"Asn    ",AminoAcidAsn);
    Set(UnitNameLibrary, 8,"N      ",AminoAcidAsn);
    Set(UnitNameLibrary, 9,"ASP    ",AminoAcidAsp);
    Set(UnitNameLibrary,10,"Asp    ",AminoAcidAsp);
    Set(UnitNameLibrary,11,"D      ",AminoAcidAsp);
    Set(UnitNameLibrary,12,"CYS    ",AminoAcidCys);
    Set(UnitNameLibrary,13,"Cys    ",AminoAcidCys);
    Set(UnitNameLibrary,14,"C      ",AminoAcidCys);
    Set(UnitNameLibrary,15,"GLN    ",AminoAcidGln);
    Set(UnitNameLibrary,16,"Gln    ",AminoAcidGln);
    Set(UnitNameLibrary,17,"Q      ",AminoAcidGln);
    Set(UnitNameLibrary,18,"GLU    ",AminoAcidGlu);
    Set(UnitNameLibrary,19,"Glu    ",AminoAcidGlu);
    Set(UnitNameLibrary,20,"E      ",AminoAcidGlu);
    Set(UnitNameLibrary,21,"GLY    ",AminoAcidGly);
    Set(UnitNameLibrary,22,"Gly    ",AminoAcidGly);
    Set(UnitNameLibrary,23,"G      ",AminoAcidGly);
    Set(UnitNameLibrary,24,"HIS    ",AminoAcidHis);
    Set(UnitNameLibrary,25,"His    ",AminoAcidHis);
    Set(UnitNameLibrary,26,"H      ",AminoAcidHis);
    Set(UnitNameLibrary,27,"ILE    ",AminoAcidIle);
    Set(UnitNameLibrary,28,"Ile    ",AminoAcidIle);
    Set(UnitNameLibrary,29,"I      ",AminoAcidIle);
    Set(UnitNameLibrary,30,"LEU    ",AminoAcidLeu);
    Set(UnitNameLibrary,31,"Leu    ",AminoAcidLeu);
    Set(UnitNameLibrary,32,"L      ",AminoAcidLeu);
    Set(UnitNameLibrary,33,"LYS    ",AminoAcidLys);
    Set(UnitNameLibrary,34,"Lys    ",AminoAcidLys);
    Set(UnitNameLibrary,35,"K      ",AminoAcidLys);
    Set(UnitNameLibrary,36,"MET    ",AminoAcidMet);
    Set(UnitNameLibrary,37,"Met    ",AminoAcidMet);
    Set(UnitNameLibrary,38,"M      ",AminoAcidMet);
    Set(UnitNameLibrary,39,"PHE    ",AminoAcidPhe);
    Set(UnitNameLibrary,40,"Phe    ",AminoAcidPhe);
    Set(UnitNameLibrary,41,"F      ",AminoAcidPhe);
    Set(UnitNameLibrary,42,"PRO    ",AminoAcidPro);
    Set(UnitNameLibrary,43,"Pro    ",AminoAcidPro);
    Set(UnitNameLibrary,44,"P      ",AminoAcidPro);
    Set(UnitNameLibrary,45,"SEC    ",AminoAcidSec);
    Set(UnitNameLibrary,46,"Sec    ",AminoAcidSec);
    Set(UnitNameLibrary,47,"U      ",AminoAcidSec);
    Set(UnitNameLibrary,48,"SER    ",AminoAcidSer);
    Set(UnitNameLibrary,49,"Ser    ",AminoAcidSer);
    Set(UnitNameLibrary,50,"S      ",AminoAcidSer);
    Set(UnitNameLibrary,51,"THR    ",AminoAcidThr);
    Set(UnitNameLibrary,52,"Thr    ",AminoAcidThr);
    Set(UnitNameLibrary,53,"T      ",AminoAcidThr);
    Set(UnitNameLibrary,54,"TRP    ",AminoAcidTrp);
    Set(UnitNameLibrary,55,"Trp    ",AminoAcidTrp);
    Set(UnitNameLibrary,56,"W      ",AminoAcidTrp);
    Set(UnitNameLibrary,57,"TYR    ",AminoAcidTyr);
    Set(UnitNameLibrary,58,"Tyr    ",AminoAcidTyr);
    Set(UnitNameLibrary,59,"Y      ",AminoAcidTyr);
    Set(UnitNameLibrary,60,"VAL    ",AminoAcidVal);
    Set(UnitNameLibrary,61,"Val    ",AminoAcidVal);
    Set(UnitNameLibrary,62,"V      ",AminoAcidVal);
    UnitNameLibrary.update();
    allocate(UnitAtomNameLibrary,244);
    Set(UnitAtomNameLibrary,  0,"    CA ",CAlpha);
    Set(UnitAtomNameLibrary,  1,"    C  ",CCarbonyl);
    Set(UnitAtomNameLibrary,  2,"    O  ",OCarbonyl);
    Set(UnitAtomNameLibrary,  3,"    OXT",OCarboxyl);
    Set(UnitAtomNameLibrary,  5,"    N  ",NAmino);
    Set(UnitAtomNameLibrary,  4,"    HA ",HAlpha);
    Set(UnitAtomNameLibrary,  6,"    HXT",HOCarboxyl);
    Set(UnitAtomNameLibrary,  7,"    H  ",H1NAmino);
    Set(UnitAtomNameLibrary,  8,"    H1 ",H1NAmino);
    Set(UnitAtomNameLibrary,  9,"    H2 ",H2NAmino);
    Set(UnitAtomNameLibrary, 10,"ALA CB ",AlaCBeta);
    Set(UnitAtomNameLibrary, 11,"ALA HB1",AlaH1Beta);
    Set(UnitAtomNameLibrary, 12,"ALA HB2",AlaH2Beta);
    Set(UnitAtomNameLibrary, 13,"ALA HB3",AlaH3Beta);
    Set(UnitAtomNameLibrary, 14,"ALA H3 ",AlaH3NAmino);
    Set(UnitAtomNameLibrary, 15,"ARG CB ",ArgCBeta);
    Set(UnitAtomNameLibrary, 16,"ARG CG ",ArgCGamma);
    Set(UnitAtomNameLibrary, 17,"ARG CD ",ArgCDelta);
    Set(UnitAtomNameLibrary, 18,"ARG NE ",ArgNEpsilon);
    Set(UnitAtomNameLibrary, 19,"ARG CZ ",ArgCZeta);
    Set(UnitAtomNameLibrary, 20,"ARG NH1",ArgN1Eta);
    Set(UnitAtomNameLibrary, 21,"ARG NH2",ArgN2Eta);
    Set(UnitAtomNameLibrary, 22,"ARG HB2",ArgH1Beta);
    Set(UnitAtomNameLibrary, 23,"ARG HB3",ArgH2Beta);
    Set(UnitAtomNameLibrary, 24,"ARG HG2",ArgH1Gamma);
    Set(UnitAtomNameLibrary, 25,"ARG HG3",ArgH2Gamma);
    Set(UnitAtomNameLibrary, 26,"ARG HD2",ArgH1Delta);
    Set(UnitAtomNameLibrary, 27,"ARG HD3",ArgH2Delta);
    Set(UnitAtomNameLibrary, 28,"ARG HE ",ArgHEpsilon);
    Set(UnitAtomNameLibrary, 29,"ARGHH11",ArgH1N1Eta);
    Set(UnitAtomNameLibrary, 30,"ARGHH12",ArgH2N1Eta);
    Set(UnitAtomNameLibrary, 31,"ARGHH21",ArgH1N2Eta);
    Set(UnitAtomNameLibrary, 32,"ARGHH22",ArgH2N2Eta);
    Set(UnitAtomNameLibrary, 33,"ARG H3 ",ArgH3NAmino);
    Set(UnitAtomNameLibrary, 34,"ASN CB ",AsnCBeta);
    Set(UnitAtomNameLibrary, 35,"ASN CG ",AsnCCarbonylGamma);
    Set(UnitAtomNameLibrary, 36,"ASN OD1",AsnOCarbonylDelta);
    Set(UnitAtomNameLibrary, 37,"ASN ND2",AsnNDelta);
    Set(UnitAtomNameLibrary, 38,"ASN HB2",AsnH1Beta);
    Set(UnitAtomNameLibrary, 39,"ASN HB3",AsnH2Beta);
    Set(UnitAtomNameLibrary, 40,"ASNHD21",AsnH1NDelta);
    Set(UnitAtomNameLibrary, 41,"ASNHD22",AsnH2NDelta);
    Set(UnitAtomNameLibrary, 42,"ASP CB ",AspCBeta);
    Set(UnitAtomNameLibrary, 43,"ASP CG ",AspCCarbonylGamma);
    Set(UnitAtomNameLibrary, 44,"ASP OD1",AspO1Delta);
    Set(UnitAtomNameLibrary, 45,"ASP OD2",AspO2Delta);
    Set(UnitAtomNameLibrary, 46,"ASP HB2",AspH1Beta);
    Set(UnitAtomNameLibrary, 47,"ASP HB3",AspH2Beta);
    Set(UnitAtomNameLibrary, 48,"ASP H3 ",AspH3NAmino);
    Set(UnitAtomNameLibrary, 49,"CYS CB ",CysCBeta);
    Set(UnitAtomNameLibrary, 50,"CYS SG ",CysSGamma);
    Set(UnitAtomNameLibrary, 51,"CYS HB2",CysH1Beta);
    Set(UnitAtomNameLibrary, 52,"CYS HB3",CysH2Beta);
    Set(UnitAtomNameLibrary, 53,"CYS HG ",CysHGamma);
    Set(UnitAtomNameLibrary, 54,"CYS H3 ",CysH3NAmino);
    Set(UnitAtomNameLibrary, 55,"GLN CB ",GlnCBeta);
    Set(UnitAtomNameLibrary, 56,"GLN CG ",GlnCGamma);
    Set(UnitAtomNameLibrary, 57,"GLN CD ",GlnCCarbonylDelta);
    Set(UnitAtomNameLibrary, 58,"GLN OE1",GlnOCarbonylEpsilon);
    Set(UnitAtomNameLibrary, 59,"GLN NE2",GlnNEpsilon);
    Set(UnitAtomNameLibrary, 60,"GLN HB2",GlnH1Beta);
    Set(UnitAtomNameLibrary, 61,"GLN HB3",GlnH2Beta);
    Set(UnitAtomNameLibrary, 62,"GLN HG2",GlnH1Gamma);
    Set(UnitAtomNameLibrary, 63,"GLN HG3",GlnH2Gamma);
    Set(UnitAtomNameLibrary, 64,"GLNHE21",GlnH1NEpsilon);
    Set(UnitAtomNameLibrary, 65,"GLNHE22",GlnH2NEpsilon);
    Set(UnitAtomNameLibrary, 66,"GLN H3 ",GlnH3NAmino);
    Set(UnitAtomNameLibrary, 67,"GLU CB ",GluCBeta);
    Set(UnitAtomNameLibrary, 68,"GLU CG ",GluCGamma);
    Set(UnitAtomNameLibrary, 69,"GLU CD ",GluCCarbonylDelta);
    Set(UnitAtomNameLibrary, 70,"GLU OE1",GluO1Epsilon);
    Set(UnitAtomNameLibrary, 71,"GLU OE2",GluO2Epsilon);
    Set(UnitAtomNameLibrary, 72,"GLU HB2",GluH1Beta);
    Set(UnitAtomNameLibrary, 73,"GLU HB3",GluH2Beta);
    Set(UnitAtomNameLibrary, 74,"GLU HG2",GluH1Gamma);
    Set(UnitAtomNameLibrary, 75,"GLU HG3",GluH2Gamma);
    Set(UnitAtomNameLibrary, 76,"GLU HE1",GluHO1Epsilon);
    Set(UnitAtomNameLibrary, 77,"GLU HE2",GluHO2Epsilon);
    Set(UnitAtomNameLibrary, 78,"GLU H3 ",GluH3NAmino);
    Set(UnitAtomNameLibrary, 79,"GLY HA2",HAlpha);
    Set(UnitAtomNameLibrary, 80,"GLY HA3",GlyH2Alpha);
    Set(UnitAtomNameLibrary, 81,"GLY H3 ",GlyH3NAmino);
    Set(UnitAtomNameLibrary, 82,"HIS CB ",HisCBeta);
    Set(UnitAtomNameLibrary, 83,"HIS CG ",HisCRingGamma);
    Set(UnitAtomNameLibrary, 84,"HIS ND1",HisNRingDelta);
    Set(UnitAtomNameLibrary, 85,"HIS CD2",HisCRingDelta);
    Set(UnitAtomNameLibrary, 86,"HIS CE1",HisCRingEpsilonNDelta);
    Set(UnitAtomNameLibrary, 87,"HIS NE2",HisNRingEpsilonCDelta);
    Set(UnitAtomNameLibrary, 88,"HIS HB2",HisH1Beta);
    Set(UnitAtomNameLibrary, 89,"HIS HB3",HisH2Beta);
    Set(UnitAtomNameLibrary, 90,"HIS HD1",HisHNDelta);
    Set(UnitAtomNameLibrary, 91,"HIS HD2",HisHCDelta);
    Set(UnitAtomNameLibrary, 92,"HIS HE1",HisHCEpsilon);
    Set(UnitAtomNameLibrary, 93,"HIS HE2",HisHNEpsilon);
    Set(UnitAtomNameLibrary, 94,"HIS H3 ",HisH3NAmino);
    Set(UnitAtomNameLibrary, 95,"ILE CB ",IleCBeta);
    Set(UnitAtomNameLibrary, 96,"ILE CG1",IleC1Gamma);
    Set(UnitAtomNameLibrary, 97,"ILE CG2",IleC2Gamma);
    Set(UnitAtomNameLibrary, 98,"ILE CD1",IleCDeltaC1Gamma);
    Set(UnitAtomNameLibrary, 99,"ILE HB ",IleHBeta);
    Set(UnitAtomNameLibrary,100,"ILEHG12",IleH1C1Gamma);
    Set(UnitAtomNameLibrary,101,"ILEHG13",IleH2C1Gamma);
    Set(UnitAtomNameLibrary,102,"ILEHG21",IleH1C2Gamma);
    Set(UnitAtomNameLibrary,103,"ILEHG22",IleH2C2Gamma);
    Set(UnitAtomNameLibrary,104,"ILEHG23",IleH3C2Gamma);
    Set(UnitAtomNameLibrary,105,"ILEHD11",IleH1CDelta);
    Set(UnitAtomNameLibrary,106,"ILEHD12",IleH2CDelta);
    Set(UnitAtomNameLibrary,107,"ILEHD13",IleH3CDelta);
    Set(UnitAtomNameLibrary,108,"ILE H3 ",IleH3NAmino);
    Set(UnitAtomNameLibrary,109,"LEU CB ",LeuCBeta);
    Set(UnitAtomNameLibrary,110,"LEU CG ",LeuCGamma);
    Set(UnitAtomNameLibrary,111,"LEU CD1",LeuC1Delta);
    Set(UnitAtomNameLibrary,112,"LEU CD2",LeuC2Delta);
    Set(UnitAtomNameLibrary,113,"LEU HB2",LeuH1Beta);
    Set(UnitAtomNameLibrary,114,"LEU HB3",LeuH2Beta);
    Set(UnitAtomNameLibrary,115,"LEU HG ",LeuHGamma);
    Set(UnitAtomNameLibrary,116,"LEUHD11",LeuH1C1Delta);
    Set(UnitAtomNameLibrary,117,"LEUHD12",LeuH2C1Delta);
    Set(UnitAtomNameLibrary,118,"LEUHD13",LeuH3C1Delta);
    Set(UnitAtomNameLibrary,119,"LEUHD21",LeuH1C2Delta);
    Set(UnitAtomNameLibrary,120,"LEUHD22",LeuH2C2Delta);
    Set(UnitAtomNameLibrary,121,"LEUHD23",LeuH3C2Delta);
    Set(UnitAtomNameLibrary,122,"LEU H3 ",LeuH3NAmino);
    Set(UnitAtomNameLibrary,123,"LYS CB ",LysCBeta);
    Set(UnitAtomNameLibrary,124,"LYS CB ",LysCBeta);
    Set(UnitAtomNameLibrary,125,"LYS CG ",LysCGamma);
    Set(UnitAtomNameLibrary,126,"LYS CD ",LysCDelta);
    Set(UnitAtomNameLibrary,127,"LYS CE ",LysCEpsilon);
    Set(UnitAtomNameLibrary,128,"LYS NZ ",LysNZeta);
    Set(UnitAtomNameLibrary,129,"LYS HB2",LysH1Beta);
    Set(UnitAtomNameLibrary,130,"LYS HB3",LysH2Beta);
    Set(UnitAtomNameLibrary,131,"LYS HG2",LysH1Gamma);
    Set(UnitAtomNameLibrary,132,"LYS HG3",LysH2Gamma);
    Set(UnitAtomNameLibrary,133,"LYS HD2",LysH1Delta);
    Set(UnitAtomNameLibrary,134,"LYS HD3",LysH2Delta);
    Set(UnitAtomNameLibrary,135,"LYS HE2",LysH1Epsilon);
    Set(UnitAtomNameLibrary,136,"LYS HE3",LysH2Epsilon);
    Set(UnitAtomNameLibrary,137,"LYS HZ1",LysH1Zeta);
    Set(UnitAtomNameLibrary,138,"LYS HZ2",LysH2Zeta);
    Set(UnitAtomNameLibrary,139,"LYS HZ3",LysH3Zeta);
    Set(UnitAtomNameLibrary,140,"LYS H3 ",LysH3NAmino);
    Set(UnitAtomNameLibrary,141,"MET CB ",MetCBeta);
    Set(UnitAtomNameLibrary,142,"MET CG ",MetCGamma);
    Set(UnitAtomNameLibrary,143,"MET SD ",MetSDelta);
    Set(UnitAtomNameLibrary,144,"MET CE ",MetCEpsilon);
    Set(UnitAtomNameLibrary,145,"MET HB2",MetH1Beta);
    Set(UnitAtomNameLibrary,146,"MET HB3",MetH2Beta);
    Set(UnitAtomNameLibrary,147,"MET HG2",MetH1Gamma);
    Set(UnitAtomNameLibrary,148,"MET HG3",MetH2Gamma);
    Set(UnitAtomNameLibrary,149,"MET HE1",MetH1Epsilon);
    Set(UnitAtomNameLibrary,150,"MET HE2",MetH2Epsilon);
    Set(UnitAtomNameLibrary,151,"MET HE3",MetH3Epsilon);
    Set(UnitAtomNameLibrary,152,"MET H3 ",MetH3NAmino);
    Set(UnitAtomNameLibrary,153,"PHE CB ",PheCBeta);
    Set(UnitAtomNameLibrary,154,"PHE CG ",PheCRingGamma);
    Set(UnitAtomNameLibrary,155,"PHE CD1",PheC1RingDelta);
    Set(UnitAtomNameLibrary,156,"PHE CD2",PheC2RingDelta);
    Set(UnitAtomNameLibrary,157,"PHE CE1",PheCRingEpsilonC1Delta);
    Set(UnitAtomNameLibrary,158,"PHE CE2",PheCRingEpsilonC2Delta);
    Set(UnitAtomNameLibrary,159,"PHE CZ ",PheCRingZeta);
    Set(UnitAtomNameLibrary,160,"PHE HB2",PheH1Beta);
    Set(UnitAtomNameLibrary,161,"PHE HB3",PheH2Beta);
    Set(UnitAtomNameLibrary,162,"PHE HD1",PheHC1Delta);
    Set(UnitAtomNameLibrary,163,"PHE HD2",PheHC2Delta);
    Set(UnitAtomNameLibrary,164,"PHE HE1",PheHCEpsilonC1Delta);
    Set(UnitAtomNameLibrary,165,"PHE HE2",PheHCEpsilonC2Delta);
    Set(UnitAtomNameLibrary,166,"PHE HZ ",PheHCZeta);
    Set(UnitAtomNameLibrary,167,"PHE H3 ",PheH3NAmino);
    Set(UnitAtomNameLibrary,168,"PRO CB ",ProCRingBeta);
    Set(UnitAtomNameLibrary,169,"PRO CG ",ProCRingGammaCBeta);
    Set(UnitAtomNameLibrary,170,"PRO CD ",ProCRingGammaNAmino);
    Set(UnitAtomNameLibrary,171,"PRO HB2",ProH1CBeta);
    Set(UnitAtomNameLibrary,172,"PRO HB3",ProH2CBeta);
    Set(UnitAtomNameLibrary,173,"PRO HG2",ProH1CGammaCBeta);
    Set(UnitAtomNameLibrary,174,"PRO HG3",ProH2CGammaCBeta);
    Set(UnitAtomNameLibrary,175,"PRO HD2",ProH1CGammaNAmino);
    Set(UnitAtomNameLibrary,176,"PRO HD3",ProH2CGammaNAmino);
    Set(UnitAtomNameLibrary,177,"SEC CB ",SecCBeta);
    Set(UnitAtomNameLibrary,178,"SECSE  ",SecSeGamma);
    Set(UnitAtomNameLibrary,179,"SEC HB2",SecH1Beta);
    Set(UnitAtomNameLibrary,180,"SEC HB3",SecH2Beta);
    Set(UnitAtomNameLibrary,181,"SEC HG ",SecHGamma);
    Set(UnitAtomNameLibrary,182,"SEC H3 ",SecH3NAmino);
    Set(UnitAtomNameLibrary,183,"SER CB ",SerCBeta);
    Set(UnitAtomNameLibrary,184,"SER OG ",SerOGamma);
    Set(UnitAtomNameLibrary,185,"SER HB2",SerH1Beta);
    Set(UnitAtomNameLibrary,186,"SER HB3",SerH2Beta);
    Set(UnitAtomNameLibrary,187,"SER HG ",SerHGamma);
    Set(UnitAtomNameLibrary,188,"SER H3 ",SerH3NAmino);
    Set(UnitAtomNameLibrary,189,"THR CB ",ThrCBeta);
    Set(UnitAtomNameLibrary,190,"THR OG1",ThrOGamma);
    Set(UnitAtomNameLibrary,191,"THR CG2",ThrCGamma);
    Set(UnitAtomNameLibrary,192,"THR HB ",ThrHBeta);
    Set(UnitAtomNameLibrary,193,"THR HG1",ThrHOGamma);
    Set(UnitAtomNameLibrary,194,"THRHG21",ThrH1CGamma);
    Set(UnitAtomNameLibrary,195,"THRHG22",ThrH2CGamma);
    Set(UnitAtomNameLibrary,196,"THRHG23",ThrH3CGamma);
    Set(UnitAtomNameLibrary,197,"THR H3 ",ThrH3NAmino);
    Set(UnitAtomNameLibrary,198,"TRP CB ",TrpCBeta);
    Set(UnitAtomNameLibrary,199,"TRP CG ",TrpCGamma);
    Set(UnitAtomNameLibrary,200,"TRP CD1",TrpC1Delta);
    Set(UnitAtomNameLibrary,201,"TRP CD2",TrpC2Delta);
    Set(UnitAtomNameLibrary,202,"TRP NE1",TrpNEpsilonC1Delta);
    Set(UnitAtomNameLibrary,203,"TRP CE2",TrpC1EpsilonC2Delta);
    Set(UnitAtomNameLibrary,204,"TRP CE3",TrpC2EpsilonC2Delta);
    Set(UnitAtomNameLibrary,205,"TRP CZ2",TrpCZetaC1Epsilon);
    Set(UnitAtomNameLibrary,206,"TRP CZ3",TrpCZetaC2Epsilon);
    Set(UnitAtomNameLibrary,207,"TRP CH2",TrpCEta);
    Set(UnitAtomNameLibrary,208,"TRP HB2",TrpH1Beta);
    Set(UnitAtomNameLibrary,209,"TRP HB3",TrpH2Beta);
    Set(UnitAtomNameLibrary,210,"TRP HD1",TrpHC1Delta);
    Set(UnitAtomNameLibrary,211,"TRP HE1",TrpHNEpsilon);
    Set(UnitAtomNameLibrary,212,"TRP HE3",TrpHC2Epsilon);
    Set(UnitAtomNameLibrary,213,"TRP HZ2",TrpHCZetaC1Epsilon);
    Set(UnitAtomNameLibrary,214,"TRP HZ3",TrpHCZetaC2Epsilon);
    Set(UnitAtomNameLibrary,215,"TRP HH2",TrpHCEta);
    Set(UnitAtomNameLibrary,216,"TRP H3 ",TrpH3NAmino);
    Set(UnitAtomNameLibrary,217,"TYR CB ",TyrCBeta);
    Set(UnitAtomNameLibrary,218,"TYR CG ",TyrCRingGamma);
    Set(UnitAtomNameLibrary,219,"TYR CD1",TyrC1RingDelta);
    Set(UnitAtomNameLibrary,220,"TYR CD2",TyrC2RingDelta);
    Set(UnitAtomNameLibrary,221,"TYR CE1",TyrCRingEpsilonC1Delta);
    Set(UnitAtomNameLibrary,222,"TYR CE2",TyrCRingEpsilonC2Delta);
    Set(UnitAtomNameLibrary,223,"TYR CZ ",TyrCRingZeta);
    Set(UnitAtomNameLibrary,224,"TYR OH ",TyrOEta);
    Set(UnitAtomNameLibrary,225,"TYR HB2",TyrH1Beta);
    Set(UnitAtomNameLibrary,226,"TYR HB3",TyrH2Beta);
    Set(UnitAtomNameLibrary,227,"TYR HD1",TyrHC1Delta);
    Set(UnitAtomNameLibrary,228,"TYR HD2",TyrHC2Delta);
    Set(UnitAtomNameLibrary,229,"TYR HE1",TyrHCEpsilonC1Delta);
    Set(UnitAtomNameLibrary,230,"TYR HE2",TyrHCEpsilonC2Delta);
    Set(UnitAtomNameLibrary,231,"TYR HH ",TyrHOEta);
    Set(UnitAtomNameLibrary,232,"TYR H3 ",TyrH3NAmino);
    Set(UnitAtomNameLibrary,233,"VAL CB ",ValCBeta);
    Set(UnitAtomNameLibrary,234,"VAL CG1",ValC1Gamma);
    Set(UnitAtomNameLibrary,235,"VAL CG2",ValC2Gamma);
    Set(UnitAtomNameLibrary,236,"VAL HB ",ValHBeta);
    Set(UnitAtomNameLibrary,237,"VALHG11",ValH1C1Gamma);
    Set(UnitAtomNameLibrary,238,"VALHG12",ValH2C1Gamma);
    Set(UnitAtomNameLibrary,239,"VALHG13",ValH3C1Gamma);
    Set(UnitAtomNameLibrary,240,"VALHG21",ValH1C2Gamma);
    Set(UnitAtomNameLibrary,241,"VALHG22",ValH2C2Gamma);
    Set(UnitAtomNameLibrary,242,"VALHG23",ValH3C2Gamma);
    Set(UnitAtomNameLibrary,243,"VAL H3 ",ValH3NAmino);
    UnitAtomNameLibrary.update();
  }

}

#include "data/basic/property-list.h"

namespace std {

  static PropertyList<bool> IsHeavyAtom;

  void InitHeavyAtomProperty() {
    if(!IsAvailable(AminoAcidNumberAtoms))  InitAminoAcidNumberAtoms();
    allocate(IsHeavyAtom,AminoAcidNumberAtoms);
    copy(IsHeavyAtom,true);
    for(unsigned int i=0;i<NumberAminoAcids;++i) {
      IsHeavyAtom[i][HAlpha]=false;
      IsHeavyAtom[i][HOCarboxyl]=false;
      IsHeavyAtom[i][H1NAmino]=false;
      IsHeavyAtom[i][H2NAmino]=false;
    }

    IsHeavyAtom[AminoAcidAla][AlaH1Beta]=false;
    IsHeavyAtom[AminoAcidAla][AlaH2Beta]=false;
    IsHeavyAtom[AminoAcidAla][AlaH3Beta]=false;
    IsHeavyAtom[AminoAcidAla][AlaH3NAmino]=false;

    IsHeavyAtom[AminoAcidArg][ArgH1Beta]=false;
    IsHeavyAtom[AminoAcidArg][ArgH2Beta]=false;
    IsHeavyAtom[AminoAcidArg][ArgH1Gamma]=false;
    IsHeavyAtom[AminoAcidArg][ArgH2Gamma]=false;
    IsHeavyAtom[AminoAcidArg][ArgH1Delta]=false;
    IsHeavyAtom[AminoAcidArg][ArgH2Delta]=false;
    IsHeavyAtom[AminoAcidArg][ArgHEpsilon]=false;
    IsHeavyAtom[AminoAcidArg][ArgH1N1Eta]=false;
    IsHeavyAtom[AminoAcidArg][ArgH2N1Eta]=false;
    IsHeavyAtom[AminoAcidArg][ArgH1N2Eta]=false;
    IsHeavyAtom[AminoAcidArg][ArgH2N2Eta]=false;
    IsHeavyAtom[AminoAcidArg][ArgH3NAmino]=false;

    IsHeavyAtom[AminoAcidAsn][AsnH1Beta]=false;
    IsHeavyAtom[AminoAcidAsn][AsnH2Beta]=false;
    IsHeavyAtom[AminoAcidAsn][AsnH1NDelta]=false;
    IsHeavyAtom[AminoAcidAsn][AsnH2NDelta]=false;
    IsHeavyAtom[AminoAcidAsn][AsnH3NAmino]=false;

    IsHeavyAtom[AminoAcidAsp][AspH1Beta]=false;
    IsHeavyAtom[AminoAcidAsp][AspH2Beta]=false;
    IsHeavyAtom[AminoAcidAsp][AspHO1Delta]=false;
    IsHeavyAtom[AminoAcidAsp][AspHO2Delta]=false;
    IsHeavyAtom[AminoAcidAsp][AspH3NAmino]=false;

    IsHeavyAtom[AminoAcidCys][CysH1Beta]=false;
    IsHeavyAtom[AminoAcidCys][CysH2Beta]=false;
    IsHeavyAtom[AminoAcidCys][CysHGamma]=false;
    IsHeavyAtom[AminoAcidCys][CysH3NAmino]=false;

    IsHeavyAtom[AminoAcidGln][GlnH1Beta]=false;
    IsHeavyAtom[AminoAcidGln][GlnH2Beta]=false;
    IsHeavyAtom[AminoAcidGln][GlnH1Gamma]=false;
    IsHeavyAtom[AminoAcidGln][GlnH2Gamma]=false;
    IsHeavyAtom[AminoAcidGln][GlnH1NEpsilon]=false;
    IsHeavyAtom[AminoAcidGln][GlnH2NEpsilon]=false;
    IsHeavyAtom[AminoAcidGln][GlnH3NAmino]=false;

    IsHeavyAtom[AminoAcidGlu][GluH1Beta]=false;
    IsHeavyAtom[AminoAcidGlu][GluH2Beta]=false;
    IsHeavyAtom[AminoAcidGlu][GluH1Gamma]=false;
    IsHeavyAtom[AminoAcidGlu][GluH2Gamma]=false;
    IsHeavyAtom[AminoAcidGlu][GluHO1Epsilon]=false;
    IsHeavyAtom[AminoAcidGlu][GluHO2Epsilon]=false;
    IsHeavyAtom[AminoAcidGlu][GluH3NAmino]=false;

    IsHeavyAtom[AminoAcidGly][GlyH2Alpha]=false;
    IsHeavyAtom[AminoAcidGly][GlyH3NAmino]=false;

    IsHeavyAtom[AminoAcidHis][HisH1Beta]=false;
    IsHeavyAtom[AminoAcidHis][HisH2Beta]=false;
    IsHeavyAtom[AminoAcidHis][HisHCDelta]=false;
    IsHeavyAtom[AminoAcidHis][HisHNDelta]=false;
    IsHeavyAtom[AminoAcidHis][HisHNEpsilon]=false;
    IsHeavyAtom[AminoAcidHis][HisHCEpsilon]=false;
    IsHeavyAtom[AminoAcidHis][HisH3NAmino]=false;

    IsHeavyAtom[AminoAcidIle][IleH1C1Gamma]=false;
    IsHeavyAtom[AminoAcidIle][IleH2C1Gamma]=false;
    IsHeavyAtom[AminoAcidIle][IleH1C2Gamma]=false;
    IsHeavyAtom[AminoAcidIle][IleH2C2Gamma]=false;
    IsHeavyAtom[AminoAcidIle][IleH3C2Gamma]=false;
    IsHeavyAtom[AminoAcidIle][IleH1CDelta]=false;
    IsHeavyAtom[AminoAcidIle][IleH2CDelta]=false;
    IsHeavyAtom[AminoAcidIle][IleH3CDelta]=false;
    IsHeavyAtom[AminoAcidIle][IleH3NAmino]=false;

    IsHeavyAtom[AminoAcidLeu][LeuH1Beta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH2Beta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuHGamma]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH1C1Delta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH2C1Delta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH3C1Delta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH1C2Delta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH2C2Delta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH3C2Delta]=false;
    IsHeavyAtom[AminoAcidLeu][LeuH3NAmino]=false;

    IsHeavyAtom[AminoAcidLys][LysH1Beta]=false;
    IsHeavyAtom[AminoAcidLys][LysH2Beta]=false;
    IsHeavyAtom[AminoAcidLys][LysH1Gamma]=false;
    IsHeavyAtom[AminoAcidLys][LysH2Gamma]=false;
    IsHeavyAtom[AminoAcidLys][LysH1Delta]=false;
    IsHeavyAtom[AminoAcidLys][LysH2Delta]=false;
    IsHeavyAtom[AminoAcidLys][LysH1Epsilon]=false;
    IsHeavyAtom[AminoAcidLys][LysH2Epsilon]=false;
    IsHeavyAtom[AminoAcidLys][LysH1Zeta]=false;
    IsHeavyAtom[AminoAcidLys][LysH2Zeta]=false;
    IsHeavyAtom[AminoAcidLys][LysH3Zeta]=false;
    IsHeavyAtom[AminoAcidLys][LysH3NAmino]=false;

    IsHeavyAtom[AminoAcidMet][MetH1Beta]=false;
    IsHeavyAtom[AminoAcidMet][MetH2Beta]=false;
    IsHeavyAtom[AminoAcidMet][MetH1Gamma]=false;
    IsHeavyAtom[AminoAcidMet][MetH2Gamma]=false;
    IsHeavyAtom[AminoAcidMet][MetH1Epsilon]=false;
    IsHeavyAtom[AminoAcidMet][MetH2Epsilon]=false;
    IsHeavyAtom[AminoAcidMet][MetH3Epsilon]=false;
    IsHeavyAtom[AminoAcidMet][MetH3NAmino]=false;

    IsHeavyAtom[AminoAcidPhe][PheH1Beta]=false;
    IsHeavyAtom[AminoAcidPhe][PheH2Beta]=false;
    IsHeavyAtom[AminoAcidPhe][PheHC1Delta]=false;
    IsHeavyAtom[AminoAcidPhe][PheHC2Delta]=false;
    IsHeavyAtom[AminoAcidPhe][PheHCEpsilonC1Delta]=false;
    IsHeavyAtom[AminoAcidPhe][PheHCEpsilonC2Delta]=false;
    IsHeavyAtom[AminoAcidPhe][PheHCZeta]=false;
    IsHeavyAtom[AminoAcidPhe][PheH3NAmino]=false;

    IsHeavyAtom[AminoAcidPro][ProH1CBeta]=false;
    IsHeavyAtom[AminoAcidPro][ProH2CBeta]=false;
    IsHeavyAtom[AminoAcidPro][ProH1CGammaCBeta]=false;
    IsHeavyAtom[AminoAcidPro][ProH2CGammaCBeta]=false;
    IsHeavyAtom[AminoAcidPro][ProH1CGammaNAmino]=false;
    IsHeavyAtom[AminoAcidPro][ProH2CGammaNAmino]=false;

    IsHeavyAtom[AminoAcidSec][SecH1Beta]=false;
    IsHeavyAtom[AminoAcidSec][SecH2Beta]=false;
    IsHeavyAtom[AminoAcidSec][SecHGamma]=false;
    IsHeavyAtom[AminoAcidSec][SecH3NAmino]=false;

    IsHeavyAtom[AminoAcidSer][SerH1Beta]=false;
    IsHeavyAtom[AminoAcidSer][SerH2Beta]=false;
    IsHeavyAtom[AminoAcidSer][SerHGamma]=false;
    IsHeavyAtom[AminoAcidSer][SerH3NAmino]=false;

    IsHeavyAtom[AminoAcidThr][ThrHBeta]=false;
    IsHeavyAtom[AminoAcidThr][ThrHOGamma]=false;
    IsHeavyAtom[AminoAcidThr][ThrH1CGamma]=false;
    IsHeavyAtom[AminoAcidThr][ThrH2CGamma]=false;
    IsHeavyAtom[AminoAcidThr][ThrH3CGamma]=false;
    IsHeavyAtom[AminoAcidThr][ThrH3NAmino]=false;

    IsHeavyAtom[AminoAcidTrp][TrpH1Beta]=false;
    IsHeavyAtom[AminoAcidTrp][TrpH2Beta]=false;
    IsHeavyAtom[AminoAcidTrp][TrpHC1Delta]=false;
    IsHeavyAtom[AminoAcidTrp][TrpHNEpsilon]=false;
    IsHeavyAtom[AminoAcidTrp][TrpHC2Epsilon]=false;
    IsHeavyAtom[AminoAcidTrp][TrpHCZetaC1Epsilon]=false;
    IsHeavyAtom[AminoAcidTrp][TrpHCZetaC2Epsilon]=false;
    IsHeavyAtom[AminoAcidTrp][TrpHCEta]=false;
    IsHeavyAtom[AminoAcidTrp][TrpH3NAmino]=false;

    IsHeavyAtom[AminoAcidTyr][TyrH1Beta]=false;
    IsHeavyAtom[AminoAcidTyr][TyrH2Beta]=false;
    IsHeavyAtom[AminoAcidTyr][TyrHC1Delta]=false;
    IsHeavyAtom[AminoAcidTyr][TyrHC2Delta]=false;
    IsHeavyAtom[AminoAcidTyr][TyrHCEpsilonC1Delta]=false;
    IsHeavyAtom[AminoAcidTyr][TyrHCEpsilonC2Delta]=false;
    IsHeavyAtom[AminoAcidTyr][TyrHOEta]=false;
    IsHeavyAtom[AminoAcidTyr][TyrH3NAmino]=false;

    IsHeavyAtom[AminoAcidVal][ValHBeta]=false;
    IsHeavyAtom[AminoAcidVal][ValH1C1Gamma]=false;
    IsHeavyAtom[AminoAcidVal][ValH2C1Gamma]=false;
    IsHeavyAtom[AminoAcidVal][ValH3C1Gamma]=false;
    IsHeavyAtom[AminoAcidVal][ValH1C2Gamma]=false;
    IsHeavyAtom[AminoAcidVal][ValH2C2Gamma]=false;
    IsHeavyAtom[AminoAcidVal][ValH3C2Gamma]=false;
    IsHeavyAtom[AminoAcidVal][ValH3NAmino]=false;
  }

}

#include "data/structure/contact-map.h"

namespace std {

  enum AminoAcidBondNumbers {
    AminoAcidAlaNumberBonds=13,
    AminoAcidArgNumberBonds=27,
    AminoAcidAsnNumberBonds=17,
    AminoAcidAspNumberBonds=17,
    AminoAcidCysNumberBonds=14,
    AminoAcidGlnNumberBonds=20,
    AminoAcidGluNumberBonds=20,
    AminoAcidGlyNumberBonds=10,
    AminoAcidHisNumberBonds=22,
    AminoAcidIleNumberBonds=22,
    AminoAcidLeuNumberBonds=22,
    AminoAcidLysNumberBonds=25,
    AminoAcidMetNumberBonds=20,
    AminoAcidPheNumberBonds=24,
    AminoAcidProNumberBonds=17,
    AminoAcidSecNumberBonds=14,
    AminoAcidSerNumberBonds=14,
    AminoAcidThrNumberBonds=17,
    AminoAcidTrpNumberBonds=29,
    AminoAcidTyrNumberBonds=25,
    AminoAcidValNumberBonds=19
  };

  Vector<ContactMap> AminoAcidBonds;

  void InitAminoAcidBonds() {
    allocate(AminoAcidBonds,NumberAminoAcids);

    allocate(AminoAcidBonds[AminoAcidAla],AminoAcidAlaNumberBonds);
    Set(AminoAcidBonds[AminoAcidAla],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidAla],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidAla],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidAla],3,CAlpha,AlaCBeta);
    Set(AminoAcidBonds[AminoAcidAla],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidAla],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidAla],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidAla],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidAla],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidAla],9,NAmino,AlaH3NAmino);
    Set(AminoAcidBonds[AminoAcidAla],10,AlaCBeta,AlaH1Beta);
    Set(AminoAcidBonds[AminoAcidAla],11,AlaCBeta,AlaH2Beta);
    Set(AminoAcidBonds[AminoAcidAla],12,AlaCBeta,AlaH3Beta);

    allocate(AminoAcidBonds[AminoAcidArg],AminoAcidArgNumberBonds);
    Set(AminoAcidBonds[AminoAcidArg],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidArg],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidArg],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidArg],3,CAlpha,ArgCBeta);
    Set(AminoAcidBonds[AminoAcidArg],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidArg],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidArg],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidArg],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidArg],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidArg],9,NAmino,ArgH3NAmino);
    Set(AminoAcidBonds[AminoAcidArg],10,ArgCBeta,ArgCGamma);
    Set(AminoAcidBonds[AminoAcidArg],11,ArgCBeta,ArgH1Beta);
    Set(AminoAcidBonds[AminoAcidArg],12,ArgCBeta,ArgH2Beta);
    Set(AminoAcidBonds[AminoAcidArg],13,ArgCGamma,ArgCDelta);
    Set(AminoAcidBonds[AminoAcidArg],14,ArgCGamma,ArgH1Gamma);
    Set(AminoAcidBonds[AminoAcidArg],15,ArgCGamma,ArgH2Gamma);
    Set(AminoAcidBonds[AminoAcidArg],16,ArgCDelta,ArgNEpsilon);
    Set(AminoAcidBonds[AminoAcidArg],17,ArgCDelta,ArgH1Delta);
    Set(AminoAcidBonds[AminoAcidArg],18,ArgCDelta,ArgH2Delta);
    Set(AminoAcidBonds[AminoAcidArg],19,ArgNEpsilon,ArgCZeta);
    Set(AminoAcidBonds[AminoAcidArg],20,ArgNEpsilon,ArgHEpsilon);
    Set(AminoAcidBonds[AminoAcidArg],21,ArgCZeta,ArgN1Eta);
    Set(AminoAcidBonds[AminoAcidArg],22,ArgCZeta,ArgN2Eta);
    Set(AminoAcidBonds[AminoAcidArg],23,ArgN1Eta,ArgH1N1Eta);
    Set(AminoAcidBonds[AminoAcidArg],24,ArgN1Eta,ArgH2N1Eta);
    Set(AminoAcidBonds[AminoAcidArg],25,ArgN2Eta,ArgH1N2Eta);
    Set(AminoAcidBonds[AminoAcidArg],26,ArgN2Eta,ArgH2N2Eta);

    allocate(AminoAcidBonds[AminoAcidAsn],AminoAcidAsnNumberBonds);
    Set(AminoAcidBonds[AminoAcidAsn],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidAsn],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidAsn],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidAsn],3,CAlpha,AsnCBeta);
    Set(AminoAcidBonds[AminoAcidAsn],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidAsn],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidAsn],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidAsn],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidAsn],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidAsn],9,NAmino,AsnH3NAmino);
    Set(AminoAcidBonds[AminoAcidAsn],10,AsnCBeta,AsnCCarbonylGamma);
    Set(AminoAcidBonds[AminoAcidAsn],11,AsnCBeta,AsnH1Beta);
    Set(AminoAcidBonds[AminoAcidAsn],12,AsnCBeta,AsnH2Beta);
    Set(AminoAcidBonds[AminoAcidAsn],13,AsnCCarbonylGamma,AsnOCarbonylDelta);
    Set(AminoAcidBonds[AminoAcidAsn],14,AsnCCarbonylGamma,AsnNDelta);
    Set(AminoAcidBonds[AminoAcidAsn],15,AsnNDelta,AsnH1NDelta);
    Set(AminoAcidBonds[AminoAcidAsn],16,AsnNDelta,AsnH2NDelta);

    allocate(AminoAcidBonds[AminoAcidAsp],AminoAcidAspNumberBonds);
    Set(AminoAcidBonds[AminoAcidAsp],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidAsp],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidAsp],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidAsp],3,CAlpha,AspCBeta);
    Set(AminoAcidBonds[AminoAcidAsp],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidAsp],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidAsp],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidAsp],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidAsp],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidAsp],9,NAmino,AspH3NAmino);
    Set(AminoAcidBonds[AminoAcidAsp],10,AspCBeta,AspCCarbonylGamma);
    Set(AminoAcidBonds[AminoAcidAsp],11,AspCBeta,AspH1Beta);
    Set(AminoAcidBonds[AminoAcidAsp],12,AspCBeta,AspH2Beta);
    Set(AminoAcidBonds[AminoAcidAsp],13,AspCCarbonylGamma,AspO1Delta);
    Set(AminoAcidBonds[AminoAcidAsp],14,AspCCarbonylGamma,AspO2Delta);
    Set(AminoAcidBonds[AminoAcidAsp],15,AspO1Delta,AspHO1Delta);
    Set(AminoAcidBonds[AminoAcidAsp],16,AspO2Delta,AspHO2Delta);

    allocate(AminoAcidBonds[AminoAcidCys],AminoAcidCysNumberBonds);
    Set(AminoAcidBonds[AminoAcidCys],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidCys],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidCys],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidCys],3,CAlpha,CysCBeta);
    Set(AminoAcidBonds[AminoAcidCys],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidCys],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidCys],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidCys],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidCys],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidCys],9,NAmino,CysH3NAmino);
    Set(AminoAcidBonds[AminoAcidCys],10,CysCBeta,CysSGamma);
    Set(AminoAcidBonds[AminoAcidCys],11,CysCBeta,CysH1Beta);
    Set(AminoAcidBonds[AminoAcidCys],12,CysCBeta,CysH2Beta);
    Set(AminoAcidBonds[AminoAcidCys],13,CysSGamma,CysHGamma);

    allocate(AminoAcidBonds[AminoAcidGln],AminoAcidGlnNumberBonds);
    Set(AminoAcidBonds[AminoAcidGln],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidGln],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidGln],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidGln],3,CAlpha,GlnCBeta);
    Set(AminoAcidBonds[AminoAcidGln],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidGln],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidGln],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidGln],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidGln],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidGln],9,NAmino,GlnH3NAmino);
    Set(AminoAcidBonds[AminoAcidGln],10,GlnCBeta,GlnCGamma);
    Set(AminoAcidBonds[AminoAcidGln],11,GlnCBeta,GlnH1Beta);
    Set(AminoAcidBonds[AminoAcidGln],12,GlnCBeta,GlnH2Beta);
    Set(AminoAcidBonds[AminoAcidGln],13,GlnCGamma,GlnCCarbonylDelta);
    Set(AminoAcidBonds[AminoAcidGln],14,GlnCGamma,GlnH1Gamma);
    Set(AminoAcidBonds[AminoAcidGln],15,GlnCGamma,GlnH2Gamma);
    Set(AminoAcidBonds[AminoAcidGln],16,GlnCCarbonylDelta,GlnOCarbonylEpsilon);
    Set(AminoAcidBonds[AminoAcidGln],17,GlnCCarbonylDelta,GlnNEpsilon);
    Set(AminoAcidBonds[AminoAcidGln],18,GlnNEpsilon,GlnH1NEpsilon);
    Set(AminoAcidBonds[AminoAcidGln],19,GlnNEpsilon,GlnH2NEpsilon);

    allocate(AminoAcidBonds[AminoAcidGlu],AminoAcidGluNumberBonds);
    Set(AminoAcidBonds[AminoAcidGlu],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidGlu],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidGlu],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidGlu],3,CAlpha,GluCBeta);
    Set(AminoAcidBonds[AminoAcidGlu],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidGlu],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidGlu],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidGlu],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidGlu],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidGlu],9,NAmino,GluH3NAmino);
    Set(AminoAcidBonds[AminoAcidGlu],10,GluCBeta,GluCGamma);
    Set(AminoAcidBonds[AminoAcidGlu],11,GluCBeta,GluH1Beta);
    Set(AminoAcidBonds[AminoAcidGlu],12,GluCBeta,GluH2Beta);
    Set(AminoAcidBonds[AminoAcidGlu],13,GluCGamma,GluCCarbonylDelta);
    Set(AminoAcidBonds[AminoAcidGlu],14,GluCGamma,GluH1Gamma);
    Set(AminoAcidBonds[AminoAcidGlu],15,GluCGamma,GluH2Gamma);
    Set(AminoAcidBonds[AminoAcidGlu],16,GluCCarbonylDelta,GluO1Epsilon);
    Set(AminoAcidBonds[AminoAcidGlu],17,GluCCarbonylDelta,GluO2Epsilon);
    Set(AminoAcidBonds[AminoAcidGlu],18,GluO1Epsilon,GluHO1Epsilon);
    Set(AminoAcidBonds[AminoAcidGlu],19,GluO2Epsilon,GluHO2Epsilon);

    allocate(AminoAcidBonds[AminoAcidGly],AminoAcidGlyNumberBonds);
    Set(AminoAcidBonds[AminoAcidGly],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidGly],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidGly],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidGly],3,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidGly],4,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidGly],5,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidGly],6,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidGly],7,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidGly],8,NAmino,GlyH3NAmino);
    Set(AminoAcidBonds[AminoAcidGly],9,CAlpha,GlyH2Alpha);

    allocate(AminoAcidBonds[AminoAcidHis],AminoAcidHisNumberBonds);
    Set(AminoAcidBonds[AminoAcidHis],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidHis],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidHis],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidHis],3,CAlpha,HisCBeta);
    Set(AminoAcidBonds[AminoAcidHis],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidHis],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidHis],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidHis],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidHis],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidHis],9,NAmino,HisH3NAmino);
    Set(AminoAcidBonds[AminoAcidHis],10,HisCBeta,HisCRingGamma);
    Set(AminoAcidBonds[AminoAcidHis],11,HisCBeta,HisH1Beta);
    Set(AminoAcidBonds[AminoAcidHis],12,HisCBeta,HisH2Beta);
    Set(AminoAcidBonds[AminoAcidHis],13,HisCRingGamma,HisCRingDelta);
    Set(AminoAcidBonds[AminoAcidHis],14,HisCRingGamma,HisNRingDelta);
    Set(AminoAcidBonds[AminoAcidHis],15,HisCRingDelta,HisHCDelta);
    Set(AminoAcidBonds[AminoAcidHis],16,HisCRingDelta,HisNRingEpsilonCDelta);
    Set(AminoAcidBonds[AminoAcidHis],17,HisNRingDelta,HisHNDelta);
    Set(AminoAcidBonds[AminoAcidHis],18,HisNRingDelta,HisCRingEpsilonNDelta);
    Set(AminoAcidBonds[AminoAcidHis],19,HisCRingEpsilonNDelta,HisNRingEpsilonCDelta);
    Set(AminoAcidBonds[AminoAcidHis],20,HisCRingEpsilonNDelta,HisHCEpsilon);
    Set(AminoAcidBonds[AminoAcidHis],21,HisNRingEpsilonCDelta,HisHNEpsilon);

    allocate(AminoAcidBonds[AminoAcidIle],AminoAcidIleNumberBonds);
    Set(AminoAcidBonds[AminoAcidIle],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidIle],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidIle],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidIle],3,CAlpha,IleCBeta);
    Set(AminoAcidBonds[AminoAcidIle],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidIle],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidIle],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidIle],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidIle],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidIle],9,NAmino,IleH3NAmino);
    Set(AminoAcidBonds[AminoAcidIle],10,IleCBeta,IleC1Gamma);
    Set(AminoAcidBonds[AminoAcidIle],11,IleCBeta,IleC2Gamma);
    Set(AminoAcidBonds[AminoAcidIle],12,IleCBeta,IleHBeta);
    Set(AminoAcidBonds[AminoAcidIle],13,IleC1Gamma,IleCDeltaC1Gamma);
    Set(AminoAcidBonds[AminoAcidIle],14,IleC1Gamma,IleH1C1Gamma);
    Set(AminoAcidBonds[AminoAcidIle],15,IleC1Gamma,IleH2C1Gamma);
    Set(AminoAcidBonds[AminoAcidIle],16,IleC2Gamma,IleH1C2Gamma);
    Set(AminoAcidBonds[AminoAcidIle],17,IleC2Gamma,IleH2C2Gamma);
    Set(AminoAcidBonds[AminoAcidIle],18,IleC2Gamma,IleH3C2Gamma);
    Set(AminoAcidBonds[AminoAcidIle],19,IleCDeltaC1Gamma,IleH1CDelta);
    Set(AminoAcidBonds[AminoAcidIle],20,IleCDeltaC1Gamma,IleH2CDelta);
    Set(AminoAcidBonds[AminoAcidIle],21,IleCDeltaC1Gamma,IleH3CDelta);

    allocate(AminoAcidBonds[AminoAcidLeu],AminoAcidLeuNumberBonds);
    Set(AminoAcidBonds[AminoAcidLeu],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidLeu],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidLeu],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidLeu],3,CAlpha,LeuCBeta);
    Set(AminoAcidBonds[AminoAcidLeu],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidLeu],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidLeu],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidLeu],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidLeu],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidLeu],9,NAmino,LeuH3NAmino);
    Set(AminoAcidBonds[AminoAcidLeu],10,LeuCBeta,LeuCGamma);
    Set(AminoAcidBonds[AminoAcidLeu],11,LeuCBeta,LeuH1Beta);
    Set(AminoAcidBonds[AminoAcidLeu],12,LeuCBeta,LeuH2Beta);
    Set(AminoAcidBonds[AminoAcidLeu],13,LeuCGamma,LeuC1Delta);
    Set(AminoAcidBonds[AminoAcidLeu],14,LeuCGamma,LeuC2Delta);
    Set(AminoAcidBonds[AminoAcidLeu],15,LeuCGamma,LeuHGamma);
    Set(AminoAcidBonds[AminoAcidLeu],16,LeuC1Delta,LeuH1C1Delta);
    Set(AminoAcidBonds[AminoAcidLeu],17,LeuC1Delta,LeuH2C1Delta);
    Set(AminoAcidBonds[AminoAcidLeu],18,LeuC1Delta,LeuH3C1Delta);
    Set(AminoAcidBonds[AminoAcidLeu],19,LeuC2Delta,LeuH1C2Delta);
    Set(AminoAcidBonds[AminoAcidLeu],20,LeuC2Delta,LeuH2C2Delta);
    Set(AminoAcidBonds[AminoAcidLeu],21,LeuC2Delta,LeuH3C2Delta);

    allocate(AminoAcidBonds[AminoAcidLys],AminoAcidLysNumberBonds);
    Set(AminoAcidBonds[AminoAcidLys],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidLys],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidLys],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidLys],3,CAlpha,LysCBeta);
    Set(AminoAcidBonds[AminoAcidLys],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidLys],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidLys],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidLys],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidLys],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidLys],9,NAmino,LysH3NAmino);
    Set(AminoAcidBonds[AminoAcidLys],10,LysCBeta,LysCGamma);
    Set(AminoAcidBonds[AminoAcidLys],11,LysCBeta,LysH1Beta);
    Set(AminoAcidBonds[AminoAcidLys],12,LysCBeta,LysH2Beta);
    Set(AminoAcidBonds[AminoAcidLys],13,LysCGamma,LysCDelta);
    Set(AminoAcidBonds[AminoAcidLys],14,LysCGamma,LysH1Gamma);
    Set(AminoAcidBonds[AminoAcidLys],15,LysCGamma,LysH2Gamma);
    Set(AminoAcidBonds[AminoAcidLys],16,LysCDelta,LysCEpsilon);
    Set(AminoAcidBonds[AminoAcidLys],17,LysCDelta,LysH1Delta);
    Set(AminoAcidBonds[AminoAcidLys],18,LysCDelta,LysH2Delta);
    Set(AminoAcidBonds[AminoAcidLys],19,LysCEpsilon,LysNZeta);
    Set(AminoAcidBonds[AminoAcidLys],20,LysCEpsilon,LysH1Epsilon);
    Set(AminoAcidBonds[AminoAcidLys],21,LysCEpsilon,LysH2Epsilon);
    Set(AminoAcidBonds[AminoAcidLys],22,LysNZeta,LysH1Zeta);
    Set(AminoAcidBonds[AminoAcidLys],23,LysNZeta,LysH2Zeta);
    Set(AminoAcidBonds[AminoAcidLys],24,LysNZeta,LysH3Zeta);

    allocate(AminoAcidBonds[AminoAcidMet],AminoAcidMetNumberBonds);
    Set(AminoAcidBonds[AminoAcidMet],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidMet],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidMet],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidMet],3,CAlpha,MetCBeta);
    Set(AminoAcidBonds[AminoAcidMet],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidMet],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidMet],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidMet],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidMet],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidMet],9,NAmino,MetH3NAmino);
    Set(AminoAcidBonds[AminoAcidMet],10,MetCBeta,MetCGamma);
    Set(AminoAcidBonds[AminoAcidMet],11,MetCBeta,MetH1Beta);
    Set(AminoAcidBonds[AminoAcidMet],12,MetCBeta,MetH2Beta);
    Set(AminoAcidBonds[AminoAcidMet],13,MetCGamma,MetSDelta);
    Set(AminoAcidBonds[AminoAcidMet],14,MetCGamma,MetH1Gamma);
    Set(AminoAcidBonds[AminoAcidMet],15,MetCGamma,MetH2Gamma);
    Set(AminoAcidBonds[AminoAcidMet],16,MetSDelta,MetCEpsilon);
    Set(AminoAcidBonds[AminoAcidMet],17,MetCEpsilon,MetH1Epsilon);
    Set(AminoAcidBonds[AminoAcidMet],18,MetCEpsilon,MetH2Epsilon);
    Set(AminoAcidBonds[AminoAcidMet],19,MetCEpsilon,MetH3Epsilon);

    allocate(AminoAcidBonds[AminoAcidPhe],AminoAcidPheNumberBonds);
    Set(AminoAcidBonds[AminoAcidPhe],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidPhe],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidPhe],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidPhe],3,CAlpha,PheCBeta);
    Set(AminoAcidBonds[AminoAcidPhe],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidPhe],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidPhe],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidPhe],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidPhe],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidPhe],9,NAmino,PheH3NAmino);
    Set(AminoAcidBonds[AminoAcidPhe],10,PheCBeta,PheCRingGamma);
    Set(AminoAcidBonds[AminoAcidPhe],11,PheCBeta,PheH1Beta);
    Set(AminoAcidBonds[AminoAcidPhe],12,PheCBeta,PheH2Beta);
    Set(AminoAcidBonds[AminoAcidPhe],13,PheCRingGamma,PheC1RingDelta);
    Set(AminoAcidBonds[AminoAcidPhe],14,PheCRingGamma,PheC2RingDelta);
    Set(AminoAcidBonds[AminoAcidPhe],15,PheC1RingDelta,PheCRingEpsilonC1Delta);
    Set(AminoAcidBonds[AminoAcidPhe],16,PheC1RingDelta,PheHC1Delta);
    Set(AminoAcidBonds[AminoAcidPhe],17,PheC2RingDelta,PheCRingEpsilonC2Delta);
    Set(AminoAcidBonds[AminoAcidPhe],18,PheC2RingDelta,PheHC2Delta);
    Set(AminoAcidBonds[AminoAcidPhe],19,PheCRingEpsilonC1Delta,PheCRingZeta);
    Set(AminoAcidBonds[AminoAcidPhe],20,PheCRingEpsilonC1Delta,PheHC1Delta);
    Set(AminoAcidBonds[AminoAcidPhe],21,PheCRingEpsilonC2Delta,PheCRingZeta);
    Set(AminoAcidBonds[AminoAcidPhe],22,PheCRingEpsilonC2Delta,PheHC2Delta);
    Set(AminoAcidBonds[AminoAcidPhe],23,PheCRingZeta,PheHCZeta);

    allocate(AminoAcidBonds[AminoAcidPro],AminoAcidProNumberBonds);
    Set(AminoAcidBonds[AminoAcidPro],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidPro],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidPro],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidPro],3,CAlpha,ProCRingBeta);
    Set(AminoAcidBonds[AminoAcidPro],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidPro],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidPro],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidPro],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidPro],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidPro],9,ProCRingBeta,ProCRingGammaCBeta);
    Set(AminoAcidBonds[AminoAcidPro],10,ProCRingBeta,ProH1CBeta);
    Set(AminoAcidBonds[AminoAcidPro],11,ProCRingBeta,ProH2CBeta);
    Set(AminoAcidBonds[AminoAcidPro],12,ProCRingGammaNAmino,ProCRingGammaCBeta);
    Set(AminoAcidBonds[AminoAcidPro],13,ProCRingGammaNAmino,ProH1CGammaNAmino);
    Set(AminoAcidBonds[AminoAcidPro],14,ProCRingGammaNAmino,ProH2CGammaNAmino);
    Set(AminoAcidBonds[AminoAcidPro],15,ProCRingGammaCBeta,ProH1CGammaCBeta);
    Set(AminoAcidBonds[AminoAcidPro],16,ProCRingGammaCBeta,ProH2CGammaCBeta);

    allocate(AminoAcidBonds[AminoAcidSec],AminoAcidSecNumberBonds);
    Set(AminoAcidBonds[AminoAcidSec],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidSec],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidSec],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidSec],3,CAlpha,SecCBeta);
    Set(AminoAcidBonds[AminoAcidSec],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidSec],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidSec],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidSec],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidSec],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidSec],9,NAmino,SecH3NAmino);
    Set(AminoAcidBonds[AminoAcidSec],10,SecCBeta,SecSeGamma);
    Set(AminoAcidBonds[AminoAcidSec],11,SecCBeta,SecH1Beta);
    Set(AminoAcidBonds[AminoAcidSec],12,SecCBeta,SecH2Beta);
    Set(AminoAcidBonds[AminoAcidSec],13,SecSeGamma,SecHGamma);

    allocate(AminoAcidBonds[AminoAcidSer],AminoAcidSerNumberBonds);
    Set(AminoAcidBonds[AminoAcidSer],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidSer],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidSer],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidSer],3,CAlpha,SerCBeta);
    Set(AminoAcidBonds[AminoAcidSer],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidSer],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidSer],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidSer],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidSer],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidSer],9,NAmino,SerH3NAmino);
    Set(AminoAcidBonds[AminoAcidSer],10,SerCBeta,SerOGamma);
    Set(AminoAcidBonds[AminoAcidSer],11,SerCBeta,SerH1Beta);
    Set(AminoAcidBonds[AminoAcidSer],12,SerCBeta,SerH2Beta);
    Set(AminoAcidBonds[AminoAcidSer],13,SerOGamma,SerHGamma);

    allocate(AminoAcidBonds[AminoAcidThr],AminoAcidThrNumberBonds);
    Set(AminoAcidBonds[AminoAcidThr],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidThr],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidThr],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidThr],3,CAlpha,ThrCBeta);
    Set(AminoAcidBonds[AminoAcidThr],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidThr],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidThr],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidThr],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidThr],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidThr],9,NAmino,ThrH3NAmino);
    Set(AminoAcidBonds[AminoAcidThr],10,ThrCBeta,ThrOGamma);
    Set(AminoAcidBonds[AminoAcidThr],11,ThrCBeta,ThrCGamma);
    Set(AminoAcidBonds[AminoAcidThr],12,ThrCBeta,ThrHBeta);
    Set(AminoAcidBonds[AminoAcidThr],13,ThrOGamma,ThrHOGamma);
    Set(AminoAcidBonds[AminoAcidThr],14,ThrCGamma,ThrH1CGamma);
    Set(AminoAcidBonds[AminoAcidThr],15,ThrCGamma,ThrH2CGamma);
    Set(AminoAcidBonds[AminoAcidThr],16,ThrCGamma,ThrH3CGamma);

    allocate(AminoAcidBonds[AminoAcidTrp],AminoAcidTrpNumberBonds);
    Set(AminoAcidBonds[AminoAcidTrp],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidTrp],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidTrp],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidTrp],3,CAlpha,TrpCBeta);
    Set(AminoAcidBonds[AminoAcidTrp],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidTrp],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidTrp],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidTrp],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidTrp],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidTrp],9,NAmino,TrpH3NAmino);
    Set(AminoAcidBonds[AminoAcidTrp],10,TrpCBeta,TrpCGamma);
    Set(AminoAcidBonds[AminoAcidTrp],11,TrpCBeta,TrpH1Beta);
    Set(AminoAcidBonds[AminoAcidTrp],12,TrpCBeta,TrpH2Beta);
    Set(AminoAcidBonds[AminoAcidTrp],13,TrpCGamma,TrpC1Delta);
    Set(AminoAcidBonds[AminoAcidTrp],14,TrpCGamma,TrpC2Delta);
    Set(AminoAcidBonds[AminoAcidTrp],15,TrpC1Delta,TrpNEpsilonC1Delta);
    Set(AminoAcidBonds[AminoAcidTrp],16,TrpC1Delta,TrpHC1Delta);
    Set(AminoAcidBonds[AminoAcidTrp],17,TrpC2Delta,TrpC1EpsilonC2Delta);
    Set(AminoAcidBonds[AminoAcidTrp],18,TrpC2Delta,TrpC2EpsilonC2Delta);
    Set(AminoAcidBonds[AminoAcidTrp],19,TrpNEpsilonC1Delta,TrpC1EpsilonC2Delta);
    Set(AminoAcidBonds[AminoAcidTrp],20,TrpNEpsilonC1Delta,TrpHNEpsilon);
    Set(AminoAcidBonds[AminoAcidTrp],21,TrpC1EpsilonC2Delta,TrpCZetaC1Epsilon);
    Set(AminoAcidBonds[AminoAcidTrp],22,TrpC2EpsilonC2Delta,TrpCZetaC2Epsilon);
    Set(AminoAcidBonds[AminoAcidTrp],23,TrpC2EpsilonC2Delta,TrpHC2Epsilon);
    Set(AminoAcidBonds[AminoAcidTrp],24,TrpCZetaC1Epsilon,TrpCEta);
    Set(AminoAcidBonds[AminoAcidTrp],25,TrpCZetaC1Epsilon,TrpHCZetaC1Epsilon);
    Set(AminoAcidBonds[AminoAcidTrp],26,TrpCZetaC2Epsilon,TrpCEta);
    Set(AminoAcidBonds[AminoAcidTrp],27,TrpCZetaC2Epsilon,TrpHCZetaC2Epsilon);
    Set(AminoAcidBonds[AminoAcidTrp],28,TrpCEta,TrpHCEta);

    allocate(AminoAcidBonds[AminoAcidTyr],AminoAcidTyrNumberBonds);
    Set(AminoAcidBonds[AminoAcidTyr],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidTyr],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidTyr],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidTyr],3,CAlpha,TyrCBeta);
    Set(AminoAcidBonds[AminoAcidTyr],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidTyr],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidTyr],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidTyr],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidTyr],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidTyr],9,NAmino,TyrH3NAmino);
    Set(AminoAcidBonds[AminoAcidTyr],10,TyrCBeta,TyrCRingGamma);
    Set(AminoAcidBonds[AminoAcidTyr],11,TyrCBeta,TyrH1Beta);
    Set(AminoAcidBonds[AminoAcidTyr],12,TyrCBeta,TyrH2Beta);
    Set(AminoAcidBonds[AminoAcidTyr],13,TyrCRingGamma,TyrC1RingDelta);
    Set(AminoAcidBonds[AminoAcidTyr],14,TyrCRingGamma,TyrC2RingDelta);
    Set(AminoAcidBonds[AminoAcidTyr],15,TyrC1RingDelta,TyrCRingEpsilonC1Delta);
    Set(AminoAcidBonds[AminoAcidTyr],16,TyrC1RingDelta,TyrHC1Delta);
    Set(AminoAcidBonds[AminoAcidTyr],17,TyrC2RingDelta,TyrCRingEpsilonC2Delta);
    Set(AminoAcidBonds[AminoAcidTyr],18,TyrC2RingDelta,TyrHC2Delta);
    Set(AminoAcidBonds[AminoAcidTyr],19,TyrCRingEpsilonC1Delta,TyrCRingZeta);
    Set(AminoAcidBonds[AminoAcidTyr],20,TyrCRingEpsilonC1Delta,TyrHCEpsilonC1Delta);
    Set(AminoAcidBonds[AminoAcidTyr],21,TyrCRingEpsilonC2Delta,TyrCRingZeta);
    Set(AminoAcidBonds[AminoAcidTyr],22,TyrCRingEpsilonC2Delta,TyrHCEpsilonC2Delta);
    Set(AminoAcidBonds[AminoAcidTyr],23,TyrCRingZeta,TyrOEta);
    Set(AminoAcidBonds[AminoAcidTyr],24,TyrOEta,TyrHOEta);

    allocate(AminoAcidBonds[AminoAcidVal],AminoAcidValNumberBonds);
    Set(AminoAcidBonds[AminoAcidVal],0,CAlpha,CCarbonyl);
    Set(AminoAcidBonds[AminoAcidVal],1,CAlpha,NAmino);
    Set(AminoAcidBonds[AminoAcidVal],2,CAlpha,HAlpha);
    Set(AminoAcidBonds[AminoAcidVal],3,CAlpha,ValCBeta);
    Set(AminoAcidBonds[AminoAcidVal],4,CCarbonyl,OCarbonyl);
    Set(AminoAcidBonds[AminoAcidVal],5,CCarbonyl,OCarboxyl);
    Set(AminoAcidBonds[AminoAcidVal],6,OCarboxyl,HOCarboxyl);
    Set(AminoAcidBonds[AminoAcidVal],7,NAmino,H1NAmino);
    Set(AminoAcidBonds[AminoAcidVal],8,NAmino,H2NAmino);
    Set(AminoAcidBonds[AminoAcidVal],9,NAmino,ValH3NAmino);
    Set(AminoAcidBonds[AminoAcidVal],10,ValCBeta,ValC1Gamma);
    Set(AminoAcidBonds[AminoAcidVal],11,ValCBeta,ValC2Gamma);
    Set(AminoAcidBonds[AminoAcidVal],12,ValCBeta,ValHBeta);
    Set(AminoAcidBonds[AminoAcidVal],13,ValC1Gamma,ValH1C1Gamma);
    Set(AminoAcidBonds[AminoAcidVal],14,ValC1Gamma,ValH2C1Gamma);
    Set(AminoAcidBonds[AminoAcidVal],15,ValC1Gamma,ValH3C1Gamma);
    Set(AminoAcidBonds[AminoAcidVal],16,ValC2Gamma,ValH1C2Gamma);
    Set(AminoAcidBonds[AminoAcidVal],17,ValC2Gamma,ValH2C2Gamma);
    Set(AminoAcidBonds[AminoAcidVal],18,ValC2Gamma,ValH3C2Gamma);

    for(unsigned int i=0;i<NumberAminoAcids;++i)  AminoAcidBonds[i].update();

  }

}

#endif
