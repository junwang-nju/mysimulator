
#ifndef _Dynamics_Base_Interface_H_
#define _Dynamics_Base_Interface_H_

#include "dynamics/base/data/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT, typename OChannel>
  struct DynamicsBase {

    public:
      
      typedef DynamicsBase<T,VT,OChannel>    Type;

      DynamicsBaseData BaseData;
      OChannel  Output;
      bool BindFlag;

      DynamicsBase() : BaseData(), Output(), BindFlag(false) {}
      ~DynamicsBase() { clearData(); }

      void clearData() {
        assert(!BindFlag);
        release(Output); release(BaseData);
      }
      bool isvalid() const { return IsValid(BaseData)&&IsValid(Output); }

      void updateNumSteps() { BaseData.updateNumSteps(); }
      void updateRunPeriod() { BaseData.updateRunPeriod(); }
      void updateNowTime(const T& delta) { BaseData.updateNowTime(delta); }
      void updateNowTime(const unsigned int& n) { BaseData.updateNowTime(n); }

    private:

      DynamicsBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT, typename OCT>
  void release(DynamicsBase<T,VT,OCT>& D) { D.clearData(); }

  template <typename T, template<typename> class VT, typename OCT>
  bool IsValid(const DynamicsBase<T,VT,OCT>& D) { return D.isvalid(); }

}

#endif

