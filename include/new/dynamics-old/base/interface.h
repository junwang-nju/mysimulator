
#ifndef _Dynamics_Base_Interface_H_
#define _Dynamics_Base_Interface_H_

#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, typename OutputChannel>
  struct DynamicsBase {

    public:

      typedef DynamicsBase<T,OutputChannel>   Type;

      T TimeStep;
      T RunPeriod;
      T StartTime;
      unsigned int NumSteps;
      T NowTime;
      OutputChannel Output;

      DynamicsBase() : TimeStep(0), RunPeriod(0), StartTime(0), NumSteps(0),
                       NowTime(0), Output() {}
      ~DynamicsBase() { clearData(); }

      void clearData() {
        TimeStep=0; RunPeriod=0; StartTime=0; NumSteps=0; NowTime=0;
        release(Output);
      }
      bool isvalid() const {
        return (TimeStep>RelativeDelta<T>())&&IsValid(Output);
      }

      void updateNumSteps() {
        NumSteps=static_cast<unsigned int>(RunPeriod/TimeStep+0.5);
        updateRunPeriod();
      }

      void updateRunPeriod() { RunPeriod=NumSteps*TimeStep; }

      void updateNowTime(const T& delta) { NowTime+=delta; }
      void updateNowTime(const unsigned int& n) { NowTime+=n*TimeStep; }

    private:

      DynamicsBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename OC>
  void release(DynamicsBase<T,OC>& D) { D.clearData(); }

  template <typename T, typename OC>
  bool IsValid(const DynamicsBase<T,OC>& D) { return D.isvalid(); }

}

#endif

