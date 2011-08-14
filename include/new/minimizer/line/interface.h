
#ifndef _Minimizer_Line_Interface_H_
#define _Minimizer_Line_Interface_H_

#include "minimizer/line/name.h"

namespace mysimulator {

  template <LineMinimizerName LMName, typename T, typename FT, typename IDT,
            typename PT, typename GT, template <typename> class ST>
  struct LineMinimizer {

    public:

      typedef LineMinimizer<LMName,T,FT,IDT,PT,GT,ST>   Type;

      ~LineMinimizer() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

      virtual int Go(const unsigned int) { return 0; }

    private:

      LineMinimizer() {}
      LineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerName LMName, typename T, typename FT, typename IDT,
            typename PT, typename GT, template <typename> class ST>
  bool IsValid(const LineMinimizer<LMName,T,FT,IDT,PT,GT,ST>& M) {
    return M.isvalid();
  }

  template <LineMinimizerName LMName, typename T, typename FT, typename IDT,
            typename PT, typename GT, template <typename> class ST>
  void release(LineMinimizer<LMName,T,FT,IDT,PT,GT,ST>& M) { M.clearData(); }

}

#include "minimizer/line/tracking/specification.h"

#endif

