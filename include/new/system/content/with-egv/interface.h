
#ifndef _System_Content_WithEGV_Interface_H_
#define _System_Content_WithEGV_Interface_H_

#include "system/content/with-eg/interface.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class SpaceType>
  struct SystemWithEGV
      : public SystemWithEG<T,IDType,ParamType,GeomType,SpaceType> {

    public:

      typedef SystemWithEGV<T,IDType,ParamType,GeomType,SpaceType> Type;
      typedef SystemWithEG<T,IDType,ParamType,GeomType,SpaceType>  ParentType;

      Object<SpaceType<T> >   G;
      Object<SpaceType<T> >   V;

      SystemWithEGV() : ParentType(), G(), V() {}
      ~SystemWithEGV() { clearData(); }

      void clearData() {
        release(V);
        release(G);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return IsValid(V)&&IsValid(G)&&
               static_cast<ParentType*>(this)->isvalid();
      }

      void loadCoor(const SpaceType<T>& iX) {
        static_cast<ParentType*>(this)->loadCoor(iX);
        imprint(G,iX);
        imprint(V,iX);
      }

  };

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class SpaceType>
  void release(SystemWithEGV<T,IDType,ParamType,GeomType,SpaceType>& S) {
    S.clearData();
  }

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class SpaceType>
  void IsValid(const SystemWithEGV<T,IDType,ParamType,GeomType,SpaceType>& S) {
    return S.isvalid();
  }

}

#endif

