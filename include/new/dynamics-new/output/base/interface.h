
#ifndef _Dynamics_Output_Base_Interface_H_
#define _Dynamics_Output_Base_Interface_H_

#include "object/refer.h"

namespace mysimulator {

  template <typename OStreamType, typename T>
  struct DynamicsOutputBase {

    public:

      typedef DynamicsOutputBase<OStreamType,T>   Type;

      OStreamType OS;
      T TimeBwOutput;
      unsigned int NumStepsBwOutput;
      bool IsFirstOutput;
      Object<T> NowTime;

      DynamicsOutputBase() : OS(), TimeBwOutput(0), NumStepsBwOutput(0),
                             IsFirstOutput(false), NowTime() {}
      ~DynamicsOutputBase() { clearData(); }

      void clearData() {
        release(NowTime); release(OS); TimeBwOutput=0; NumStepsBwOutput=0;
        IsFirstOutput=false;
      }
      bool isvalid() const {
        return IsValid(OS)&&(NumStepsBwOutput>0)&&IsValid(NowTime);
      }

      virtual void write() = 0;

      void updateNumStepsBwOutput(const T& dt) {
        NumStepsBwOutput=static_cast<unsigned int>(TimeBwOutput/dt+0.5);
        updateTimeBwOutput(dt);
      }
      void updateTimeBwOutput(const T& dt) { TimeBwOutput=dt*NumStepsBwOutput; }
      void setNowTime(const T& time) { refer(NowTime,time); }

    private:

      DynamicsOutputBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename OST, typename T>
  void release(DynamicsOutputBase<OST,T>& O) { O.clearData(); }

  template <typename OST, typename T>
  bool IsValid(DynamicsOutputBase<OST,T>& O) { return O.isvalid(); }

}

#endif

