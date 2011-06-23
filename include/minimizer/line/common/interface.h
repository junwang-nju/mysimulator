
#ifndef _Minimizer_Line_Common_Interface_H_
#define _Minimizer_Line_Common_Interface_H_

#include "minimizer/base/interface.h"
#include "intrinsic-type/constant.h"
#include "intrinsic-type/abs-value.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename IKernelType,template<typename> class SpaceVType,
            typename IParamType,typename T>
  struct LineMinimizerCommon
      : public MinimizerBase<IKernelType,SpaceVType,IParamType,T> {

    typedef LineMinimizerCommon<IKernelType,SpaceVType,IParamType,T>   Type;
    typedef MinimizerBase<IKernelType,SpaceVType,IParamType,T>    ParentType;

    Object<SpaceVType<T> >    RunX;
    Object<SpaceVType<T> >    RunG;
    SpaceVType<T>             LineDirc;
    unsigned int              LineSearchCount;
    T                         RunEnergy;
    T                         RunProject;
    T                         DecreaseFac;
    T                         CurvatureFac;
    T                         GradThreshold;

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
      return CalcMinimalStep(this->MinX(),LineDirc,this->MinUMask,this->DOF);
    }

    virtual int Go(const unsigned int)=0;

  };

  template <typename KT,template<typename> class VT,typename PT,typename T>
  bool IsValid(const LineMinimizerCommon<KT,VT,PT,T>& L) {
    typedef MinimizerBase<KT,VT,PT,T>    Type;
    return IsValid(static_cast<const Type&>(L))&&
           IsValid(L.RunX)&&IsValid(L.RunX())&&IsValid(L.RunG)&&
           IsValid(L.RunG())&&IsValid(L.LineDirc);
  }

  template <typename KT,template<typename> class VT,typename PT,typename T>
  void release(LineMinimizerCommon<KT,VT,PT,T>& L) { L.clearData(); }

}

#include "list/interface.h"

namespace mysimulator {

  template <template<typename> class VT, typename T>
  T CalcMinimalStep(const VT<T>&,const VT<T>&,const VT<unsigned int>&,
                    const unsigned int&) {
    Error("Minimal-Step Calculation for this VType Not Implemented!");
    return static_cast<T>(cZero);
  }

  template <typename T>
  T CalcMinimalStep(const Vector<T>& X, const Vector<T>& D,
                    const Vector<unsigned int>& M, const unsigned int& F) {
    assert(IsValid(X)&&IsValid(D)&&IsValid(M));
    T mstep;
    T tmd;
    copy(mstep,0.);
    for(unsigned int i=0;i<M.size;++i) {
      if(M[i]==0)    continue;
      tmd=absval(X[i]);
      tmd=(tmd<1.?D[i]:D[i]/tmd);
      mstep+=tmd*tmd;
    }
    return RelativeDelta<T>()*sqroot(F/mstep);
  }


  template <typename T>
  T CalcMinimalStep(const List<T>& X, const List<T>& D,
                    const List<unsigned int>& M, const unsigned int& F) {
    assert(IsValid(X)&&IsValid(D)&&IsValid(M));
    return CalcMinimalStep(static_cast<const Vector<T>&>(X),
                           static_cast<const Vector<T>&>(D),
                           static_cast<const Vector<unsigned int>&>(M),F);
  }    

}

#endif

