
#ifndef _Minimizer_Line_Common_Interface_H_
#define _Minimizer_Line_Common_Interface_H_

#include "minimizer/base/interface.h"
#include "minimizer/line/common/minimal-step.h"

namespace mysimulator {

  template <typename T, typename FuncType, typename IDType, typename ParamType,
            typename GeomType, template <typename> class SpaceType>
  struct LineMinimizerCommon
      : public MinimizerBase<T,FuncType,IDType,ParamType,GeomType,SpaceType> {

    public:

      typedef
        LineMinimizerCommon<T,FuncType,IDType,ParamType,GeomType,SpaceType>
        Type;
      typedef MinimizerBase<T,FuncType,IDType,ParamType,GeomType,SpaceType>
        ParentType;

      Object<SpaceType<T> > RunX;
      Object<SpaceType<T> > RunG;
      SpaceType<T>  LineDirc;
      unsigned int LineSearchCount;
      T RunEnergy;
      T RunProj;
      T DecFac;
      T CurvFac;
      T GradThreshold;

      LineMinimizerCommon()
        : RunX(), RunG(), LineDirc(), LineSearchCount(0), RunEnergy(0),
          RunProj(0), DecFac(1e-4), CurvFac(0.4),
          GradThreshold(RelativeDelta<T>()) {}
      ~LineMinimizerCommon() { clearData(); }

      void clearData() {
        release(RunX);  release(RunG);  release(LineDirc);  LineSearchCount=0;
        RunEnergy=0;  RunProj=0;  DecFac=1e-4;  CurvFac=0.4;
        GradThreshold=RelativeDelta<T>();
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(RunX)&&IsValid(RunG)&&IsValid(LineDirc);
      }

      T MinimalStep() const {
        return MinimalStepCalc<SpaceType,T>::Do(
            this->Sys().X(),LineDirc,this->Sys().UMask);
      }

      virtual int Go(const unsigned int&) = 0;

    private:

      LineMinimizerCommon(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template <typename> class ST>
  bool IsValid(const LineMinimizerCommon<T,FT,IDT,PT,GT,ST>& M) {
    return M.isvalid();
  }

  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template <typename> class ST>
  void release(LineMinimizerCommon<T,FT,IDT,PT,GT,ST>& M) { M.clearData(); }

}

#endif

