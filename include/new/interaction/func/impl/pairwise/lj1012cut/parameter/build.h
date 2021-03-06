
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Paramete_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Paramete_Build_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "unique/64bit/copy.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012Cut(Unique64Bit* prm) {
    T R0RC,R0RC2,R0RC10,R0RC12,R02,RC2;
    R02=prm[LJ1012CutEqRadius].value<T>();
    RC2=prm[LJ1012CutCutR].value<T>();
    R0RC=R02/RC2;
    R02*=R02;
    RC2*=RC2;
    copy(prm[LJ1012CutCutRSQ],RC2);
    R0RC2=R02/RC2;
    R0RC10=R0RC2*R0RC2;
    R0RC10*=R0RC10;
    R0RC10*=R0RC2;
    R0RC12=R0RC10*R0RC2;

    T Sigma2=R02*(R0RC10*R0RC-1)/(R0RC12*R0RC-1);
    T SGRC2,SGRC10,SGRC12;
    SGRC2=Sigma2/RC2;
    SGRC10=SGRC2*SGRC2;
    SGRC10*=SGRC10;
    SGRC10*=SGRC2;
    SGRC12=SGRC10*SGRC2;
    T VC=5*(SGRC12-SGRC10)-SGRC10;
    T KC=60*(SGRC10-SGRC12)/prm[LJ1012CutCutR].value<T>();

    T SGR010,SGR012;
    SGR010=SGRC10/R0RC10;
    SGR012=SGRC12/R0RC12;
    T E;
    E=5*(SGR012-SGR010)-SGR010;
    E-=VC;
    E-=KC*(prm[LJ1012CutEqRadius].value<T>()-prm[LJ1012CutCutR].value<T>());
    E=-prm[LJ1012CutEqEnergyDepth].value<T>()/E;

    T Sigma10=Sigma2*Sigma2;
    Sigma10*=Sigma10;
    Sigma10*=Sigma2;
    Sigma10*=E;
    copy(prm[LJ1012CutFactorA],Sigma10*Sigma2*5);
    copy(prm[LJ1012CutFactorB],Sigma10*6);
    Sigma10*=60;
    copy(prm[LJ1012CutDiffFactorA],Sigma10*Sigma2);
    copy(prm[LJ1012CutDiffFactorB],Sigma10);
    copy(prm[LJ1012CutVc],VC*E);
    copy(prm[LJ1012CutKc],KC*E);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012Cut(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>LJ1012CutNumberParameter);
    BuildParameterLJ1012Cut<T>(prm.start);
  }

}

#endif

