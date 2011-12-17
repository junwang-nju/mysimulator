
#ifndef _Minimizer_Line_Common_Interface_H_
#define _Minimizer_Line_Common_Interface_H_

#include "minimizer/base/interface.h"
#include "system/content/with-egv/interface.h"
#include "minimizer/line/common/get-minimal-step.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct LineMinimizerCommon
    : public MinimizerBase<T,IDType,ParamType,GeomType,VecType,SysContentType> {

    public:

      typedef
        LineMinimizerCommon<T,IDType,ParamType,GeomType,VecType,SysContentType>
        Type;
      typedef MinimizerBase<T,IDType,ParamType,GeomType,VecType,SysContentType>
              ParentType;
      typedef System<T,IDType,ParamType,GeomType,VecType,SysContentWithEGV>
              SysType;

      Object<SysType> MemSys;
      Object<SysType> RunSys;
      T Step;
      Object<VecType<T> > LineDirc;
      T RunProj;
      T DecreaseFac;
      T CurvatureFac;
      T GradientThreshold;
      unsigned int LineSearchCount;

      LineMinimizerCommon()
        : MemSys(), RunSys(), Step(0), LineDirc(), RunProj(0),
          DecreaseFac(1e-4), CurvatureFac(0.4),
          GradientThreshold(RelativeDelta<T>()), LineSearchCount(0U) {}
      ~LineMinimizerCommon() { clearData(); }

      void clearData() {
        LineSearchCount=0U;
        GradientThreshold=RelativeDelta<T>();
        CurvatureFac=0.4;
        DecreaseFac=1e-4;
        RunProj=0;
        Step=0;
        release(RunSys);
        release(MemSys);
        release(LineDirc);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<ParentType*>(this)->isvalid()&&IsValid(RunSys)&&
               IsValid(MemSys)&&IsValid(LineDirc);
      }

      T MininalStep() {
        return getMinimalStep(RunSys.SysContent().X(),RunSys.SysContent().V(),
                              this->DOF);
      }

      void _load();
      void _write();

    private:

      LineMinimizerCommon(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(LineMinimizerCommon<T,IDT,PT,GT,VT,SCT>& M) { M.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const LineMinimizerCommon<T,IDT,PT,GT,VT,SCT>& M) {
    return M.isvalid();
  }

}

#define _LoadOperateXE \
  copy(M.MemSys().Content().X(),M.Sys().Content().X());\
  copy(M.MemSys().Content().Energy(),M.Sys().Content().Energy());

#include "system/content/with-ev/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _load(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithE>& M) {
    _LoadOperateXE
    sync(M.MemSys().Content(),M.MemSys().Interaction());
    M.GCalcCount++;
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _load(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEV>& M) {
    _LoadOperateXE
    sync(M.MemSys().Content(),M.MemSys().Interaction());
    M.GCalcCount++;
  }

  /*
  void LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithE>::_load() {
    _LoadOperateXE
    sync(MemSys().Content(),MemSys().Interaction());
    this->GCalcCount++;
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEV>::_load() {
    _LoadOperateXE
    sync(MemSys().Content(),MemSys().Interaction());
    this->GCalcCount++;
  }
  */

}

#define _LoadOperateXEG \
  _LoadOperateXE \
  copy(M.MemSys().Content().Gradient(),M.Sys().Content().Gradient());

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _load(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEG>& M) {
    _LoadOperateXEG
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _load(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEGV>& M) {
    _LoadOperateXEG
  }

  /*
  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEG>::_load() {
    _LoadOperateXEG
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEGV>::_load() {
    _LoadOperateXEG
  }
  */

}

#undef _LoadOperateXEG
#undef _LoadOperateXE

#define _WriteOperateXE \
  copy(M.Sys().Content().X(),M.MemSys().Content().X());\
  copy(M.Sys().Content().Energy(),M.MemSys().Content().Energy());

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _write(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithE>& M) {
    _WriteOperateXE
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _write(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEV>& M) {
    _WriteOperateXE
  }

}

#define _WriteOperateXEG \
  _WriteOperateXE \
  copy(M.Sys().Content().Gradient(),M.MemSys().Content().Gradient());

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _write(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEG>& M) {
    _WriteOperateXEG
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void _write(LineMinimizerCommon<T,IDT,PT,GT,VT,SysContentWithEGV>& M) {
    _WriteOperateXEG
  }

}

#undef _WriteOperateXEG
#undef _WriteOperateXE

#endif

