
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/evolute/mode.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct System {

    public:

      typedef System<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;
      typedef SysContentType<T,VecType>   ContentType;
      typedef SysInteraction<T,IDType,ParamType,GeomType,VecType,SysContentType>
              InteractionType;
      typedef SysPropagate<T,VecType,SysContentType>  PropagateType;
      typedef void (*EvFuncType)(ContentType&,Array1DContent<InteractionType>&,
                                 Array1DContent<PropagateType>&,
                                 const Array1DContent<Array1D<unsigned int> >&);

      Object<ContentType> Content;
      Array1D<InteractionType>  Interactions;
      Array1D<PropagateType>  Propagates;
      Array1D<Array1D<unsigned int> > GrpMap;
      EvFuncType  evfunc;

      System() : Content(), Interactions(), Propagates(), GrpMap(),
                 evfunc(NULL) {}
      ~System() { clearData(); }

      void clearData() {
        release(GrpMap);  release(Propagates);  release(Interactions);
        release(Content); evfunc=NULL;
      }
      bool isvalid() const {
        return IsValid(Content)&&IsValid(Interactions)&&IsValid(Propagates)&&
               IsValid(GrpMap)&&IsValid(evfunc);
      }

      void init() {
        assert(isvalid());
        for(unsigned int i=0;i<Propagates.size;++i) Propagates[i].init();
      }
      void evolute() {
        assert(isvalid());
        evfunc(Content(),Interactions,Propagates,GrpMap);
      }

      void build() {
        assert(IsValid(Propagates));
        Array1D<unsigned int> sz;
        allocate(sz,NumberSystemPropagateMethods);
        fill(sz,0U);
        for(unsigned int i=0;i<Propagates.size;++i) sz[Propagates[i].Method]++;
        allocate(GrpMap,NumberSystemPropagateMethods);
        for(unsigned int i=0;i<sz.size;++i)
          if(sz[i]>0) { allocate(GrpMap[i],sz[i]);  sz[i]=0; }
        for(unsigned int i=0,k;i<Propagates.size;++i) {
          k=Propagates[i].Method;
          GrpMap[k][sz[k]]=i;
          ++sz[k];
        }
        release(sz);
        unsigned int mode=0;
        for(unsigned int i=0;i<GrpMap.size;++i)
          mode+=(GrpMap[i].size>0?1:0)<<i;
        switch(mode) {
          case 0:
            Error("No Propagate Available!");
            break;
          case 1:
          case 3:
          case 5:
          case 7:
          case 9:
          case 11:
          case 13:
          case 15:
            evfunc=SysEvoluteModeTBD<T,IDType,ParamType,GeomType,VecType,
                                     SysContentType>;
            break;
          case 2:
            evfunc=SysEvoluteModeFPOnly<T,IDType,ParamType,GeomType,VecType,
                                        SysContentType>;
            break;
          case 4:
            evfunc=SysEvoluteModeMLROnly<T,IDType,ParamType,GeomType,VecType,
                                         SysContentType>;
            break;
          case 6:
            evfunc=SysEvoluteModeFPMLR<T,IDType,ParamType,GeomType,VecType,
                                       SysContentType>;
            break;
          case 8:
            evfunc=SysEvoluteModeCEVVOnly<T,IDType,ParamType,GeomType,VecType,
                                          SysContentType>;
            break;
          case 16:
            evfunc=SysEvoluteModeLgVVOnly<T,IDType,ParamType,GeomType,VecType,
                                          SysContentType>;
            break;
          default:
            Error("Unknown Mode to Evalute!");
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

