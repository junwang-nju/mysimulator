
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
    NumberAminoAcid,
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
    CBeta=AminoAcidNumberCommonAtoms,
    H1Beta,
    H2Beta,
    H3Beta,
    H3Amino,
    AminoAcidAlaNumberAtoms
  };

  enum AminoAcidArgAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CGamma,
    CDelta,
    NEpsilon,
    CZeta,
    N1Eta,
    N2Eta,
    H1Beta,
    H2Beta,
    H1Gamma,
    H2Gamma,
    H1Delta,
    H2Delta,
    HEpsilon,
    H1N1Eta,
    H2N1Eta,
    H1N2Eta,
    H2N2Eta,
    H3Amino,
    AminoAcidArgNumberAtoms
  };

  enum AminoAcidAsnAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CCarbonylGamma,
    OCarbonylDelta,
    NDelta,
    H1Beta,
    H2Beta,
    H1NDelta,
    H2NDelta,
    H3Amino,
    AminoAcidAsnNumberAtoms
  };

  enum AminoAcidAspAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CCarbonylGamma,
    O1Delta,
    O2Delta,
    H1Beta,
    H2Beta,
    HO1Delta,
    HO2Delta,
    H3Amino,
    AminoAcidAspNumberAtoms
  };

  enum AminoAcidCysAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    SGamma,
    H1Beta,
    H2Beta,
    HGamma,
    H3Amino,
    AminoAcidCysNumberAtoms
  };
  
  enum AminoAcidGlnAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CGamma,
    CCarbonylDelta,
    OCarbonylEpsilon,
    NEpsilon,
    H1Beta,
    H2Beta,
    H1Gamma,
    H2Gamma,
    H1NEpsilon,
    H2NEpsilon,
    H3Amino,
    AminoAcidGlnNumberAtoms
  };
  
  enum AminoAcidGluAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CGamma,
    CCarbonylDelta,
    O1Epsilon,
    O2Epsilon,
    H1Beta,
    H2Beta,
    H1Gamma,
    H2Gamma,
    HO1Epsilon,
    HO2Epsilon,
    H3Amino,
    AminoAcidGluNumberAtoms
  };
  
  enum AminoAcidGlyAtomName {
    H2Alpha,
    H3Amino,
    AminoAcidGlyNumberAtoms
  };
  
  enum AminoAcidHisAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CRingGamma,
    CRingDelta,
    NRingDelta,
    NRingEpsilonCDelta,
    CRingEpsilonNDelta,
    H1Beta,
    H2Beta,
    HCDelta,
    HNDelta,
    HNEpsilon,
    HCEpsilon,
    H3Amino,
    AminoAcidHisNumberAtoms
  };
  
  enum AminoAcidIleAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    C1Gamma,
    C2Gamma,
    CDeltaC1Gamma,
    HBeta,
    H1C1Gamma,
    H2C1Gamma,
    H1C2Gamma,
    H2C2Gamma,
    H3C2Gamma,
    H1CDelta,
    H2CDelta,
    H3CDelta,
    H3Amino,
    AminoAcidIleNumberAtoms
  };
  
  enum AminoAcidLeuAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CGamma,
    C1Delta,
    C2Delta,
    H1Beta,
    H2Beta,
    HGamma,
    H1C1Delta,
    H2C1Delta,
    H3C1Delta,
    H1C2Delta,
    H2C2Delta,
    H3C2Delta,
    H3Amino,
    AminoAcidLeuNumberAtoms
  };
  
  enum AminoAcidLysAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CGamma,
    CDelta,
    CEpsilon,
    NZeta,
    H1Beta,
    H2Beta,
    H1Gamma,
    H2Gamma,
    H1Delta,
    H2Delta,
    H1Epsilon,
    H2Epsilon,
    H1Zeta,
    H2Zeta,
    H3Zeta,
    H3Amino,
    AminoAcidLysNumberAtoms
  };
  
  enum AminoAcidMetAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CGamma,
    SDelta,
    CEpsilon,
    H1Beta,
    H2Beta,
    H1Gamma,
    H2Gamma,
    H1Epsilon,
    H2Epsilon,
    H3Epsilon,
    H3Amino,
    AminoAcidMetNumberAtoms
  };
  
  enum AminoAcidPheAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    CRingGamma,
    C1RingDelta,
    C2RingDelta,
    CRingEpsilonC1Delta,
    CRingEpsilonC2Delta,
    CRingZeta,
    H1Beta,
    H2Beta,
    HC1Delta,
    HC2Delta,
    HCEpsilonC1Delta,
    HCEpsilonC2Delta,
    HCZeta,
    H3Amino,
    AminoAcidPheNumberAtoms
  };
  
  enum AminoAcidProAtomName {
    CRingBeta=AminoAcidNumberCommonAtoms,
    CRingGammaCBeta,
    CRingGammaNAmino,
    H1CBeta,
    H2CBeta,
    H1CGammaCBeta,
    H2CGammaCBeta,
    H1CGammaNAmino,
    H2CGammaNAmino,
    AminoAcidProNumberAtoms,
    NRingBeta=NAmino,
    H1NBeta=H1NAmino,
    H2NBeta=H2NAmino,
    CRingGammaNBeta=CRingGammaNAmino,
    H1CGammaNBeta=H1CGammaNAmino,
    H2CGammaNBeta=H2CGammaNAmino
  };
  
  enum AminoAcidSecAtomName {
    CBeta=AminoAcidNumberCommonAtoms,
    SeGamma,
    H1Beta,
    H2Beta,
    HGamma,
    H3Amino,
    AminoAcidSecNumberAtoms
  };
  
  enum AminoAcidSerAtomName {
    AminoAcidSerNumberAtoms
  };
  
  enum AminoAcidThrAtomName {
    AminoAcidThrNumberAtoms
  };
  
  enum AminoAcidTrpAtomName {
    AminoAcidTrpNumberAtoms
  };
  
  enum AminoAcidTyrAtomName {
    AminoAcidTyrNumberAtoms
  };
  
  enum AminoAcidValAtomName {
    AminoAcidValNumberAtoms
  };

  static Vector<unsigned int> AminoAcidNumberAtoms;
  
  void InitAminoAcidNumberAtoms() {
    allocate(AminoAcidNumberAtoms,NumberAminoAcid);
    AminoAcidNumberAtoms[AminoAcidAla]=14;
    AminoAcidNumberAtoms[AminoAcidArg]=27;
    AminoAcidNumberAtoms[AminoAcidAsn]=18;
    AminoAcidNumberAtoms[AminoAcidAsp]=17;
    AminoAcidNumberAtoms[AminoAcidCys]=16;
    AminoAcidNumberAtoms[AminoAcidGln]=21;
    AminoAcidNumberAtoms[AminoAcidGlu]=20;
    AminoAcidNumberAtoms[AminoAcidGly]=11;
    AminoAcidNumberAtoms[AminoAcidHis]=22;
    AminoAcidNumberAtoms[AminoAcidIle]=23;
    AminoAcidNumberAtoms[AminoAcidLeu]=23;
    AminoAcidNumberAtoms[AminoAcidLys]=26;
    AminoAcidNumberAtoms[AminoAcidMet]=21;
    AminoAcidNumberAtoms[AminoAcidPhe]=24;
    AminoAcidNumberAtoms[AminoAcidPro]=18;
    AminoAcidNumberAtoms[AminoAcidSec]=15;
    AminoAcidNumberAtoms[AminoAcidSer]=15;
    AminoAcidNumberAtoms[AminoAcidThr]=18;
    AminoAcidNumberAtoms[AminoAcidTrp]=28;
    AminoAcidNumberAtoms[AminoAcidTyr]=25;
    AminoAcidNumberAtoms[AminoAcidVal]=20;
  }

}

#endif
