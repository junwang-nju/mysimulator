
#ifndef _System_With_EnergyGradient_Interface_H_
#define _System_With_EnergyGradient_Interface_H_

#include "system/with-e/interface.h"
#include "system/mask-mode.h"
#include "system/masked/method/interface.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType, SystemMaskModeName MN>
  struct SystemWithEG
      : public SystemWithE<T,IDType,ParamType,GeomType,SpaceType> {

    public:

      typedef SystemWithEG<T,IDType,ParamType,GeomType,SpaceType,MN> Type;
      typedef SystemWithE<T,IDType,ParamType,GeomType,SpaceType> ParentType;
      typedef typename ParentType::FuncType   FuncType;

      Object<SpaceType<T> > G;
      Mask4System<T,SpaceType> Mask;
      SystemMaskApply<static_cast<SystemMaskMethodName>(MN)> MaskApply;

      SystemWithEG() : ParentType(), G(), Mask(), MaskApply() {
        assert((MN==SystemNoMask)&&(MN==SystemFree));
      }
      ~SystemWithEG() { clearData(); }

      void clearData() {
        release(MaskApply);
        release(Mask);
        release(G);
        static_cast<ParentType*>(this)->clearData();
      }
      const bool isvalid() const {
        return IsValid(MaskApply)&&IsValid(Mask)&&IsValid(G)&&
               static_cast<const ParentType*>(this)->isvalid();
      }

      void loadCoor(const SpaceType<T>& iX) {
        static_cast<ParentType*>(this)->loadCoor(iX);
        imprint(G,iX);
        allocate(Mask,iX);
      }

      void UpdateG() {
        assert(isvalid());
        fill(G,cZero);
        Calc(this->Func,this->X(),this->ID,this->Param,this->Geo,G());
        MaskApply.Do(G,Mask);
      }
      void Update() {
        assert(isvalid());
        this->Energy=0;
        fill(G,cZero);
        Calc(this->Func,this->X(),this->ID,this->Param,this->Geo,
             this->Energy,G());
        MaskApply.Do(G,Mask);
      }

    private:

      SystemWithEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType, SystemMaskModeName MN>
  void release(SystemWithEG<T,IDType,ParamType,GeomType,SpaceType,MN>& S) {
    S.clearData();
  }

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType, SystemMaskModeName MN>
  bool IsValid(const SystemWithEG<T,IDType,ParamType,GeomType,SpaceType,MN>& S){
    return S.isvalid();
  }

}

#endif

