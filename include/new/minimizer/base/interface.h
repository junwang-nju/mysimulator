
#ifndef _Minimizer_Base_Interface_H_
#define _Minimizer_Base_Interface_H_

#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct MinimizerBase {

    public:

      typedef MinimizerBase<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;

      Object<System<T,IDType,ParamType,GeomType,VecType,SysContentType> > Sys;
      T Proj;
      T Move;
      T SearchScale;
      unsigned int GCalcCount;
      unsigned int DOF;

      MinimizerBase()
          : Sys(),Proj(0),Move(0),SearchScale(0.1),GCalcCount(0U),DOF(0U) {}
      ~MinimizerBase() { clearData(); }

      void clearData() {
        DOF=0U;
        GCalcCount=0U;
        SearchScale=0.1;
        Move=0;
        Proj=0;
        release(Sys);
      }
      bool isvalid() const { return IsValid(Sys); }

    private:

      MinimizerBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void release(MinimizerBase<T,IDT,PT,GT,VT,SCT>& M) { M.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  bool IsValid(const MinimizerBase<T,IDT,PT,GT,VT,SCT>& M) {
    return M.isvalid();
  }

}

#endif

