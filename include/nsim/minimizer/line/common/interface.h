
#ifndef _Minimizer_Line_Common_Interface_H_
#define _Minimizer_Line_Common_Interface_H_

#include "minimizer/base/interface.h"
#include "system/content/with-egv/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  struct LineMinimizerCommon : public MinimizerBase<T,IDT,PT,GT,BT,CT> {

    public:

      typedef LineMinimizerCommon<T,IDT,PT,GT,BT,CT>  Type;
      typedef MinimizerBase<T,IDT,PT,GT,BT,CT>  ParentType;
      typedef System<T,IDT,PT,GT,BT,SystemContentWithEGV>   SystemType;

      SystemType    MemSys;
      SystemType    RunSys;
      T             Step;
      Array2D<T>    LineDirc;
      T             RunProj;
      T             DecreaseFac;
      T             CurvatureFac;
      T             GradThreshold;
      unsigned int  LineSearchCount;

      LineMinimizerCommon()
        : MemSys(),RunSys(),Step(0),LineDirc(),RunProj(0),DecreaseFac(1e-4),
          CurvatureFac(0.4),GradThreshold(RelDelta<T>()), LineSearchCount(0U) {}
      ~LineMinimizerCommon() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               RunSys.IsValid()&&MemSys.IsValid()&&LineDirc.IsValid();
      }

      void Load(System<T,IDT,PT,GT,BT,CT>& S) {
        Clear(*this);
        static_cast<ParentType*>(this)->Load(S);
        static_cast<SystemContentWithEG<T>&>(MemSys.Content).Allocate(
            S.Content.X);
        static_cast<SystemContentWithEG<T>&>(RunSys.Content).Allocate(
            S.Content.X);
        Imprint(LineDirc,S.Content.X);
        MemSys.Content.Velocity.Refer(LineDirc);
        RunSys.Content.Velocity.Refer(LineDirc);
        MemSys.Interactions.Allocate(S.Interactions.Size());
        RunSys.Interactions.Allocate(S.Interactions.Size());
        for(unsigned int i=0;i<S.Interactions.Size();++i) {
          MemSys.Interactions[i].Func.Refer(this->Sys.Interactions[i].Func);
          RunSys.Interactions[i].Func.Refer(this->Sys.Interactions[i].Func);
          MemSys.Interactions[i].ID.Refer(this->Sys.Interactions[i].ID);
          RunSys.Interactions[i].ID.Refer(this->Sys.Interactions[i].ID);
          MemSys.Interactions[i].Param.Refer(this->Sys.Interactions[i].Param);
          RunSys.Interactions[i].Param.Refer(this->Sys.Interactions[i].Param);
          MemSys.Interactions[i].Buffer.Refer(this->Sys.Interactions[i].Buffer);
          RunSys.Interactions[i].Buffer.Refer(this->Sys.Interactions[i].Buffer);
          MemSys.Interactions[i].Geom.Refer(this->Sys.Interactions[i].Geom);
          RunSys.Interactions[i].Geom.Refer(this->Sys.Interactions[i].Geom);
          MemSys.Interactions[i].EGData.Allocate(S.Content.X);
          RunSys.Interactions[i].EGData.Allocate(S.Content.X);
        }
        MemSys.Propagtors.Allocate(S.Propagtors.Size());
        RunSys.Propagtors.Allocate(S.Propagtors.Size());
        for(unsigned int i=0,n;i<S.Propagtors.Size();++i) {
          SystemPropagatorMethodName SPN;
          switch(this->Sys.Propagtors[i].Method) {
            case  SystemFixPosition:
            case SystemMinimizerLineRegular:
              SPN=this->Sys.Propagtors[i].Method;
              break;
            case SystemToBeDetermined:
              SPN=SystemMinimizerLineRegular;
              break;
            default:
              fprintf(stderr,"Improper Propagator Method!\n");
              SPN=SystemPropagatorUnassigned;
          }
          MemSys.Propagators[i].Allocate(SPN);
          RunSys.Propagators[i].Allocate(SPN);
          MemSys.Propagators[i].IDRange.Refer(this->Sys.Propagators[i].IDRange);
          RunSys.Propagators[i].IDRange.Refer(this->Sys.Propagators[i].IDRange);
          n=S.Propagators[i].IDRange.Size();
          MemSys.Propagators[i].GrpContent.Allocate(n);
          RunSys.Propagators[i].GrpContent.Allocate(n);
          MemSys.Propagators[i]._Build(MemSys.Content);
          RunSys.Propagators[i]._Build(RunSys.Content);
          switch(SPN) {
            case SystemFixPosition: break;
            case SystemMinimizerLineRegular:
              Pointer<T>(
                  MemSys.Propagators[i].Param[MinimizerLineRegularPtrStep])
                =&Step;
              Pointer<T>(
                  RunSys.Propagators[i].Param[MinimizerLineRegularPtrStep])
                =&Step;
              break;
            default:
              fprintf(stderr,"Improper Propagator Method!\n");
          }
        }
        MemSys._Build();
        RunSys._Build();
        MemSys._Init();
        RunSys._Init();
      }

      T MinimalStep() {
        assert(IsSameStructure(RunSys.Content.X,RunSys.Content.Velocity));
        unsigned int n=RunSys.Content.X._ldata.Size();
        T mstep,tmd,tmd1;
        for(unsigned int i=0;i<n;++i) {
          tmd=absval(RunSys.Content.X._ldata[i]);
          tmd1=RunSys.Content.Velocity._ldata[i];
          tmd=(tmd<1?tmd1:tmd1/tmd);
          mstep+=Square(tmd);
        }
        return RelDelta<T>()*sqroot(this->DOF/mstep);
      }

    private:

      LineMinimizerCommon(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void Clear(LineMinimizerCommon<T,IDT,PT,GT,BT,CT>& M) {
    typedef typename LineMinimizerCommon<T,IDT,PT,GT,BT,CT>::ParentType Type;
    Clear(M.MemSys);
    Clear(M.RunSys);
    M.Step=0.;
    Clear(M.LineDirc);
    M.RunProj=0.;
    M.DecreaseFac=1e-4;
    M.CurvatureFac=0.4;
    M.GradThreshold=RelDelta<T>();
    M.LineSearchCount=0;
    Clear(static_cast<Type&>(M));
  }

}

