
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/evolute/mode.h"
#include "dynamics/interface.h"

#define _DefEvFunc(NAME) \
  EvFunc=SystemEvoluteMode##NAME<T,IDType,ParamType,GeomType,BufferType,\
                                 ContentType>

namespace mysimulator {

  template <DynamicsModeName DN,typename T,typename GRT>
  struct Dynamics;

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
      Array1D<PropagatorType>   Propagators;
      Array1D<Array1D<unsigned int> >     GrpMap;
      EvFuncType                EvFunc;

      System() : EvoluteMode(0), Content(), Interactions(), Propagators(),
                 GrpMap(), EvFunc(NULL) {}
      ~System() { Clear(*this); }

      bool IsValid() const {
        return (EvoluteMode!=0)&&Content.IsValid()&&Interactions.IsValid()&&
               Propagators.IsValid()&&GrpMap.IsValid()&&(EvFunc!=NULL);
      }

      void Refer(Type& S) {
        Clear(*this);
        EvoluteMode=S.EvoluteMode;
        Content.Refer(S.Content);
        Interactions.Refer(S.Interactions);
        Propagators.Refer(S.Propagators);
        GrpMap.Refer(S.GrpMap);
        EvFunc=S.EvFunc;
      }

      void _Init() {
        assert(IsValid());
        for(unsigned int i=0;i<Propagators.Size();++i) Propagators[i]._Init();
      }
      void _Clear() {
        assert(IsValid());
        for(unsigned int i=0;i<Propagators.Size();++i) Propagators[i]._Clear();
      }
      void StepEvolute() {
        assert(IsValid());
        EvFunc(Content,Interactions,Propagators,GrpMap);
      }
      template <DynamicsModeName DN,typename GRT>
      void Evolute(Dynamics<DN,T,GRT>& D) {
        assert(IsValid()&&D.IsValid());
        assert(IsMatch(D,*this));
        assert(D.BindFlag);
        typedef void (*EvWriteType)(Type&,Dynamics<DN,T,GRT>&);
        EvWriteType EvWrite=reinterpret_cast<EvWriteType>(D.WriteFunc.ptr);
        unsigned int n=
          static_cast<unsigned int>(D.RunPeriod/D.TimeBwOutput);
        D.NowTime=D.StartTime;
        if(D.IsFirstOutput) EvWrite(*this,D);
        for(unsigned int i=0;i<=n;++i) {
          for(unsigned int k=0;k<D.NumStepsBwOutput;++k)  StepEvolute();
          D.UpdateNowTime(D.TimeBwOutput);
          EvWrite(*this,D);
        }
      }

      void _Build() {
        assert(Propagators.IsValid());
        GrpMap.Allocate(SystemPropagatorNumberMethods);
        Array1D<unsigned int> sz;
        sz.Allocate(SystemPropagatorNumberMethods);
        Fill(sz,0U,sz.Size());
        for(unsigned int i=0;i<Propagators.Size();++i)
          ++sz[Propagators[i].Method];
        GrpMap.Allocate(SystemPropagatorNumberMethods);
        for(unsigned int i=0;i<SystemPropagatorNumberMethods;++i)
          if(sz[i]>0) { GrpMap[i].Allocate(sz[i]); sz[i]=0; }
        for(unsigned int i=0,k;i<Propagators.Size();++i) {
          k=Propagators[i].Method;
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
            case 4:
              _DefEvFunc(MinimizerLineRegular); break;
            case 6:
              _DefEvFunc(MinimizerLRFP);  break;
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
    Clear(S.Propagators);
    Clear(S.Interactions);
    Clear(S.Content);
    S.EvoluteMode=0;
  }

}

#endif

