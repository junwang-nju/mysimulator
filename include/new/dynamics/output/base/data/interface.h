
#ifndef _Dynamics_Output_Base_Data_Interface_H_
#define _Dynamics_Output_Base_Data_Interface_H_

#include "object/interface.h"

namespace mysimulator {

  template <typename T>
  struct DynamicsOutputBaseData {

    public:

      typedef DynamicsOutputBaseData<T>   Type;

      T TimeBwOutput;
      unsigned int NumStepsBwOutput;
      Object<T> NowTime;

      DynamicsOutputBaseData() : TimeBwOutput(0), NumStepsBwOutput(0),
                                 NowTime() {}
      ~DynamicsOutputBaseData() { clearData(); }

      void clearData() { TimeBwOutput=0; NumStepsBwOutput=0; release(NowTime); }
      bool isvalid() const { return IsValid(NowTime)&&(NumStepsBwOutput>0); }

      void updateNumStepsBwOutput(const T& dt) {
        NumStepsBwOutput=static_cast<unsigned int>(TimeBwOutput/dt+0.5);
        updateTimeBwOutput(dt);
      }
      void updateTimeBwOutput(const T& dt) { TimeBwOutput=dt*NumStepsBwOutput; }
      void setNowTime(const T& time) { refer(NowTime,time); }

    private:

      DynamicsOutputBaseData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(DynamicsOutputBaseData<T>& D) { D.clearDdata(); }

  template <typename T>
  bool IsValid(const DynamicsOutputBaseData<T>& D) { return D.isvalid(); }

}

#endif

