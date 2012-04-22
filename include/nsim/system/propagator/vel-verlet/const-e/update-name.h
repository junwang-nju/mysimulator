
#ifndef _System_Propagator_VelVerlet_ConstE_Update_Name_H_
#define _System_Propagator_VelVerlet_ConstE_Update_Name_H_

namespace mysimulator {

  enum VelVerletConstEUpdateName {
    VelVerletConstECalcHTIM=0,
    VelVerletConstECalcVSQ,
    VelVerletConstECalcKESimple,
    VelVerletConstECalcKE,
    VelVerletConstENumberUpdates
  };

}

#endif

