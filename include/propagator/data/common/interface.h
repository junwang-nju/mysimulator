
#ifndef _Propagator_Data_Common_Interface_H_
#define _Propagator_Data_Common_Interface_H_

#include "io/error.h"

namespace mysimulator {

  template <typename T>
  struct PropagatorDataCommon {

    T StartTime;
    T RunTimeStep;
    T TotalTime;
    T NowTime;
    unsigned int NowStepID;
    T OutputInterval;
    unsigned int NumberOutput;
    unsigned int NumStepPerOutput;

    PropagatorDataCommon()
        : StartTime(0), RunTimeStep(0), TotalTime(0), NowTime(0), NowStepID(0),
          OutputInterval(0), NumberOutput(0), NumStepPerOutput(0) {
    }
    PropagatorDataCommon(const Type&) {
      Error("Copier of PropagatorDataCommon Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for PropagatorDataCommon Disabled!");
      return *this;
    }
    ~PropagatorDataCommon() { clearData(); }

    void clearData() {
      StartTime=0; RunTimeStep=0; TotalTime=0; NowTime=0;
      NowStepID=0; OutputInterval=0; NumberOutput=0; NumStepPerOutput=0;
    }

  };

  template <typename T>
  bool IsValid(const PropagatorDataCommon<T>&) { return true; }

  template <typename T>
  void release(PropagatorDataCommon<T>& PD) { PD.clearData(); }

}

#endif

