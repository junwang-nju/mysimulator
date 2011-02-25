
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
    AminoAcidR=AminoAcidArg
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
    AminoAcidV=AminoAcidVal
  };

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
    AminoAcidNumberCommonAtoms
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
    GlyH2Alpha,
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
    TrpHC1Gamma,
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

  static PropertyList<bool> IsHeavyAtom;

  void InitHeavyAtomProperty() {
    if(!IsAvailable(AminoAcidNumberAtoms))  InitAminoAcidNumberAtoms();
    allocate(IsHeavyAtom,AminoAcidNumberAtoms);
    copy(IsHeavyAtom,true);
    for(unsigned int i=0;i<NumberAminoAcids,++i) {
      IsHeavyAtom[i][HAlpha]=false;
      IsHeavyAtom[i][HOCarboxyl]=false;
      IsHeavyAtom[i][H1NAmino]=false;
      IsHeavyAtom[i][H2NAmino]=false;
    }
  }

}

#endif
