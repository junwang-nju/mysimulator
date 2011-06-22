
#ifndef _Minimizer_Data_Base_Interface_H_
#define _Minimizer_Data_Base_Interface_H_

#include "unique-parameter/64bit/interface.h"
#include "vector/interface.h"

namespace mysimulator {

  template <typename InteractionKernelType,template<typename> class SpaceVType,
            typename InteractionParamType, typename T>
  struct MinimizerDataBase {

    typedef InteractionKernelType   IKType;
    typedef InteractionParamType    IPType;
    typedef MinimizerDataBase<IKType,SpaceVType,IPType,T>  Type;

    InteractionKernelType MinFunc;
    SpaceVType<T>         MinX;
    SpaceVType<T>         MinG;
    InteractionParamType  MinP;
    SpaceVType<T>         MinMask;
    SpaceVType<unsigned int>  MinUMask;
    T                     MinEnergy;
    T                     MinProject;
    T                     MinMove;
    unsigned int          GCalcCount;
    T                     SearchScale;
    unsigned int          DOF;

    MinimizerDataBase()
      : MinFunc(), MinX(), MinG(), MinP(), MinMask(), MinUMask(), MinEnergy(0),
        MinProject(), MinMove(0), GCalcCount(0), SearchScale(0.1), DOF(0) {}
    MinimizerDataBase(const Type&) {
      Error("Copier of MinimizerDataBase Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MinimizerDataBase Disabled!");
      return *this;
    }
    ~MinimizerDataBase() { clearData(); }

    void clearData() {
      release(MinFunc);   release(MinX);    release(MinG);
      release(MinP);      release(MinMask); release(MinUMask);
      GCalcCount=0;       DOF=0;
    }

  };

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  bool IsValid(const MinimizerDataBase<KT,VT,PT,T>& M) {
    return IsValid(M.MinFunc)&&IsValid(M.MinX)&&IsValid(M.MinG)&&
           IsValid(M.MinP)&&IsValid(M.MinMask)&&IsValid(M.MinUMask);
  }

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  void release(MinimizerDataBase<KT,VT,PT,T>& M) { M.clearData(); }

}

#endif

