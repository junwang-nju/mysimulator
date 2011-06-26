
#ifndef _Minimizer_SteepestDescent_Specification_H_
#define _Minimizer_SteepestDescent_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerName LMinName, typename IKernelType,
            template<typename> class SpaceVType,typename IParamType,typename T>
  struct Minimizer<SteepestDescent,LMinName,IKernelType,SpaceVType,IParamType,T>
      : public LineMinimizer<LMinName,IKernelType,SpaceVType,IParamType,T> {

    typedef IKernelType IKType;
    typedef IParamType  IPType;
    typedef Minimizer<SteepestDescent,LMinName,IKType,SpaceVType,IPType,T>
            Type;
    typedef LineMinimizer<LMinName,IKType,SpaceVType,IPType,T>  ParentType;

    static const unsigned int DefaultMaxIterations;

    Minimizer() : ParentType() {}
    Minimizer(const Type&) { Error("Copier of Minimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Minimizer Disabled!");
      return *this;
    }
    ~Minimizer() { clearData(); }

    void clearData() { static_cast<ParentType*>(this)->clearData(); }

    virtual int Go(const unsigned int MaxIt=DefaultMaxIterations) {
      assert(IsValid(*this));
      this->GCalcCount=0;
      this->LineSearchCount=0;
      T tmd;
      int f=0,lf;
      for(unsigned int neval=0;neval<MaxIt;++neval) {
        copy(this->LineDirc,this->MinG);
        tmd=norm(this->LineDirc);
        if(tmd<this->GradThreshold) { this->LineSearchCount=neval; f=3; break; }
        scale(this->LineDirc,-1./tmd);
        this->MinProject=-tmd;
        tmd=this->MinEnergy;
        lf=static_cast<ParentType*>(this)->_Go();
        if(lf==2) { this->LineSearchCount=neval; f=1; break; }
        else if(lf==0)  { this->LineSearchCount=neval; f=4; break; }
        if(2*absval(tmd-this->MinEnergy)<=
           absval(tmd+this->MinEnergy)*RelativeDelta<T>()) {
          this->LineSearchCount=neval;
          f=2;
          break;
        }
      }
      if(f==0)  this->LineSearchCount=MaxIt;
      return f;
    }

  };

  template <LineMinimizerName LMN,typename KT,template<typename> class VT,
            typename PT,typename T>
  const unsigned int
  Minimizer<SteepestDescent,LMN,KT,VT,PT,T>::DefaultMaxIterations=10000;

  template <LineMinimizerName LMN,typename KT,template<typename> class VT,
            typename PT,typename T>
  bool IsValid(const Minimizer<SteepestDescent,LMN,KT,VT,PT,T>& M) {
    typedef LineMinimizer<LMN,KT,VT,PT,T> Type;
    return IsValid(static_cast<const Type&>(M));
  }

  template <LineMinimizerName LMN,typename KT,template<typename> class VT,
            typename PT,typename T>
  void release(Minimizer<SteepestDescent,LMN,KT,VT,PT,T>& M) { M.clearData(); }

}

#endif

