
#ifndef _Minimizer_Line_Common_Interface_H_
#define _Minimizer_Line_Common_Interface_H_

#include "minimizer/base/interface.h"
#include "system/content/with-egv/interface.h"
#include "minimizer/line/common/get-minimal-step.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType, template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct LineMinimizerCommon
    : public MinimizerBase<T,IDType,ParamType,GeomType,BufferType,
                           VecType,SysContentType> {

    public:

      typedef
      LineMinimizerCommon<T,IDType,ParamType,GeomType,BufferType,
                          VecType,SysContentType>
      Type;
      typedef MinimizerBase<T,IDType,ParamType,GeomType,VecType,SysContentType>
              ParentType;
      typedef System<T,IDType,ParamType,GeomType,BufferType,
                     VecType,SysContentWithEGV>
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
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(RunSys)&&IsValid(MemSys)&&IsValid(LineDirc);
      }

      T MininalStep() {
        return getMinimalStep(RunSys().Content().X(),
                              RunSys().Content().Velocity(),this->DOF);
      }

    private:

      LineMinimizerCommon(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(LineMinimizerCommon<T,IDT,PT,GT,BT,VT,SCT>& M) { M.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const LineMinimizerCommon<T,IDT,PT,GT,BT,VT,SCT>& M) {
    return M.isvalid();
  }

}

#define _LoadOperateXE \
  copy(M.MemSys().Content().X(),M.Sys().Content().X());\
  copy(M.MemSys().Content().EGData.Energy(),M.Sys().Content().EGData.Energy());

#define _LoadXE(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class VT> \
  void _load(LineMinimizerCommon<T,IDT,PT,GT,BT,VT,SCType>& M) { \
    _LoadOperateXE \
    GenericEvaluateGradient(M.MemSys().Content(),M.MemSys().Interactions);\
    M.GCalcCount++;\
  }

#include "system/content/with-ev/interface.h"
#include "system/evaluate/gradient.h"

namespace mysimulator {

  _LoadXE(SysContentWithE)
  _LoadXE(SysContentWithEV)

}

#undef LoadXE

#define _LoadXEG(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class VT> \
  void _load(LineMinimizerCommon<T,IDT,PT,GT,BT,VT,SCType>& M) { \
    _LoadOperateXE \
    copy(M.MemSys().Content().EGData.Gradient(),\
         M.Sys().Content().EGData.Gradient()); \
  }

namespace mysimulator {

  _LoadXEG(SysContentWithEG)
  _LoadXEG(SysContentWithEGV)

}

#undef _LoadXEG
#undef _LoadOperateXE

#define _WriteOperateXE \
  copy(M.Sys().Content().X(),M.MemSys().Content().X());\
  copy(M.Sys().Content().EGData.Energy(),M.MemSys().Content().EGData.Energy());

#define _WriteXE(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class VT>\
  void _write(LineMinimizerCommon<T,IDT,PT,GT,BT,VT,SCType>& M) { \
    _WriteOperateXE \
  }

namespace mysimulator {

  _WriteXE(SysContentWithE)
  _WriteXE(SysContentWithEV)

}

#undef _WriteXE

#define _WriteXEG(SCType) \
  template <typename T,typename IDT,typename PT,typename GT,typename BT,\
            template<typename> class VT> \
  void _write(LineMinimizerCommon<T,IDT,PT,GT,BT,VT,SCType>& M) { \
    _WriteOperateXE \
    copy(M.Sys().Content().EGData.Gradient(),\
         M.MemSys().Content().EGData.Gradient()); \
  }

namespace mysimulator {

  _WriteXEG(SysContentWithEG)
  _WriteXEG(SysContentWithEGV)

}

#undef _WriteXEG
#undef _WriteOperateXE

#endif

