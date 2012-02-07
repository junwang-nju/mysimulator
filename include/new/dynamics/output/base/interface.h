
#ifndef _Dynamics_Output_Base_Interface_H_
#define _Dynamics_Output_Base_Interface_H_

#include "dynamics/output/base/data/interface.h"

namespace mysimulator {

  template <typename OStreamType, typename T>
  struct DynamicsOutputBase {

    public:

      typedef DynamicsOutputBase<OStreamType,T>   Type;

      Object<DynamicsOutputBaseData<T> >  BaseData;
      Object<OStreamType> OS;
      bool IsFirstOutput;
      bool IsTerminated;

      DynamicsOutputBase() : BaseData(), OS(), IsFirstOutput(false),
                             IsTerminated(false) {}
      ~DynamicsOutputBase() { clearData(); }

      void clearData() {
        IsFirstOutput=false; IsTerminated=false;
        release(BaseData); release(OS);
      }
      bool isvalid() const { return IsValid(OS)&&IsValid(BaseData); }

      virtual void write() = 0;

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

