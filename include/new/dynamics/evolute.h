
#ifndef _Dynamics_Evolute_H_
#define _Dynamics_Evolute_H_

#include "dynamics/interface.h"
#include "dynamics/output/base/interface.h"

namespace mysimulator {

  template <DynamicsModeName DMN, typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            typename OC>
  void evolute(Dynamics<DMN,T,VT,OC>& D, System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(D)&&IsValid(S));
    assert(IsMatch(D,S));
    unsigned int nout=
      static_cast<unsigned int>(D.RunPeriod/D.Output.TimeBwOutput);
    if(D.Output.IsFirstOutput)  { D.Output.write(); D.Output.OS<<Endl; }
    for(unsigned int n=0;n<nout;++n) {
      for(unsigned int i=0;i<D.Output.NumStepsBwOutput;++i) S.evolute();
      D.Output.write();
      D.Output.OS<<Endl;
    }
  }

}

#endif

