
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612Cut(Array1D<Unique64Bit>& prm) {
    T R0RC,R0RC6,R06,RC6,R0RC7;
    R06=prm[LJ612CutEqRadius].value<T>();
    RC6=prm[LJ612CutCutR].value<T>();
    R0RC=R06/RC6;
    R06*=R06*R06;    R06*=R06;
    RC6*=RC6;
    prm[LJ612CutCutRSQ].value<T>()=RC6;
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
    prm[LJ612CutFactorA].value<T>()=E*Sigma6*Sigma6;
    prm[LJ612CutFactorB].value<T>()=E*Sigma6*2;
    prm[LJ612CutDiffFactorA].value<T>()=E*Sigma6*Sigma6*12;
    prm[LJ612CutDiffFactorB].value<T>()=E*Sigma6*12;
    prm[LJ612CutVc].value<T>()=VC*E;
    prm[LJ612CutKc].value<T>()=KC*E;
  }

}

#endif

