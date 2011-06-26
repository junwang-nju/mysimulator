
#ifndef _Propagator_Ensemble_Name_H_
#define _Propagator_Ensemble_Name_H_

namespace mysimulator {

  enum PropagatorEnsembleName {
    ConstantE,
    BerendsenThermo,
    LangevinThermo,
    UnknownEnsemble,
    Microscanonical=ConstantE
  };

}

#endif

