
#ifndef _Minimizer_Line_Interface_H_
#define _Minimizer_Line_Interface_H_

#include "minimizer/line/condition/method-name.h"
#include "minimizer/line/method-name.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC=StrongWolfe>
  struct LineMinimizer {

    public:

      typedef LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC>  Type;

      LineMinimizer() { fprintf(stderr,"Unknown Method for LineMinimizer!\n"); }
      ~LineMinimizer() { Clear(*this); }

      bool IsValid() const { return false; }

    private:

      LineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerMethodName LMC>
  void Clear(LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC>& M) {}


}

#include "minimizer/line/tracking/interface.h"

#endif

