
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

#include "data/derived/parameter-list.h"

namespace std {

  enum AminoAcidBondNumbers {
    AminoAcidAlaNumberBonds=13,
    AminoAcidArgNumberBonds=27,
    AminoAcidAsnNumberBonds=17,
    AminoAcidAspNumberBonds=17,
    AminoAcidCysNumberBonds=14,
    AminoAcidGlnNumberBonds=20,
    AminoAcidGluNumberBonds=20,
    AminoAcidGlyNumberBonds=11,
    AminoAcidHisNumberBonds=22,
    AminoAcidIleNumberBonds=21,
    AminoAcidLeuNumberBonds=22,
    AminoAcidLysNumberBonds=25,
    AminoAcidMetNumberBonds=20,
    AminoAcidPheNumberBonds=24,
    AminoAcidProNumberBonds=18,
    AminoAcidSecNumberBonds=14,
    AminoAcidSerNumberBonds=14,
    AminoAcidThrNumberBonds=17,
    AminoAcidTrpNumberBonds=29,
    AminoAcidTyrNumberBonds=25,
    AminoAcidValNumberBonds=19
  };

  Vector<ParameterList> AminoAcidBonds;

  void InitAminoAcidBonds() {
    allocate(AminoAcidBonds,NumberAminoAcids);
    Vector<ParameterKey> key;
    allocate(AminoAcidBonds[AminoAcidAla],2,1,AminoAcidAlaNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidAla].key,AminoAcidBonds[AminoAcidAla].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=AlaCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=AlaH3NAmino;
    key[10][0]=AlaCBeta;    key[10][1]=AlaH1Beta;
    key[11][0]=AlaCBeta;    key[11][1]=AlaH2Beta;
    key[12][0]=AlaCBeta;    key[12][1]=AlaH3Beta;
    for(unsigned int i=0;i<AminoAcidAlaNumberBonds;++i) {
      key[i+AminoAcidAlaNumberBonds][0]=key[i][1];
      key[i+AminoAcidAlaNumberBonds][1]=key[i][0];
    }
    allocate(AminoAcidBonds[AminoAcidArg],2,1,AminoAcidArgNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidArg].key,AminoAcidBonds[AminoAcidArg].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=ArgCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=ArgH3NAmino;
    key[10][0]=ArgCBeta;    key[10][1]=ArgCGamma;
    key[11][0]=ArgCBeta;    key[11][1]=ArgH1Beta;
    key[12][0]=ArgCBeta;    key[12][1]=ArgH2Beta;
    key[13][0]=ArgCGamma;   key[13][1]=ArgCDelta;
    key[14][0]=ArgCGamma;   key[14][1]=ArgH1Gamma;
    key[15][0]=ArgCGamma;   key[15][1]=ArgH2Gamma;
    key[16][0]=ArgCDelta;   key[16][1]=ArgNEpsilon;
    key[17][0]=ArgCDelta;   key[17][1]=ArgH1Delta;
    key[18][0]=ArgCDelta;   key[18][0]=ArgH2Delta;
    key[19][0]=ArgNEpsilon; key[19][1]=ArgCZeta;
    key[20][0]=ArgNEpsilon; key[20][1]=ArgHEpsilon;
    key[21][0]=ArgCZeta;    key[21][1]=ArgN1Eta;
    key[22][0]=ArgCZeta;    key[22][1]=ArgN2Eta;
    key[23][0]=ArgN1Eta;    key[23][1]=ArgH1N1Eta;
    key[24][0]=ArgN1Eta;    key[24][1]=ArgH2N1Eta;
    key[25][0]=ArgN2Eta;    key[25][1]=ArgH1N2Eta;
    key[26][0]=ArgN2Eta;    key[26][1]=ArgH2N2Eta;
    for(unsigned int i=0;i<AminoAcidArgNumberBonds;++i) {
      key[i+AminoAcidArgNumberBonds][0]=key[i][1];
      key[i+AminoAcidArgNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidAsn],2,1,AminoAcidAsnNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidAsn].key,AminoAcidBonds[AminoAcidAsn].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=AsnCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=AsnH3NAmino;
    key[10][0]=AsnCBeta;    key[10][1]=AsnCCarbonylGamma;
    key[11][0]=AsnCBeta;    key[11][1]=AsnH1Beta;
    key[12][0]=AsnCBeta;    key[12][1]=AsnH2Beta;
    key[13][0]=AsnCCarbonylGamma;   key[13][1]=AsnOCarbonylDelta;
    key[14][0]=AsnCCarbonylGamma;   key[14][1]=AsnNDelta;
    key[15][0]=AsnNDelta;   key[15][1]=AsnH1NDelta;
    key[16][0]=AsnNDelta;   key[16][1]=AsnH2NDelta;
    for(unsigned int i=0;i<AminoAcidAsnNumberBonds;++i) {
      key[i+AminoAcidAsnNumberBonds][0]=key[i][1];
      key[i+AminoAcidAsnNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidAsp],2,1,AminoAcidAspNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidAsp].key,AminoAcidBonds[AminoAcidAsp].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=AspCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=AspH3NAmino;
    key[10][0]=AspCBeta;    key[10][1]=AspCCarbonylGamma;
    key[11][0]=AspCBeta;    key[11][1]=AspH1Beta;
    key[12][0]=AspCBeta;    key[12][1]=AspH2Beta;
    key[13][0]=AspCCarbonylGamma;   key[13][1]=AspO1Delta;
    key[14][0]=AspCCarbonylGamma;   key[14][1]=AspO2Delta;
    key[15][0]=AspO1Delta;  key[15][1]=AspHO1Delta;
    key[16][0]=AspO2Delta;  key[16][1]=AspHO2Delta;
    for(unsigned int i=0;i<AminoAcidAspNumberBonds;++i) {
      key[i+AminoAcidAspNumberBonds][0]=key[i][1];
      key[i+AminoAcidAspNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidCys],2,1,AminoAcidCysNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidCys].key,AminoAcidBonds[AminoAcidCys].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=CysCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=CysH3NAmino;
    key[10][0]=CysCBeta;    key[10][1]=CysSGamma;
    key[11][0]=CysCBeta;    key[11][1]=CysH1Beta;
    key[12][0]=CysCBeta;    key[12][1]=CysH2Beta;
    key[13][0]=CysSGamma;   key[13][1]=CysHGamma;
    for(unsigned int i=0;i<AminoAcidCysNumberBonds;++i) {
      key[i+AminoAcidCysNumberBonds][0]=key[i][1];
      key[i+AminoAcidCysNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidGln],2,1,AminoAcidGlnNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidGln].key,AminoAcidBonds[AminoAcidGln].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=GlnCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=GlnH3NAmino;
    key[10][0]=GlnCBeta;    key[10][1]=GlnCGamma;
    key[11][0]=GlnCBeta;    key[11][1]=GlnH1Beta;
    key[12][0]=GlnCBeta;    key[12][1]=GlnH2Beta;
    key[13][0]=GlnCGamma;   key[13][1]=GlnCCarbonylDelta;
    key[14][0]=GlnCGamma;   key[14][1]=GlnH1Gamma;
    key[15][0]=GlnCGamma;   key[15][1]=GlnH2Gamma;
    key[16][0]=GlnCCarbonylDelta;   key[16][1]=GlnOCarbonylEpsilon;
    key[17][0]=GlnCCarbonylDelta;   key[17][1]=GlnNEpsilon;
    key[18][0]=GlnNEpsilon; key[18][1]=GlnH1NEpsilon;
    key[19][0]=GlnNEpsilon; key[19][1]=GlnH2NEpsilon;
    for(unsigned int i=0;i<AminoAcidGlnNumberBonds;++i) {
      key[i+AminoAcidGlnNumberBonds][0]=key[i][1];
      key[i+AminoAcidGlnNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidGlu],2,1,AminoAcidGluNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidGlu].key,AminoAcidBonds[AminoAcidGlu].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=GluCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=GluH3NAmino;
    key[10][0]=GluCBeta;    key[10][1]=GluCGamma;
    key[11][0]=GluCBeta;    key[11][1]=GluH1Beta;
    key[12][0]=GluCBeta;    key[12][1]=GluH2Beta;
    key[13][0]=GluCGamma;   key[13][1]=GluCCarbonylDelta;
    key[14][0]=GluCGamma;   key[14][1]=GluH1Gamma;
    key[15][0]=GluCGamma;   key[15][1]=GluH2Gamma;
    key[16][0]=GluCCarbonylDelta;   key[16][1]=GluO1Epsilon;
    key[17][0]=GluCCarbonylDelta;   key[17][1]=GluO2Epsilon;
    key[18][0]=GluO1Epsilon;key[18][1]=GluHO1Epsilon;
    key[19][0]=GluO2Epsilon;key[19][1]=GluHO2Epsilon;
    for(unsigned int i=0;i<AminoAcidGluNumberBonds;++i) {
      key[i+AminoAcidGluNumberBonds][0]=key[i][1];
      key[i+AminoAcidGluNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidGly],2,1,AminoAcidGlyNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidGly].key,AminoAcidBonds[AminoAcidGly].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=GlyH3NAmino;
    key[10][0]=CAlpha;      key[10][1]=GlyH2Alpha;
    for(unsigned int i=0;i<AminoAcidGlyNumberBonds;++i) {
      key[i+AminoAcidGlyNumberBonds][0]=key[i][1];
      key[i+AminoAcidGlyNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidHis],2,1,AminoAcidHisNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidHis].key,AminoAcidBonds[AminoAcidHis].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=HisCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=HisH3NAmino;
    key[10][0]=HisCBeta;      key[10][1]=HisCRingGamma;
    key[11][0]=HisCBeta;      key[11][1]=HisH1Beta;
    key[12][0]=HisCBeta;      key[12][1]=HisH2Beta;
    key[13][0]=HisCRingGamma; key[13][1]=HisCRingDelta;
    key[14][0]=HisCRingGamma; key[14][1]=HisNRingDelta;
    key[15][0]=HisCRingDelta; key[15][1]=HisHCDelta;
    key[16][0]=HisCRingDelta; key[16][1]=HisNRingEpsilonCDelta;
    key[17][0]=HisNRingDelta; key[17][1]=HisHNDelta;
    key[18][0]=HisNRingDelta; key[18][1]=HisCRingEpsilonNDelta;
    key[19][0]=HisCRingEpsilonNDelta;   key[19][1]=HisNRingEpsilonCDelta;
    key[20][0]=HisCRingEpsilonNDelta;   key[20][1]=HisHCEpsilon;
    key[21][0]=HisNRingEpsilonCDelta;   key[21][1]=HisHNEpsilon;
    for(unsigned int i=0;i<AminoAcidHisNumberBonds;++i) {
      key[i+AminoAcidHisNumberBonds][0]=key[i][1];
      key[i+AminoAcidHisNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidIle],2,1,AminoAcidIleNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidIle].key,AminoAcidBonds[AminoAcidIle].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=IleCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=IleH3NAmino;
    key[10][0]=IleCBeta;      key[10][1]=IleC1Gamma;
    key[11][0]=IleCBeta;      key[11][1]=IleHBeta;
    key[12][0]=IleC1Gamma;    key[12][1]=IleCDeltaC1Gamma;
    key[13][0]=IleC1Gamma;    key[13][1]=IleH1C1Gamma;
    key[14][0]=IleC1Gamma;    key[14][1]=IleH2C1Gamma;
    key[15][0]=IleC2Gamma;    key[15][1]=IleH1C2Gamma;
    key[16][0]=IleC2Gamma;    key[16][1]=IleH2C2Gamma;
    key[17][0]=IleC2Gamma;    key[17][1]=IleH3C2Gamma;
    key[18][0]=IleCDeltaC1Gamma;    key[18][1]=IleH1CDelta;
    key[19][0]=IleCDeltaC1Gamma;    key[19][1]=IleH2CDelta;
    key[20][0]=IleCDeltaC1Gamma;    key[20][1]=IleH3CDelta;
    for(unsigned int i=0;i<AminoAcidIleNumberBonds;++i) {
      key[i+AminoAcidIleNumberBonds][0]=key[i][1];
      key[i+AminoAcidIleNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidLeu],2,1,AminoAcidLeuNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidLeu].key,AminoAcidBonds[AminoAcidLeu].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=LeuCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=LeuH3NAmino;
    key[10][0]=LeuCBeta;      key[10][1]=LeuCGamma;
    key[11][0]=LeuCBeta;      key[11][1]=LeuH1Beta;
    key[12][0]=LeuCBeta;      key[12][1]=LeuH2Beta;
    key[13][0]=LeuCGamma;     key[13][1]=LeuC1Delta;
    key[14][0]=LeuCGamma;     key[14][1]=LeuC2Delta;
    key[15][0]=LeuCGamma;     key[15][1]=LeuHGamma;
    key[16][0]=LeuC1Delta;    key[16][1]=LeuH1C1Delta;
    key[17][0]=LeuC1Delta;    key[17][1]=LeuH2C1Delta;
    key[18][0]=LeuC1Delta;    key[18][1]=LeuH3C1Delta;
    key[19][0]=LeuC2Delta;    key[19][1]=LeuH1C2Delta;
    key[20][0]=LeuC2Delta;    key[20][1]=LeuH2C2Delta;
    key[21][0]=LeuC2Delta;    key[21][1]=LeuH3C2Delta;
    for(unsigned int i=0;i<AminoAcidLeuNumberBonds;++i) {
      key[i+AminoAcidLeuNumberBonds][0]=key[i][1];
      key[i+AminoAcidLeuNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidLys],2,1,AminoAcidLysNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidLys].key,AminoAcidBonds[AminoAcidLys].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=LysCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=LysH3NAmino;
    key[10][0]=LysCBeta;      key[10][1]=LysCGamma;
    key[11][0]=LysCBeta;      key[11][1]=LysH1Beta;
    key[12][0]=LysCBeta;      key[12][1]=LysH2Beta;
    key[13][0]=LysCGamma;     key[13][1]=LysCDelta;
    key[14][0]=LysCGamma;     key[14][1]=LysH1Gamma;
    key[15][0]=LysCGamma;     key[15][1]=LysH2Gamma;
    key[16][0]=LysCDelta;     key[16][1]=LysCEpsilon;
    key[17][0]=LysCDelta;     key[17][1]=LysH1Delta;
    key[18][0]=LysCDelta;     key[18][1]=LysH2Delta;
    key[19][0]=LysCEpsilon;   key[19][1]=LysNZeta;
    key[20][0]=LysCEpsilon;   key[20][1]=LysH1Epsilon;
    key[21][0]=LysCEpsilon;   key[21][1]=LysH2Epsilon;
    key[22][0]=LysNZeta;      key[22][1]=LysH1Zeta;
    key[23][0]=LysNZeta;      key[23][1]=LysH2Zeta;
    key[24][0]=LysNZeta;      key[24][1]=LysH3Zeta;
    for(unsigned int i=0;i<AminoAcidLysNumberBonds;++i) {
      key[i+AminoAcidLysNumberBonds][0]=key[i][1];
      key[i+AminoAcidLysNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidMet],2,1,AminoAcidMetNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidMet].key,AminoAcidBonds[AminoAcidMet].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=MetCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=MetH3NAmino;
    key[10][0]=MetCBeta;      key[10][1]=MetCGamma;
    key[11][0]=MetCBeta;      key[11][1]=MetH1Beta;
    key[12][0]=MetCBeta;      key[12][1]=MetH2Beta;
    key[13][0]=MetCGamma;     key[13][1]=MetSDelta;
    key[14][0]=MetCGamma;     key[14][1]=MetH1Gamma;
    key[15][0]=MetCGamma;     key[15][1]=MetH2Gamma;
    key[16][0]=MetSDelta;     key[16][1]=MetCEpsilon;
    key[17][0]=MetCEpsilon;   key[17][1]=MetH1Epsilon;
    key[18][0]=MetCEpsilon;   key[18][1]=MetH2Epsilon;
    key[19][0]=MetCEpsilon;   key[19][1]=MetH3Epsilon;
    for(unsigned int i=0;i<AminoAcidMetNumberBonds;++i) {
      key[i+AminoAcidMetNumberBonds][0]=key[i][1];
      key[i+AminoAcidMetNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidPhe],2,1,AminoAcidPheNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidPhe].key,AminoAcidBonds[AminoAcidPhe].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=PheCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=PheH3NAmino;
    key[10][0]=PheCBeta;      key[10][1]=PheCRingGamma;
    key[11][0]=PheCBeta;      key[11][1]=PheH1Beta;
    key[12][0]=PheCBeta;      key[12][1]=PheH2Beta;
    key[13][0]=PheCRingGamma; key[13][1]=PheC1RingDelta;
    key[14][0]=PheCRingGamma; key[14][1]=PheC2RingDelta;
    key[15][0]=PheC1RingDelta;key[15][1]=PheCRingEpsilonC1Delta;
    key[16][0]=PheC1RingDelta;key[16][1]=PheHC1Delta;
    key[17][0]=PheC2RingDelta;key[17][1]=PheCRingEpsilonC2Delta;
    key[18][0]=PheC2RingDelta;key[18][1]=PheHC2Delta;
    key[19][0]=PheCRingEpsilonC1Delta;    key[19][1]=PheCRingZeta;
    key[20][0]=PheCRingEpsilonC1Delta;    key[20][1]=PheHC1Delta;
    key[21][0]=PheCRingEpsilonC2Delta;    key[21][1]=PheCRingZeta;
    key[22][0]=PheCRingEpsilonC2Delta;    key[22][1]=PheHC2Delta;
    key[23][0]=PheCRingZeta;  key[23][1]=PheHCZeta;
    for(unsigned int i=0;i<AminoAcidPheNumberBonds;++i) {
      key[i+AminoAcidPheNumberBonds][0]=key[i][1];
      key[i+AminoAcidPheNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidPro],2,1,AminoAcidProNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidPro].key,AminoAcidBonds[AminoAcidPro].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=ProCRingBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[10][0]=ProCRingBeta;  key[10][1]=ProCRingGammaCBeta;
    key[11][0]=ProCRingBeta;  key[11][1]=ProH1CBeta;
    key[12][0]=ProCRingBeta;  key[12][1]=ProH2CBeta;
    key[13][0]=ProCRingGammaNAmino;   key[13][0]=ProCRingGammaCBeta;
    key[14][0]=ProCRingGammaNAmino;   key[14][1]=ProH1CGammaNAmino;
    key[15][0]=ProCRingGammaNAmino;   key[15][1]=ProH2CGammaNAmino;
    key[16][0]=ProCRingGammaCBeta;    key[16][1]=ProH1CGammaCBeta;
    key[17][0]=ProCRingGammaCBeta;    key[17][1]=ProH2CGammaCBeta;
    for(unsigned int i=0;i<AminoAcidProNumberBonds;++i) {
      key[i+AminoAcidProNumberBonds][0]=key[i][1];
      key[i+AminoAcidProNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidSec],2,1,AminoAcidSecNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidSec].key,AminoAcidBonds[AminoAcidSec].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=SecCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=SecH3NAmino;
    key[10][0]=SecCBeta;    key[10][1]=SecSeGamma;
    key[11][0]=SecCBeta;    key[11][1]=SecH1Beta;
    key[12][0]=SecCBeta;    key[12][1]=SecH2Beta;
    key[13][0]=SecSeGamma;  key[13][1]=SecHGamma;
    for(unsigned int i=0;i<AminoAcidSecNumberBonds;++i) {
      key[i+AminoAcidSecNumberBonds][0]=key[i][1];
      key[i+AminoAcidSecNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidSer],2,1,AminoAcidSerNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidSer].key,AminoAcidBonds[AminoAcidSer].size);
    key[0][0]=CAlpha;       key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;       key[1][1]=NAmino;
    key[2][0]=CAlpha;       key[2][1]=HAlpha;
    key[3][0]=CAlpha;       key[3][1]=SerCBeta;
    key[4][0]=CCarbonyl;    key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;    key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;    key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;       key[7][1]=H1NAmino;
    key[8][0]=NAmino;       key[8][1]=H2NAmino;
    key[9][0]=NAmino;       key[9][1]=SerH3NAmino;
    key[10][0]=SerCBeta;    key[10][1]=SerOGamma;
    key[11][0]=SerCBeta;    key[11][1]=SerH1Beta;
    key[12][0]=SerCBeta;    key[12][1]=SerH2Beta;
    key[13][0]=SerOGamma;   key[13][1]=SerHGamma;
    for(unsigned int i=0;i<AminoAcidSerNumberBonds;++i) {
      key[i+AminoAcidSerNumberBonds][0]=key[i][1];
      key[i+AminoAcidSerNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidThr],2,1,AminoAcidThrNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidThr].key,AminoAcidBonds[AminoAcidThr].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=ThrCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=ThrH3NAmino;
    key[10][0]=ThrCBeta;      key[10][1]=ThrOGamma;
    key[11][0]=ThrCBeta;      key[11][1]=ThrCGamma;
    key[12][0]=ThrCBeta;      key[12][1]=ThrHBeta;
    key[13][0]=ThrOGamma;     key[13][1]=ThrHOGamma;
    key[14][0]=ThrCGamma;     key[14][1]=ThrH1CGamma;
    key[15][0]=ThrCGamma;     key[15][1]=ThrH2CGamma;
    key[16][0]=ThrCGamma;     key[16][1]=ThrH3CGamma;
    for(unsigned int i=0;i<AminoAcidThrNumberBonds;++i) {
      key[i+AminoAcidThrNumberBonds][0]=key[i][1];
      key[i+AminoAcidThrNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidTrp],2,1,AminoAcidTrpNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidTrp].key,AminoAcidBonds[AminoAcidTrp].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=TrpCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=TrpH3NAmino;
    key[10][0]=TrpCBeta;      key[10][1]=TrpCGamma;
    key[11][0]=TrpCBeta;      key[11][1]=TrpH1Beta;
    key[12][0]=TrpCBeta;      key[12][1]=TrpH2Beta;
    key[13][0]=TrpCGamma;     key[13][1]=TrpC1Delta;
    key[14][0]=TrpCGamma;     key[14][1]=TrpC2Delta;
    key[15][0]=TrpC1Delta;    key[15][1]=TrpNEpsilonC1Delta;
    key[16][0]=TrpC1Delta;    key[16][1]=TrpHC1Delta;
    key[17][0]=TrpC2Delta;    key[17][1]=TrpC1EpsilonC2Delta;
    key[18][0]=TrpC2Delta;    key[18][1]=TrpC2EpsilonC2Delta;
    key[19][0]=TrpNEpsilonC1Delta;    key[19][1]=TrpC1EpsilonC2Delta;
    key[20][0]=TrpNEpsilonC1Delta;    key[20][1]=TrpHNEpsilon;
    key[21][0]=TrpC1EpsilonC2Delta;   key[21][1]=TrpCZetaC1Epsilon;
    key[22][0]=TrpC2EpsilonC2Delta;   key[22][1]=TrpCZetaC2Epsilon;
    key[23][0]=TrpC2EpsilonC2Delta;   key[23][1]=TrpHC2Epsilon;
    key[24][0]=TrpCZetaC1Epsilon;     key[24][1]=TrpCEta;
    key[25][0]=TrpCZetaC1Epsilon;     key[25][1]=TrpHCZetaC1Epsilon;
    key[26][0]=TrpCZetaC2Epsilon;     key[26][1]=TrpCEta;
    key[27][0]=TrpCZetaC2Epsilon;     key[27][1]=TrpHCZetaC2Epsilon;
    key[28][0]=TrpCEta;       key[28][1]=TrpHCEta;
    for(unsigned int i=0;i<AminoAcidTrpNumberBonds;++i) {
      key[i+AminoAcidTrpNumberBonds][0]=key[i][1];
      key[i+AminoAcidTrpNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidTyr],2,1,AminoAcidTyrNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidTyr].key,AminoAcidBonds[AminoAcidTyr].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=TyrCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=TyrH3NAmino;
    key[10][0]=TyrCBeta;      key[10][1]=TyrCRingGamma;
    key[11][0]=TyrCBeta;      key[11][1]=TyrH1Beta;
    key[12][0]=TyrCBeta;      key[12][1]=TyrH2Beta;
    key[13][0]=TyrCRingGamma; key[13][1]=TyrC1RingDelta;
    key[14][0]=TyrCRingGamma; key[14][1]=TyrC2RingDelta;
    key[15][0]=TyrC1RingDelta;key[15][1]=TyrCRingEpsilonC1Delta;
    key[16][0]=TyrC1RingDelta;key[16][1]=TyrHC1Delta;
    key[17][0]=TyrC2RingDelta;key[17][1]=TyrCRingEpsilonC2Delta;
    key[18][0]=TyrC2RingDelta;key[18][1]=TyrHC2Delta;
    key[19][0]=TyrCRingEpsilonC1Delta;    key[19][1]=TyrCRingZeta;
    key[20][0]=TyrCRingEpsilonC1Delta;    key[19][1]=TyrHCEpsilonC1Delta;
    key[21][0]=TyrCRingEpsilonC2Delta;    key[19][1]=TyrCRingZeta;
    key[22][0]=TyrCRingEpsilonC2Delta;    key[19][1]=TyrHCEpsilonC2Delta;
    key[23][0]=TyrCRingZeta;  key[23][1]=TyrOEta;
    key[24][0]=TyrOEta;       key[24][1]=TyrHOEta;
    for(unsigned int i=0;i<AminoAcidTyrNumberBonds;++i) {
      key[i+AminoAcidTyrNumberBonds][0]=key[i][1];
      key[i+AminoAcidTyrNumberBonds][1]=key[i][0];
    }