#ifndef _LOAD4XE
#define _LOAD4XE \
  BlasCopy(M.MemSys.Content.X,M.Sys.Content.X); \
  Copy(M.MemSys.Content.EGData.Energy[0],M.Sys.Content.EGData.Energy[0]);
#else
#error "Duplicate Definition for Macro _LOAD4XE"
#endif

#ifndef _LOAD
#define _LOAD(CType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT> \
  void _Load2Mem(LineMinimizerCommon<T,IDT,PT,GT,BT,CType>& M) { \
    _LOAD4XE \
    EvaluateGradient(M.MemSys.Content,M.MemSys.Interactions); \
    M.GCalcCount++; \
  }
#else
#error "Duplicate Definition for Macro _LOAD"
#endif


namespace mysimulator {

  _LOAD(SystemContentWithE)
  _LOAD(SystemContentWithEV)

}

#ifdef _LOAD
#undef _LOAD
#endif

#ifndef _LOAD
#define _LOAD(CType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT> \
  void _Load2Mem(LineMinimizerCommon<T,IDT,PT,GT,BT,CType>& M) { \
    _LOAD4XE \
    BlasCopy(M.MemSys.Content.EGData.Gradient,M.Sys.Content.EGData.Gradient); \
  }
#else
#error "Duplicate Definition for Macro _LOAD"
#endif

namespace mysimulator {

  _LOAD(SystemContentWithEG)
  _LOAD(SystemContentWithEGV)

}

#ifdef _LOAD
#undef _LOAD
#endif

#ifdef _LOAD4XE
#undef _LOAD4XE
#endif

#ifndef _WRITE4XE
#define _WRITE4XE \
  BlasCopy(M.Sys.Content.X,M.MemSys.Content.X); \
  Copy(M.Sys.Content.EGData.Energy[0],M.MemSys.Content.EGData.Energy[0]);
#else
#error "Duplicate Definition for Macro _WRITE4XE"
#endif

#ifndef _WRITE
#define _WRITE(CType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT> \
  void _Write2Sys(LineMinimizerCommon<T,IDT,PT,GT,BT,CType>& M) { _WRITE4XE }
#else
#error "Duplicate Definition for Macro _WRITE"
#endif

namespace mysimulator {

  _WRITE(SystemContentWithE)
  _WRITE(SystemContentWithEV)

}

#ifdef _WRITE
#undef _WRITE
#endif

#ifndef _WRITE
#define _WRITE(CType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT> \
  void _Write2Sys(LineMinimizerCommon<T,IDT,PT,GT,BT,CType>& M) { \
    _WRITE4XE \
    BlasCopy(M.Sys.Content.EGData.Gradient,M.MemSys.Content.EGData.Gradient); \
  }
#else
#error "Duplicate Definition for Macro _WRITE"
#endif

namespace mysimulator {

  _WRITE(SystemContentWithEG)
  _WRITE(SystemContentWithEGV)

}

#ifdef _WRITE
#undef _WRITE
#endif

#ifdef _WRITE4XE
#undef _WRITE4XE
#endif

#endif

