
#ifndef _Propagator_Time_MolecularDynamics_Update_Name_H_
#define _Propagator_Time_MolecularDynamics_Update_Name_H_

namespace mysimulator {

  enum PropagatorMDTimeUpdateName {
    Step_Total_OInterval=0,
    Step_Total_NBwOutput,
    Step_NTotal_OInterval,
    Step_NTotal_NBwOutput,
    NTotal_Total_OInterval,
    NTotal_Total_NBwOutput
  };

}

#endif

