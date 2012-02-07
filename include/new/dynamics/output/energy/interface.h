
#ifndef _Dynamics_Output_Energy_Interface_H_
#define _Dynamics_Output_Energy_Interface_H_

#include "dynamics/output/base/interface.h"
#include "dynamics/output/energy/data/interface.h"
#include "system/evaluate/energy.h"
#include "system/property/kinetic-energy.h"

namespace mysimulator {

  template <typename OST,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  struct DynamicsOutputEnergy : public DynamicsOutputBase<OST,T> {

    public:

      typedef DynamicsOutputEnergy<OST,T,IDT,PT,GT,VT,SCT>  Type;
      typedef DynamicsOutputBase<OST,T>   ParentType;

      DynamicsOutputEnergyData<T,IDT,PT,GT,VT,SCT>  EnergyData;

      DynamicsOutputEnergy() : ParentType(), EnergyData() {}
      ~DynamicsOutputEnergy() { clearData(); }

      void clearData() {
        release(EnergyData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(EnergyData);
      }

      virtual void write() {
        assert(isvalid());
        (this->OS())<<(this->BaseData().NowTime());
        GenericEvaluateEnergy(EnergyData.S().Content(),
                              EnergyData.S().Interactions);
        for(unsigned int i=0;i<EnergyData.S().Interactions.size;++i)
          (this->OS())<<"\t"<<EnergyData.S().Interactions[i].EGData().Energy();
        (this->OS())<<"\t"<<EnergyData.S().Content().EGData.Energy();
        T SumKE=0,KE;
        for(unsigned int i=0;i<EnergyData.S().Propagates.size;++i) {
          KE=KineticEnergy(EnergyData.S().Propagates[i]);
          SumKE+=KE;
          (this->OS())<<"\t"<<KE;
        }
        (this->OS())<<"\t"<<SumKE;
        if(IsTerminated)  (this->OS())<<Endl;
      }

    private:

      DynamicsOutputEnergy(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename OST,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(DynamicsOutputEnergy<OST,T,IDT,PT,GT,VT,SCT>& O) {
    O.clearData();
  }

  template <typename OST,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const DynamicsOutputEnergy<OST,T,IDT,PT,GT,VT,SCT>& O) {
    return O.isvalid();
  }

}

#endif

