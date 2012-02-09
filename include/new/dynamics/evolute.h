
#ifndef _Dynamics_Evolute_H_
#define _Dynamics_Evolute_H_

#include "dynamics/interface.h"

namespace mysimulator {

  template <DynamicsModeName DN,typename T,typename IDT,typename PT,
            typename GT,typename OCT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void evolute(Dynamics<DN,T,VT,OCT>& D, System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(D)&&IsValid(S));
    assert(IsMatch(D,S));
    assert(D.BindFlag);
    unsigned int nout;
    nout=static_cast<unsigned int>(D.RunPeriod/D.Output.TimeBwOutput);
    D.NowTime=D.StartTime;
    if(D.Output.IsFirstOutput) { D.Output.write(); D.Output.OS<<Endl; }
    for(unsigned int i=0;i<nout;++i) {
      for(unsigned int k=0;k<D.Output.NumStepsBwOutput;++k) S.evolute();
      D.updateNowTime(D.Output.TimeBwOutput);
      D.Output.write();
      D.Output.OS<<Endl;
    }
  }

}

#endif

