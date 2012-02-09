
#ifndef _Dynamics_Output_Base_Data_Interface_H_
#define _Dynamics_Output_Base_Data_Interface_H_

namespace mysimulator {

  struct DynamicsOutputBaseData {
  };

  void release(DynamicsOutputBaseData& D) { D.clearDdata(); }
  bool IsValid(const DynamicsOutputBaseData& D) { return D.isvalid(); }

}

#endif

