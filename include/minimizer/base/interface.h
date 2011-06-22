
#ifndef _Minimizer_Base_Interface_H_
#define _Minimizer_Base_Interface_H_

#include "minimizer/data-base/interface.h"
#include "referable-object/interface.h"

namespace mysimulator {

  template <typename InteractionFuncType, template<typename> class SpaceVType,
            typename InteractionParamType,typename T>
  struct MinimizerBase {

    typedef InteractionFuncType   IFType;
    typedef InteractionParamType  IPType;
    typedef MinimizerBase<IFType,SpaceVType,IPType,T>   Type;

    Object<MinimizerDataBase<IFType,SpaceVType,IPType,T> >  Data;

    MinimizerBase() : Data() {}
    MinimizerBase(const Type&) { Error("Copier of MinimizerBase Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MinimizerBase Disabled!");
      return *this;
    }
    ~MinimizerBase() { clearData(); }

    void clearData() { release(Data); }

    virtual int Go(const unsigned int)=0;

  };    

  template <typename FT,template<typename> class VT, typename PT, typename T>
  bool IsValid(const MinimizerBase<FT,VT,PT,T>& M) {
    return IsValid(M.Data)&&IsValid(M.Data());
  }

  template <typename FT,template<typename> class VT, typename PT, typename T>
  void release(MinimizerBase<FT,VT,PT,T>& M) { M.clearData(); }

}

#endif

