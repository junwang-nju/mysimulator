
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612Cut(Array1D<Unique64Bit>& prm) {
    T R0RC,R0RC6,R06,RC6,R0RC7;
    R06=Value<T>(prm[LJ612CutEqRadius]);
    RC6=Value<T>(prm[LJ612CutCutR]);
    R0RC=R06/RC6;
    R06*=R06*R06;    R06*=R06;
    RC6*=RC6;
    Value<T>(prm[LJ612CutCutRSQ])=RC6;
    RC6*=RC6*RC6;
    R0RC6=R06/RC6;
    R0RC7=R0RC6*R0RC;

    T Sigma6=R06*(1-R0RC7)/(1-R0RC6*R0RC7);

    T SGRC6,SGRC12;
    SGRC6=Sigma6/RC6;
    SGRC12=SGRC6*SGRC6;

    T VC=SGRC12-SGRC6*2;
    T KC=(SGRC6-SGRC12)/Value<T>(prm[LJ612CutCutR])*12;

    T SGR06,E;
    SGR06=Sigma6/R06;
    E=SGR06*(SGR06-2.);
    E-=VC;
    E-=KC*(Value<T>(prm[LJ612CutEqRadius])-Value<T>(prm[LJ612CutCutR]));
    E=-Value<T>(prm[LJ612CutEqEnergyDepth])/E;
    Value<T>(prm[LJ612CutFactorA])=E*Sigma6*Sigma6;
    Value<T>(prm[LJ612CutFactorB])=E*Sigma6*2;
    Value<T>(prm[LJ612CutDiffFactorA])=E*Sigma6*Sigma6*12;
    Value<T>(prm[LJ612CutDiffFactorB])=E*Sigma6*12;
    Value<T>(prm[LJ612CutVc])=VC*E;
    Value<T>(prm[LJ612CutKc])=KC*E;
  }

}

#endif

