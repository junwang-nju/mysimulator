
#ifndef _Dynamics_Base_Interface_H_
#define _Dynamics_Base_Interface_H_

#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T>
  struct DynamicsBase {

    public:

      typedef DynamicsBase<T>   Type;

      T TimeStep;
      T RunPeriod;
      T StartTime;
      unsigned int NumSteps;

      DynamicsBase() : TimeStep(0), RunPeriod(0), StartTime(0), NumSteps(0) {}
      ~DynamicsBase() { clearData(); }

      void clearData() {
        TimeStep=0; RunPeriod=0; StartTime=0; NumSteps=0;
      }
      bool isvalid() const { return TimeStep>RelativeDelta<T>(); }

    private:

      DynamicsBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(DynamicsBase<T>& D) { D.clearData(); }

  template <typename T>
  bool IsValid(const DynamicsBase<T>& D) { return D.isvalid(); }

}

#endif

