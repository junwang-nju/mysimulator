
#ifndef _Minimizer_Steep_Interface_H_
#define _Minimizer_Steep_Interface_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"
//#include "array/2d/norm.h"
//#include "array/2d/scale.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  struct Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,BT,CT,LMC>
      : public LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC> {

    public:

      typedef Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,BT,CT,LMC>  Type;
      typedef LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC>  ParentType;

      static const unsigned int DefaultMaxSteps;

      Minimizer() : ParentType() {}
      ~Minimizer() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

      void Load(System<T,IDT,PT,GT,BT,CT>& S) {
        static_cast<ParentType*>(this)->Load(S);
      }

      int Go(unsigned int MaxSteps=DefaultMaxSteps) {
        this->GCalcCount=0;
        this->LineSearchCount=0;
        _Load2Mem(*this);
        T tmd,tmd2;
        int fg=0, lfg;
        for(unsigned int nr=0;nr<MaxSteps;++nr) {
          BlasCopy(this->LineDirc,this->MemSys->Content.EGData.Gradient);
          tmd=Norm(this->LineDirc);
          if(tmd<this->GradThreshold) { fg=3; break; }
          Scale(this->LineDirc,-1./tmd);
          this->Proj=-tmd;
          tmd=this->MemSys->Content.EGData.Energy[0];
          lfg=static_cast<ParentType*>(this)->Go();
          this->LineSearchCount++;
          if(lfg==2) {  fg=1; break; }
          else if(lfg==0) { fg=4; break; }
          else {
            tmd2=this->MemSys->Content.EGData.Energy[0];
            if(2*absval(tmd-tmd2)<=absval(tmd+tmd2)*RelDelta<T>()) {
              fg=2; break;
            }
          }
        }
        _Write2Sys(*this);
        return fg;
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  void Clear(Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,BT,CT,LMC>& M) {
    typedef
    typename Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,BT,CT,LMC>::ParentType
    Type;
    Clear(static_cast<Type&>(M));
  }

}

#endif

