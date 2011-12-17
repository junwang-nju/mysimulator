
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/grouping/interface.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct System {

    public:

      typedef System<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;

      Object<SysContentType<T,VecType> > Content;
      Object<SysInteraction<IDType,ParamType,GeomType,T> > Interaction;
      Array1D<SysGrouping<T,IDType,ParamType,GeomType,VecType,SysContentType> >
        Groups;
      Array1D<Array1D<unsigned int> > GrpMap;

      System() : Content(), Interaction(), Groups(), GrpMap() {}
      ~System() { clearData(); }

      void clearData() {
        release(GrpMap);release(Groups);release(Content);release(Interaction);
      }
      bool isvalid() const {
        return IsValid(Content)&&IsValid(Interaction)&&IsValid(Groups)&&
               IsValid(GrpMap);
      }

      void init() {
        assert(isvalid());
        for(unsigned int i=0;i<Groups.size;++i)
          Groups[i].init(Content(),Interaction());
      }
      void evolute() {
        assert(isvalid());
        for(unsigned int i=0;i<Groups.size;++i)
          Groups[i].evolute(Content(),Interaction());
      }

      void mapBuild() {
        assert(IsValid(Groups));
        Array1D<unsigned int> sz;
        allocate(sz,NumSystemGroupingMethods);
        fill(sz,0U);
        for(unsigned int i=0;i<Groups.size;++i) sz[Groups[i].Method]++;
        allocate(GrpMap,NumSystemGroupingMethods);
        for(unsigned int i=0;i<NumSystemGroupingMethods;++i)
          if(sz[i]>0) { allocate(GrpMap[i],sz[i]); sz[i]=0; }
        for(unsigned int i=0,k;i<Groups.size;++i) {
          k=Groups[i].Method;
          GrpMap[k][sz[k]]=i;   sz[k]++;
        }
        release(sz);
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

