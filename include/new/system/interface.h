
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/grouping/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct System {

    public:

      typedef System<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;

      SysContentType<T,VecType> SysContent;
      SysInteraction<IDType,ParamType,GeomType,T> SysInteract;
      Array1D<SysGrouping<T,IDType,ParamType,GeomType,VecType,SysContentType> >
        SysGroups;

      System() : SysContent(), SysInteract(), SysGroups() {}
      ~System() { clearData(); }

      void clearData() {
        release(SysContent); release(SysInteract); release(SysGroups);
      }
      bool isvalid() const {
        return IsValid(SysContent)&&IsValid(SysInteract)&&IsValid(SysGroups);
      }

      void evolute() {
        for(unsigned int i=0;i<SysGroups.size;++i)
          SysGroups[i].evolute(SysContent,SysInteract);
      }

    private:

      System(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(System<T,IDT,PT,GT,VT,SCT>& S) { S.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const System<T,IDT,PT,GT,VT,SCT>& S) { return S.isvalid(); }

}

#endif