    allocate(AminoAcidBonds[AminoAcidVal],2,1,AminoAcidValNumberBonds*2);
    refer(key,
          AminoAcidBonds[AminoAcidVal].key,AminoAcidBonds[AminoAcidVal].size);
    key[0][0]=CAlpha;         key[0][1]=CCarbonyl;
    key[1][0]=CAlpha;         key[1][1]=NAmino;
    key[2][0]=CAlpha;         key[2][1]=HAlpha;
    key[3][0]=CAlpha;         key[3][1]=ValCBeta;
    key[4][0]=CCarbonyl;      key[4][1]=OCarbonyl;
    key[5][0]=CCarbonyl;      key[5][1]=OCarboxyl;
    key[6][0]=OCarboxyl;      key[6][1]=HOCarboxyl;
    key[7][0]=NAmino;         key[7][1]=H1NAmino;
    key[8][0]=NAmino;         key[8][1]=H2NAmino;
    key[9][0]=NAmino;         key[9][1]=ValH3NAmino;
    key[10][0]=ValCBeta;      key[10][1]=ValC1Gamma;
    key[11][0]=ValCBeta;      key[11][1]=ValC2Gamma;
    key[12][0]=ValCBeta;      key[12][1]=ValHBeta;
    key[13][0]=ValC1Gamma;    key[13][1]=ValH1C1Gamma;
    key[14][0]=ValC1Gamma;    key[14][1]=ValH2C1Gamma;
    key[15][0]=ValC1Gamma;    key[15][1]=ValH3C1Gamma;
    key[16][0]=ValC2Gamma;    key[16][1]=ValH1C2Gamma;
    key[17][0]=ValC2Gamma;    key[17][1]=ValH2C2Gamma;
    key[18][0]=ValC2Gamma;    key[18][1]=ValH3C2Gamma;
    for(unsigned int i=0;i<AminoAcidValNumberBonds;++i) {
      key[i+AminoAcidValNumberBonds][0]=key[i][1];
      key[i+AminoAcidValNumberBonds][1]=key[i][0];
    }

    for(unsigned int i=0;i<NumberAminoAcids;++i)  AminoAcidBonds[i].update();

  }

}

#endif
