
#ifndef _Minimizer_Steep_Specification_H_
#define _Minimizer_Steep_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerName LMinName, typename T,typename FT,typename IDT,
            typename PT,typename GT,template <typename> class ST>
  struct Minimizer<SteepestDescent,LMinName,T,FT,IDT,PT,GT,ST>
    : public LineMinimizer<LMinName,T,FT,IDT,PT,GT,ST> {

    public:

      typedef Minimizer<SteepestDescent,LMinName,T,FT,IDT,PT,GT,ST> Type;
      typedef LineMinimizer<LMinName,T,FT,IDT,PT,GT,ST>   ParentType;

      static const unsigned int DefaultMaxIterations;

      Minimizer() : ParentType() {}
      ~Minimizer() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }

      virtual int Go(const unsigned int& MaxIt=DefaultMaxIterations) {
        assert(isvalid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        T tmd;
        int f=0, lf;
        for(unsigned int nite=0;nite<MaxIt;++nite) {
          copy(this->LineDirc,this->G);
          tmd=norm(this->LineDirc);
          if(tmd<this->GradThreshold) {
            this->LineSearchCount=nite; f=3; break;
          }
          scale(this->LineDirc,-1./tmd);
          this->Proj=-tmd;
          tmd=this->Energy;
          lf=static_cast<ParentType*>(this)->_Go();
          if(lf==2) { this->LineSearchCount=nite; f=1; break; }
          else if(lf==0) { this->LineSearchCount=nite; f=4; break; }
          if(2*absval(tmd-this->Energy)<=
             absval(tmd+this->Energy)*RelativeDelta<T>()) {
            this->LineSearchCount=nite; f=2;  break;
          }
        }
        if(f==0)  this->LineSearchCount=MaxIt;
        return f;
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerName LMinName, typename T,typename FT,typename IDT,
            typename PT,typename GT,template <typename> class ST>
  const unsigned int
  Minimizer<SteepestDescent,LMinName,T,FT,IDT,PT,GT,ST>::DefaultMaxIterations
  =10000;

}

#endif

