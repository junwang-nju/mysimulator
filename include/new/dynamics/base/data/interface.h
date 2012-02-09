
#ifndef _Dynamics_Base_Data_Interface_H_
#define _Dynamics_Base_Data_Interface_H_

#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  struct DynamicsBaseData {

    public:

      typedef DynamicsBaseData<T,VT>    Type;

      T TimeStep;
      T RunPeriod;
      T StartTime;
      unsigned int NumSteps;
      T NowTime;

      VT<T> Mass;

      DynamicsBaseData() : TimeStep(0), RunPeriod(0), StartTime(0), NumSteps(0),
                           NowTime(0), Mass() {}
      ~DynamicsBaseData() { clearData(); }

      void clearData() {
        TimeStep=0; RunPeriod=0; StartTime=0; NumSteps=0; NowTime=0;
        release(Mass);
      }
      bool isvalid() const { return (TimeStep>RelativeDelta<T>()); }

      void updateNumSteps() {
        NumSteps=static_cast<unsigned int>(RunPeriod/TimeStep+0.5);
        updateRunPeriod();
      }
      void updateRunPeriod() { RunPeriod=NumSteps*TimeStep; }
      void updateNowTime(const T& delta) { NowTime+=delta; }
      void updateNowTime(const unsigned int& n) { updateNowTime(n*TimeStep); }

    private:

      DynamicsBaseData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(DynamicsBaseData<T,VT>& D) { D.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const DynamicsBaseData<T,VT>& D) { return D.isvalid(); }

}

#endif

