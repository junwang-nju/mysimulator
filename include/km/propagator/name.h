
#ifndef _Propagator_Name_H_
#define _Propagator_Name_H_

namespace mysimulator {

  enum PropagatorName {
    MolecularDynamics = 0,
    MolecularDynamicsWithNeighborList,
    SteepestDescentMinimizer,
    ConjugateGradientMinimizer,
    LBFGSMinimizer,
    NumberPropagator,
    UnknownPropagator
  };

}

#endif

