
#ifndef _Minimizer_Line_Common_Interface_H_
#define _Minimizer_Line_Common_Interface_H_

#include "minimizer/base/interface.h"
#include "intrinsic-type/constant.h"
#include "intrinsic-type/abs-value.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename IFuncType,template<typename> class SpaceVType,
            typename IParamType,typename T>
  struct LineMinimizerCommon
      : public MinimizerBase<IFuncType,SpaceVType,IParamType,T> {

    typedef LineMinimizerCommon<IFuncType,SpaceVType,IParamType,T>   Type;
    typedef MinimizerBase<IFuncType,SpaceVType,IParamType,T>    ParentType;

    SpaceVType<T>   RunX;
    SpaceVType<T>   RunG;
    SpaceVType<T>   LineDirc;
    unsigned int    LineSearchCount;
    T               RunEnergy;
    T               RunProject;
    T               DecreaseFac;
    T               CurvatureFac;
    T               GradThreshold;

    LineMinimizerCommon()
        : ParentType(), RunX(), RunG(), LineDirc(), LineSearchCount(0),
          RunEnergy(0.), RunProject(0.), DecreaseFac(1e-4), CurvatureFac(0.4),
          GradThreshold(RelativeDelta<T>()) {}
    LineMinimizerCommon(const Type&) {
      Error("Copier of LineMinimizerCommon Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LineMinimizerCommon Disabled!");
      return *this;
    }
    ~LineMinimizerCommon() { clearData(); }

    void clearData() {
      release(RunX); release(RunG); release(LineDirc);
      static_cast<ParentType*>(this)->clearData();
    }

    T MinimalStep() const {
      Error("Minimal Step is not available for this kind of SpaceVType!");
      return static_cast<T>(cZero);
    }

    virtual int Go(const unsigned int)=0;

  };

  template <typename FT,template<typename> class VT,typename PT,typename T>
  bool IsValid(const LineMinimizerCommon<FT,VT,PT,T>& L) {
    typedef MinimizerBase<FT,VT,PT,T>    Type;
    return IsValid(static_cast<const Type&>(L))&&
           IsValid(L.RunX)&&IsValid(L.RunG)&&IsValid(L.LineDirc);
  }

  template <typename FT,template<typename> class VT,typename PT,typename T>
  void release(LineMinimizerCommon<FT,VT,PT,T>& L) { L.clearData(); }

}

#include "list/interface.h"

namespace mysimulator {

  template <typename FT,typename PT,typename T>
  T LineMinimizerCommon<FT,Vector,PT,T>::MinimalStep() const {
    assert(IsValid(*this));
    T mstep;
    T tmd;
    copy(mstep,0.);
    for(unsigned int i=0;i<MinUMask.size;++i) {
      if(MinUMask[i]==0)    continue;
      tmd=absval(MinX[i]);
      tmd=(tmd<1.?LineDirc[i]:LineDirc/tmd);
      mstep+=tmd*tmd;
    }
    return RelativeDelta<T>()*sqroot(DOF/mstep);
  }


  template <typename FT,typename PT,typename T>
  T LineMinimizerCommon<FT,List,PT,T>::MinimalStep() {
    assert(IsValid(*this));
    T mstep;
    T tmd;
    copy(mstep,0.);
    const T *px=MinX.pdata;
    const T *pd=LineDirc.pdata;
    const unsigned int *pm=MinUMask.pdata;
    for(unsigned int i=0;i<MinUMask.NumElements();++i) {
      if(pm[i]==0)  continue;
      tmd=absval(px[i]);
      tmd=(tmd<1.?pd[i]:pd[i]/tmd);
      mstep+=tmd*tmd;
    }
    return RelativeDelta<T>()*sqroot(DOF/mstep);
  }    

}

#endif

