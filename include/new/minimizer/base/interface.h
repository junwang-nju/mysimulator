
#ifndef _Minimizer_Base_Interface_H_
#define _Minimizer_Base_Interface_H_

#include "object/interface.h"
#include "system/interface.h"

namespace mysimulator {

  template <typename T, typename FuncType, typename IDType, typename ParamType,
            typename GeomType, template <typename> class SpaceType>
  struct MinimizerBase {

    public:

      typedef MinimizerBase<T,FuncType,IDType,ParamType,GeomType,SpaceType>
              Type;

      Object<System<T,FuncType,IDType,ParamType,GeomType,SpaceType> > Sys;
      T Proj;
      T Move;
      unsigned int GCalcCount;
      T SearchScale;
      unsigned int DOF;

      MinimizerBase() :
        Sys(), Proj(0), Move(0), GCalcCount(0), SearchScale(0.1), DOF(0) {}
      ~MinimizerBase() { clearData(); }

      void clearData() {
        release(Sys); Proj=0; Move=0; GCalcCount=0; SearchScale=0.1; DOF=0;
      }
      bool isvalid() const { return IsValid(Sys); }

      virtual int Go(const unsigned int&) = 0;

    private:

      MinimizerBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template <typename> class ST>
  bool IsValid(const MinimizerBase<T,FT,IDT,PT,GT,ST>& M) {
    return M.isvalid();
  }
            
  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template <typename> class ST>
  void release(MinimizerBase<T,FT,IDT,PT,GT,ST>& M) { M.clearData(); }

}

#endif

