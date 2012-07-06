
#ifndef _Propagator_Name_H_
#define _Propagator_Name_H_

namespace mysimulator {

  enum PropagatorName {
    MolecularDynamics = 0,
    SteepestDescentMinimizer,
    ConjugateGradientMinimizer,
    NumberPropagator,
    UnknownPropagator
  };

}

#endif

