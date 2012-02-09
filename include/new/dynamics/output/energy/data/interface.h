
#ifndef _Dynamics_Output_Energy_Data_Interface_H_
#define _Dynamics_Output_Energy_Data_Interface_H_

#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  struct DynamicsOutputEnergyData {

    public:

      typedef DynamicsOutputEnergyData<T,IDT,PT,GT,VT,SCT>  Type;

      Object<System<T,IDT,PT,GT,VT,SCT> > S;
      VT<T> VelocitySQ;

      DynamicsOutputEnergyData() : S(), VelocitySQ() {}
      ~DynamicsOutputEnergyData() { clearData(); }

      void clearData() { release(S); release(VelocitySQ); }
      bool isvalid() const { return IsValid(S); }

    private:

      DynamicsOutputEnergyData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(DynamicsOutputEnergyData<T,IDT,PT,GT,VT,SCT>& O) {
    O.clearData();
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const DynamicsOutputEnergyData<T,IDT,PT,GT,VT,SCT>& O) {
    return O.isvalid();
  }

}

#endif

