
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "unique/64bit/copy.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612Cut(Unique64Bit* prm) {
    T R0RC,R0RC6,R06,RC6,R0RC7;
    R06=prm[LJ612CutEqRadius].value<T>();
    RC6=prm[LJ612CutCutR].value<T>();
    R0RC=R06/RC6;
    R06*=R06*R06;    R06*=R06;
    RC6*=RC6;
    copy(prm[LJ612CutCutRSQ],RC6);
    RC6*=RC6*RC6;
    R0RC6=R06/RC6;
    R0RC7=R0RC6*R0RC;

    T Sigma6=R06*(1-R0RC7)/(1-R0RC6*R0RC7);

    T SGRC6,SGRC12;
    SGRC6=Sigma6/RC6;
    SGRC12=SGRC6*SGRC6;

    T VC=SGRC12-SGRC6*2;
    T KC=(SGRC6-SGRC12)/prm[LJ612CutCutR].value<T>()*12;

    T SGR06,E;
    SGR06=Sigma6/R06;
    E=SGR06*(SGR06-2.);
    E-=VC;
    E-=KC*(prm[LJ612CutEqRadius].value<T>()-prm[LJ612CutCutR].value<T>());
    E=-prm[LJ612CutEqEnergyDepth].value<T>()/E;
    copy(prm[LJ612CutFactorA],E*Sigma6*Sigma6);
    copy(prm[LJ612CutFactorB],E*Sigma6*2);
    copy(prm[LJ612CutDiffFactorA],E*Sigma6*Sigma6*12);
    copy(prm[LJ612CutDiffFactorB],E*Sigma6*12);
    copy(prm[LJ612CutVc],VC*E);
    copy(prm[LJ612CutKc],KC*E);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612Cut(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=LJ612CutNumberParameters);
    BuildParameterLJ612Cut<T>(prm.start);
  }

}

#endif

