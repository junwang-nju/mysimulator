
#ifndef _Minimizer_Base_Interface_H_
#define _Minimizer_Base_Interface_H_

#include "system/interface.h"
#include "system/DOF.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  struct MinimizerBase {

    public:

      typedef MinimizerBase<T,IDT,PT,GT,BT,CT>    Type;

      System<T,IDT,PT,GT,BT,CT> Sys;
      T Proj;
      T Move;
      T SearchScale;
      unsigned int GCalcCount;
      unsigned int DOF;

      MinimizerBase()
        : Sys(), Proj(0), Move(0), SearchScale(0.1), GCalcCount(0U), DOF(0U) {}
      ~MinimizerBase() { Clear(*this); }

      bool IsValid() const { return Sys.IsValid(); }

      void Load(System<T,IDT,PT,GT,BT,CT>& S) {
        Clear(*this);
        Sys.Refer(S);
        DOF=DegreeOfFreedom(S);
      }

    private:

      MinimizerBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void Clear(MinimizerBase<T,IDT,PT,GT,BT,CT>& M) {
    Clear(M.Sys);
    M.Proj=0.;
    M.Move=0.;
    M.SearchScale=0.1;
    M.GCalcCount=0U;
    M.DOF=0U;
  }

}

#endif

