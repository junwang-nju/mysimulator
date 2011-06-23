
#ifndef _Minimizer_Base_Interface_H_
#define _Minimizer_Base_Interface_H_

#include "referable-object/interface.h"

namespace mysimulator {

  template <typename InteractionKernelType, template<typename> class SpaceVType,
            typename InteractionParamType,typename T>
  struct MinimizerBase {

    typedef InteractionKernelType   IKType;
    typedef InteractionParamType  IPType;
    typedef MinimizerBase<IKType,SpaceVType,IPType,T>   Type;

    InteractionKernelType     MinFunc;
    Object<SpaceVType<T> >    MinX;
    Object<SpaceVType<T> >    MinG;
    InteractionParamType      MinP;
    SpaceVType<T>             MinMask;
    SpaceVType<unsigned int>  MinUMask;
    T                         MinEnergy;
    T                         MinProject;
    T                         MinMove;
    unsigned int              GCalcCount;
    T                         SearchScale;
    unsigned int              DOF;

    MinimizerBase()
      : MinFunc(), MinX(), MinG(), MinP(), MinMask(), MinUMask(), MinEnergy(0),
        MinProject(), MinMove(0), GCalcCount(0), SearchScale(0.1), DOF(0) {}
    MinimizerBase(const Type&) { Error("Copier of MinimizerBase Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MinimizerBase Disabled!");
      return *this;
    }
    ~MinimizerBase() { clearData(); }

    void clearData() {
      release(MinFunc);   release(MinX);    release(MinG);
      release(MinP);      release(MinMask); release(MinUMask);
      GCalcCount=0;       DOF=0;
    }

    virtual int Go(const unsigned int)=0;

  };    

  template <typename KT,template<typename> class VT, typename PT, typename T>
  bool IsValid(const MinimizerBase<KT,VT,PT,T>& M) {
    return IsValid(M.MinFunc)&&IsValid(M.MinX)&&IsValid(M.MinX())&&
           IsValid(M.MinG)&&IsValid(M.MinG())&&
           IsValid(M.MinP)&&IsValid(M.MinMask)&&IsValid(M.MinUMask);
  }

  template <typename KT,template<typename> class VT, typename PT, typename T>
  void release(MinimizerBase<KT,VT,PT,T>& M) { M.clearData(); }

}

#endif

