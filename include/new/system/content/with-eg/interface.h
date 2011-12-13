
#ifndef _System_Content_With_EnergyGradient_Interface_H_
#define _System_Content_With_EnergyGradient_Interface_H_

#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType>
  struct SystemWithEG
      : public SystemWithE<T,IDType,ParamType,GeomType,SpaceType> {

    public:

      typedef SystemWithEG<T,IDType,ParamType,GeomType,SpaceType> Type;
      typedef SystemWithE<T,IDType,ParamType,GeomType,SpaceType> ParentType;

      Object<SpaceType<T> > G;

      SystemWithEG() : ParentType(), G() {}
      ~SystemWithEG() { clearData(); }

      void clearData() {
        release(G);
        static_cast<ParentType*>(this)->clearData();
      }
      const bool isvalid() const {
        return IsValid(G)&&static_cast<const ParentType*>(this)->isvalid();
      }

      void loadCoor(const SpaceType<T>& iX) {
        static_cast<ParentType*>(this)->loadCoor(iX);
        imprint(G,iX);
      }

      void UpdateG() {
        assert(isvalid());
        fill(G,cZero);
        Calc(this->Func,this->X(),this->ID,this->Param,this->Geo,G());
      }
      void Update() {
        assert(isvalid());
        this->Energy=0;
        fill(G,cZero);
        Calc(this->Func,this->X(),this->ID,this->Param,this->Geo,
             this->Energy,G());
      }

    private:

      SystemWithEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType>
  void release(SystemWithEG<T,IDType,ParamType,GeomType,SpaceType>& S) {
    S.clearData();
  }

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType>
  bool IsValid(const SystemWithEG<T,IDType,ParamType,GeomType,SpaceType>& S) {
    return S.isvalid();
  }

}

#endif

