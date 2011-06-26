
#ifndef _Propagator_Ensemble_Method_Name_H_
#define _Propagator_Ensemble_Method_Name_H_

namespace mysimulator {

  enum PropagatorEnsembleMethodName {
    ConstantE,
    Berendsen,
    Langevin,
    UnknownEnsemble,
    Microcanonical=ConstantE,
  };

}

#endif

