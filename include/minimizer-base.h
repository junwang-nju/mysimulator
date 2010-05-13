
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "error-proc.h"
#include "util.h"
#include "storage-state-name.h"
#include "memory.h"

namespace std {

  template <typename SpaceDataType, typename ParameterType>
  struct MinimizerKernelBase {

    typedef MinimizerKernelBase<SpaceDataType,ParameterType>  Type;
    typedef void (*EFuncType)(const SpaceDataType&, double&, ParameterType&);
    typedef void (*GFuncType)(const SpaceDataType&, SpaceDataType&,
                              ParameterType&);
    typedef void (*BFuncType)(const SpaceDataType&, SpaceDataType&, double&,
                              ParameterType&);

    EFuncType MinEFunc;
    GFuncType MinGFunc;
    BFuncType MinBFunc;
    SpaceDataType *MinCoor;
    SpaceDataType *MinGrad;
    double *MinEnergy;
    ParameterType *MinParam;
    double *MinProject;
    double *MinMove;
    unsigned int *GCalcCount;
    double *SearchScale;
    unsigned int state;

    MinimizerKernelBase()
      : MinEFunc(NULL), MinGFunc(NULL), MinBFunc(NULL), MinCoor(NULL),
        MinGrad(NULL), MinEnergy(NULL), MinParam(NULL), MinProject(NULL),
        MinMove(NULL), GCalcCount(NULL), SearchScale(NULL), state(Unused) {}
    MinimizerKernelBase(const Type&) {
      myError("Cannot create from MinimizerKernelBase");
    }
    Type& operator=(const Type& M) { assign(*this,M); return *this; }
    ~MinimizerKernelBase() { release(*this); }
  };

  template <typename SpaceDataType, typename ParameterType>
  void IsAvailable(const MinimizerKernelBase<SpaceDataType,ParameterType>& M) {
    return IsAvailable(M.MinCoor);
  }

  template <typename SpaceDataType, typename ParameterType>
  void release(MinimizerKernelBase<SpaceDataType,ParameterType>& M) {
    if(M.state==Allocated) {
      safe_delete(M.MinCoor);
      safe_delete(M.MinGrad);
      safe_delete(M.Energy);
      safe_delete(M.MinParam);
      safe_delete(M.MinProject);
      safe_delete(M.MinMove);
      safe_delete(M.GCalcCount);
      safe_delete(M.SearchScale);
    } else {
      M.MinCoor=NULL;
      M.MinGrad=NULL;
      M.MinEnergy=NULL;
      M.MinParam=NULL;
      M.MinProject=NULL;
      M.MinMove=NULL;
      M.GCalcCount=NULL;
      M.SearchScale=NULL;
    }
    M.MinEFunc=NULL;
    M.MinGFunc=NULL;
    M.MinBFunc=NULL;
    M.state=Unused;
  }

  template <typename SpaceDataType, typename ParameterType>
  void assign(MinimizerKernelBase<SpaceDataType,ParameterType>& dest,
              const MinimizerKernelBase<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    dest.MinEFunc=src.MinEFunc;
    dest.MinGFunc=src.MinGFunc;
    dest.MinBFunc=src.MinBFunc;
    *(dest.MinCoor)=*(src.MinCoor);
    *(dest.MinGrad)=*(src.MinGrad);
    *(dest.MinEnergy)=*(src.MinEnergy);
    *(dest.MinParam)=*(src.MinParam);
    *(dest.MinProject)=*(src.MinProject);
    *(dest.MinMove)=*(src.MinMove);
    *(dest.GCalcCount)=*(src.GCalcCount);
    *(dest.SearchScale)=*(src.SearchScale);
  }

  template <typename SpaceDataType, typename ParameterType>
  void allocate(MinimizerKernelBase<SpaceDataType,ParameterType>& M) {
    release(M);
    M.MinCoor=new SpaceDataType;
    M.MinGrad=new SpaceDataType;
    M.MinEnergy=new double;
    M.MinParam=new ParameterType;
    M.MinProject=new double;
    M.MinMove=new double;
    M.GCalcCount=new unsigned int;
    M.SearchScale=new double;
    M.state=Allocated;
    *(M.SearchScale)=0.1;
  }

  template <typename SpaceDataType, typename ParameterType>
  void refer(MinimizerKernelBase<SpaceDataType,ParameterType>& dest,
             const MinimizerKernelBase<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.MinEFunc=src.MinEFunc;
    dest.MinGFunc=src.MinGFunc;
    dest.MinBFunc=src.MinBFunc;
    dest.MinCoor=src.MinCoor;
    dest.MinGrad=src.MinGrad;
    dest.MinEnergy=src.MinEnergy;
    dest.MinParam=src.MinParam;
    dest.MinProject=src.MinProject;
    dest.MinMove=src.MinMove;
    dest.GCalcCount=src.GCalcCount;
    dest.SearchScale=src.SearchScale;
    dest.state=Reference;
  }

  template <typename SpaceDataType, typename ParameterType>
  void GenerateNewLocation(
      const MinimizerKernelBase<SpaceDataType,ParameterType>& M,
      const SpaceDataType& Origin, const SpaceDataType& Dirc,
      const double step, SpaceDataType& Dest, double& DestY,
      SpaceDataType& DestG, double& DestPrj) {
    assign(Dest,Origin);
    shift(Dest,step,Dirc);
    update(M.MinParam);
    M.MinBFunc(Dest,DestG,DestY,M.MinParam);
    ++M.GCalcCount;
    DestPrj=dot(DestG,Dirc);
  }

}

#endif

