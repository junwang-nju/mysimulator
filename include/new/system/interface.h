
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/evolute/mode.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"

#define _DefEvFunc(name) \
  evfunc=name<T,IDType,ParamType,GeomType,VecType,SysContentType>;

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

      unsigned int EvoluteMode;
      Object<ContentType> Content;
      Array1D<InteractionType>  Interactions;
      Array1D<PropagateType>  Propagates;
      Array1D<Array1D<unsigned int> > GrpMap;
      EvFuncType  evfunc;

      System() : EvoluteMode(0), Content(), Interactions(), Propagates(),
                 GrpMap(), evfunc(NULL) {}
      ~System() { clearData(); }

      void clearData() {
        release(GrpMap);  release(Propagates);  release(Interactions);
        release(Content); evfunc=NULL; EvoluteMode=0;
      }
      bool isvalid() const {
        return IsValid(Content)&&IsValid(Interactions)&&IsValid(Propagates)&&
               IsValid(GrpMap)&&IsValid(evfunc)&&(EvoluteMode!=0);
      }

      void init() {
        assert(isvalid());
        for(unsigned int i=0;i<Propagates.size;++i) Propagates[i].init();
      }
      void evolute() {
        assert(isvalid());
        evfunc(Content(),Interactions,Propagates,GrpMap);
      }
      void clear() {
        assert(isvalid());
        for(unsigned int i=0;i<Propagates.size;++i) Propagates[i].clear();
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
        EvoluteMode=mode;
        if(EvoluteMode&1)
          evfunc=SysEvoluteModeTBD<T,IDType,ParamType,GeomType,VecType,
                                   SysContentType>;
        else {
          switch(EvoluteMode) {
            case 0:
              Error("No Propagate Available!");
              break;
            case 2:
              _DefEvFunc(SysEvoluteModeFPOnly)
              break;
            case 4:
              _DefEvFunc(SysEvoluteModeMLROnly)
              break;
            case 6:   //  4+2
              _DefEvFunc(SysEvoluteModeFPMLR)
              break;
            case 8:
              _DefEvFunc(SysEvoluteModeCEVVOnly)
              break;
            case 10:  //  8+2
              _DefEvFunc(SysEvoluteModeFPCEVV)
              break;
            case 16:
              _DefEvFunc(SysEvoluteModeLgVVOnly)
              break;
            case 18:  //  16+2
              _DefEvFunc(SysEvoluteModeFPLgVV)
              break;
            case 24:  //  16+8
              _DefEvFunc(SysEvoluteModeCELgVV)
              break;
            case 26:  //  16+8+2
              _DefEvFunc(SysEvoluteModeFPCELgVV)
              break;
            case 32:
              _DefEvFunc(SysEvoluteModeBsVVOnly)
              break;
            default:
              Error("Unknown Mode to Evalute!");
          }
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

#undef _DefEvFunc

#endif

