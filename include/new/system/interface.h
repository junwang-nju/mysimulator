
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/grouping/interface.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"
#include "system/evolute/mode-1.h"
#include "system/evolute/mode-2.h"
#include "system/evolute/mode-3.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct System {

    public:

      typedef System<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;
      typedef SysContentType<T,VecType> ContentType;
      typedef SysInteraction<IDType,ParamType,GeomType,T> InteractionType;
      typedef SysGrouping<T,IDType,ParamType,GeomType,VecType,SysContentType>
              GroupingType;
      typedef void (*EvFuncType)(ContentType&,InteractionType&,
                                 Array1D<GroupingType>&,
                                 const Array1D<Array1D<unsigned int> >&);

      Object<ContentType> Content;
      Object<InteractionType> Interaction;
      Array1D<GroupingType> Groups;
      Array1D<Array1D<unsigned int> > GrpMap;
      EvFuncType evfunc;

      System() : Content(), Interaction(), Groups(), GrpMap(), evfunc(NULL) {}
      ~System() { clearData(); }

      void clearData() {
        release(GrpMap);release(Groups);release(Content);release(Interaction);
        evfunc=NULL;
      }
      bool isvalid() const {
        return IsValid(Content)&&IsValid(Interaction)&&IsValid(Groups)&&
               IsValid(GrpMap)&&IsValid(evfunc);
      }

      void init() {
        assert(isvalid());
        for(unsigned int i=0;i<Groups.size;++i)
          Groups[i].init(Content(),Interaction());
      }
      void evolute() {
        assert(isvalid());
        evfunc(Content(),Interaction(),Groups,GrpMap);
      }

      void Build() {
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
        unsigned int mode=0;
        for(unsigned int i=0;i<GrpMap.size;++i)
          mode+=(GrpMap[i].size>0?1:0)<<i;
        switch(mode) {
          case 1:
            evfunc=SystemEvoluteMode1<T,IDType,ParamType,GeomType,VecType,
                                      SysContentType>;
            break;
          case 2:
            evfunc=SystemEvoluteMode2<T,IDType,ParamType,GeomType,VecType,
                                      SysContentType>;
            break;
          case 3:
            evfunc=SystemEvoluteMode3<T,IDType,ParamType,GeomType,VecType,
                                      SysContentType>;
            break;
          default:
            Error("Unknown Mode for Evolution!");
        }
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

