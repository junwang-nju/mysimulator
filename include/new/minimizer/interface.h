
#ifndef _Minimizer_Interface_H_
#define _Minimizer_Interface_H_

#include "minimizer/name.h"
#include "minimizer/line/name.h"

namespace mysimulator {

  template <MinimizerName MinName, LineMinimizerName LMinName, typename T,
            typename FT, typename IDT, typename PT, typename GT,
            template <typename> class ST>
  struct Minimizer {

    public:

      typedef Minimizer<MinName,LMinName,T,FT,IDT,PT,GT,ST>   Type;

      ~Minimizer() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

      virtual int Go(const unsigned int&) { return 0; }

    private:

      Minimizer() {}
      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <MinimizerName MN, LineMinimizerName LMN, typename T, typename FT,
            typename IDT,typename PT,typename GT,template<typename> class ST>
  bool IsValid(const Minimizer<MN,LMN,T,FT,IDT,PT,GT,ST>& M) {
    return M.isvalid();
  }

  template <MinimizerName MN, LineMinimizerName LMN, typename T, typename FT,
            typename IDT,typename PT,typename GT,template<typename> class ST>
  void release(Minimizer<MN,LMN,T,FT,IDT,PT,GT,ST>& M) { M.clearData(); }

}

#include "minimizer/steep/specification.h"
#include "minimizer/conjg/specification.h"

#endif

