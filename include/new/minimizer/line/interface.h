
#ifndef _Minimizer_Line_Interface_H_
#define _Minimizer_Line_Interface_H_

#include "minimizer/line/method-name.h"
#include "minimizer/line/condition/method-name.h"
#include "io/error.h"

namespace mysimulator {

  template <LineMinimizerMethodName LM,
            typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType,
            LineMinimizerConditionMethodName LCM=StrongWolfe>
  struct LineMinimizer {

    public:

      typedef
      LineMinimizer<LM,T,IDType,ParamType,GeomType,VecType,SysContentType,LCM>
      Type;

      LineMinimizer() { Error("Unknown Method for Line Minimizer"); }
      ~LineMinimizer() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

    private:

      LineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerMethodName LM,
            typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void release(LineMinimizer<LM,T,IDT,PT,GT,VT,SCT,LCM>& M) { M.clearData(); }

  template <LineMinimizerMethodName LM,
            typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  bool IsValid(const LineMinimizer<LM,T,IDT,PT,GT,VT,SCT,LCM>& M) {
    return M.isvalid();
  }

}

#include "minimizer/line/tracking/specification.h"

#endif

