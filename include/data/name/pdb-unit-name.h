
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
    IsHeavyAtom[AminoAcidTrp][TrpHC1Gamma]=false;
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

  Vector<ParameterList> AminoAcidBonds;

  void InitAminoAcidBonds() {
    allocate(AminoAcidBonds,NumberAminoAcids);
  }

}

#endif
