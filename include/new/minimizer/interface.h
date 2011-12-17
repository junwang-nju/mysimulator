
#ifndef _Minimizer_Interface_H_
#define _Minimizer_Interface_H_

#include "minimizer/method-name.h"
#include "minimizer/line/method-name.h"
#include "minimizer/line/condition/method-name.h"

namespace mysimulator {

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN,
            typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType,
            LineMinimizerConditionMethodName LCM=StrongWolfe>
  struct Minimizer {

    public:
      typedef
      Minimizer<MN,LMN,T,IDType,ParamType,GeomType,VecType,SysContentType,LCM>
      Type;

      Minimizer() { Error("This type of Minimizer Not Available!"); }
      ~Minimizer() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN,
            typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void release(Minimizer<MN,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M) { M.clearData(); }

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN,
            typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  bool IsValid(const Minimizer<MN,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M) {
    return M.isvalid();
  }

}

#include "minimizer/steep/specification.h"
#include "minimizer/conjg/specification.h"
#include "minimizer/lbfgs/specification.h"

#endif

