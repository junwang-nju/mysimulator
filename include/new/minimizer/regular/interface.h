
#ifndef _Minimizer_Regular_Interface_H_
#define _Minimizer_Regular_Interface_H_

#include "minimizer/interface.h"
#include "array/2d/norm.h"
#include "array/2d/scale.h"
#include "array/2d/copy.h"
#include "array/2d/shift.h"
#include "array/2d/dot.h"

namespace mysimulator {

  template <MinimizerName MinName, LineMinimizerName LMinName, typename T,
            typename FT, typename IDT, typename PT, typename GT>
  struct MinimizerRegular
      : public Minimizer<MinName,LMinName,T,FT,IDT,PT,GT,Array2D> {

    public:

      typedef MinimizerRegular<MinName,LMinName,T,FT,IDT,PT,GT>   Type;
      typedef Minimizer<MinName,LMinName,T,FT,IDT,PT,GT,Array2D>  ParentType;

      MinimizerRegular() : ParentType() {}
      ~MinimizerRegular() { this->clearData(); }

    private:

      MinimizerRegular(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <MinimizerName MN, LineMinimizerName LMN, typename T,
            typename FT, typename IDT, typename PT, typename GT>
  bool IsValid(const MinimizerRegular<MN,LMN,T,FT,IDT,PT,GT>& M) {
    return M.isvalid();
  }

  template <MinimizerName MN, LineMinimizerName LMN, typename T,
            typename FT, typename IDT, typename PT, typename GT>
  void release(MinimizerRegular<MN,LMN,T,FT,IDT,PT,GT>& M) { M.clearData(); }

}

#endif

