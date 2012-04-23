
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/evolute/mode.h"
#include "array/1d/fill.h"

#define _DefEvFunc(NAME) \
  EvFunc=SystemEvoluteMode##NAME<T,IDType,ParamType,GeomType,ParamType,\
                                 BufferType,ContentType>

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType,template<typename> class ContentType>
  struct System {

    public:

      typedef
        System<T,IDType,ParamType,GeomType,BufferType,ContentType>
        Type;
      typedef
        SystemInteraction<T,IDType,ParamType,GeomType,BufferType,ContentType>
        InteractionType;
      typedef
        SystemPropagator<T,ContentType>
        PropagatorType;
      typedef
        void (*EvFuncType)(ContentType<T>&,Array1D<InteractionType>&,
                           Array1D<PropagatorType>&,
                           const Array1D<Array1D<unsigned int> >&);

      unsigned int EvoluteMode;
      ContentType<T> Content;
      Array1D<InteractionType>  Interactions;
      Array1D<PropagatorType>   Propagtors;
      Array1D<Array1D<unsigned int> >     GrpMap;
      EvFuncType                EvFunc;

      System() : EvoluteMode(0), Content(), Interactions(), Propagtors(),
                 GrpMap(), EvFunc(NULL) {}
      ~System() { Clear(*this); }

      bool IsValid() const {
        return (EvoluteMode!=0)&&Content.IsValid()&&Interactions.IsValid()&&
               Propagtors.IsValid()&&GrpMap.IsValid()&&(EvFunc!=NULL);
      }

      void _Init() {
        assert(IsValid());
        for(unsigned int i=0;i<Propagtors.Size();++i) Propagtors[i]._Init();
      }
      void _Clear() {
        assert(IsValid());
        for(unsigned int i=0;i<Propagtors.Size();++i) Propagtors[i]._Clear();
      }
      void Evolute() {
        assert(IsValid());
        EvFunc(Content,Interactions,Propagtors,GrpMap);
      }

      void _Build() {
        assert(Propagtors.IsValid());
        GrpMap.Allocate(SystemPropagatorNumberMethods);
        Array1D<unsigned int> sz;
        sz.Allocate(SystemPropagatorNumberMethods);
        Fill(sz,0U,sz.Size());
        for(unsigned int i=0;i<Propagtors.Size();++i)
          ++sz[Propagtors[i].Method];
        for(unsigned int i=0;i<Propagtors.Size();++i)
          if(sz[i]>0) { GrpMap[i].Allocate(sz[i]); sz[i]=0; }
        for(unsigned int i=0,k;i<Propagtors.Size();++i) {
          k=Propagtors[i].Method;
          GrpMap[k][sz[k]]=i;
          ++sz[k];
        }
        Clear(sz);
        EvoluteMode=0;
        for(unsigned int i=0;i<GrpMap.Size();++i)
          EvoluteMode+=((GrpMap[i].Size()>0?1:0)<<i);
        if(EvoluteMode&1)
          EvFunc=SystemEvoluteModeTBD<T,IDType,ParamType,GeomType,BufferType,
                                      ContentType>;
        else {
          switch(EvoluteMode) {
            case 0:
              fprintf(stderr,"No Propagator Available!\n");
              break;
            case 2:
              _DefEvFunc(FixPosition);  break;
            case 8:
              _DefEvFunc(VelVerletConstE);  break;
            case 10:
              _DefEvFunc(VelVerletCEFP);  break;
            default:
              fprintf(stderr,"Not Implemented!\n");
          }
        }
      }

    private:

      System(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void Clear(System<T,IDT,PT,GT,BT,CT>& S) {
    S.EvFunc=NULL;
    Clear(S.GrpMap);
    Clear(S.Propagtors);
    Clear(S.Interactions);
    Clear(S.Content);
    S.EvoluteMode=0;
  }

}

#endif

