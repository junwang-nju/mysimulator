
#ifndef _Minimizer_Regular_Interface_H_
#define _Minimizer_Regular_Interface_H_

#include "minimizer/interface.h"
#include "array/2d/norm.h"
#include "array/2d/dot.h"
#include "array/2d/scale.h"
#include "array/2d/shift.h"
#include "array/2d/copy.h"

namespace mysimulator {

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN, typename T,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename> class> class SCT,
            LineMinimizerConditionMethodName LCM=StrongWolfe>
  struct MinimizerRegular
      : public Minimizer<MN,LMN,T,IDT,PT,GT,Array2D,SCT,LCM> {

    public:

      typedef MinimizerRegular<MN,LMN,T,IDT,PT,GT,SCT,LCM>    Type;
      typedef Minimizer<MN,LMN,T,IDT,PT,GT,Array2D,SCT,LCM>   ParentType;

      MinimizerRegular() : ParentType() {}
      ~MinimizerRegular() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }

    private:

      MinimizerRegular(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN, typename T,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename> class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void release(MinimizerRegular<MN,LMN,T,IDT,PT,GT,SCT,LCM>& M) {
    return M.clearData();
  }

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN, typename T,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename> class> class SCT,
            LineMinimizerConditionMethodName LCM>
  bool IsValid(const MinimizerRegular<MN,LMN,T,IDT,PT,GT,SCT,LCM>& M) {
    return M.isvalid();
  }

}

#endif

