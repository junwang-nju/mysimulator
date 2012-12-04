
#ifndef _System_Interaction_Parameter_Pairwise_LJ612Cut_Build_H_
#define _System_Interaction_Parameter_Pairwise_LJ612Cut_Build_H_

#include "system/interaction/parameter/pairwise/lj612cut/name.h"
#include "array/interface.h"

namespace mysimulator {

  void _build_pair_lj612cut(Array<Double>& _FParam, Array<Int>&) {
    assert((bool)_FParam);
    assert(_FParam.size()>=PairLJ612CutParameterName::NumberParameter);
    double R0RC, R0RC6, R06, RC6, R0RC7;
    R06=_FParam[PairLJ612CutParameterName::EqRadius];
    RC6=_FParam[PairLJ612CutParameterName::CutR];
    assert(RC6>R06);
    R0RC=R06/RC6;
    R06*=R06*R06; R06*=R06;
    RC6*=RC6;
    _FParam[PairLJ612CutParameterName::CutRSQ]=RC6;
    RC6*=RC6*RC6;
    R0RC6=R06/RC6;
    R0RC7=R0RC6*R0RC;
    double Sigma6=R06*(1-R0RC7)/(1-R0RC6*R0RC7);
    double SGRC6=Sigma6/RC6;
    double SGRC12=SGRC6*SGRC6;
    double VC=SGRC12-SGRC6-SGRC6;
    double KC=(SGRC6-SGRC12)/_FParam[PairLJ612CutParameterName::CutR]*12;
    double SGR06=Sigma6/R06;
    double E=SGR06*(SGR06-2.);
    E-=VC;
    E-=KC*(_FParam[PairLJ612CutParameterName::EqRadius]-
           _FParam[PairLJ612CutParameterName::CutR]);
    E=-_FParam[PairLJ612CutParameterName::EqEnergyDepth]/E;
    double A=E*Sigma6;
    double B=A*2;
    A*=Sigma6;
    _FParam[PairLJ612CutParameterName::FactorA]=A;
    _FParam[PairLJ612CutParameterName::FactorB]=B;
    _FParam[PairLJ612CutParameterName::DFactorA]=12*A;
    _FParam[PairLJ612CutParameterName::DFactorB]=6*B;
    _FParam[PairLJ612CutParameterName::Vc]=VC*E;
    _FParam[PairLJ612CutParameterName::Kc]=KC*E;
  }

}

#endif

