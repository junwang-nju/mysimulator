
#ifndef _Minimizer_Line_Base_H_
#define _Minimizer_Line_Base_H_

#include "minimizer-base.h"
#include "constant.h"

namespace std {

  template <typename SpaceDataType, typename ParameterType>
  struct LineMinimizerBase
    : public MinimizerKernelBase<SpaceDataType,ParameterType> {

    typedef MinimizerKernelBase<SpaceDataType,ParameterType>  ParentType;
    typedef LineMinimizerBase<SpaceDataType,ParameterType>  Type;
    typedef SpaceDataType DataType;

    unsigned int *LineSearchCount;
    DataType  *RunCoor;
    DataType  *RunGrad;
    double  *RunEnergy;
    double  *RunProject;
    double  *DecreaseFactor;
    double  *CurvatureFactor;
    double  *GradThreshold;

    LineMinimizerBase()
      : ParentType(), LineSearchCount(NULL), RunCoor(NULL), RunGrad(NULL),
        RunEnergy(NULL), RunProject(NULL), DecreaseFactor(NULL),
        CurvatureFactor(NULL), GradThreshold(NULL) {}
    LineMinimizerBase(const Type&) {
      myError("Cannot create from Line Minimizer Base");
    }
    Type& operator=(const Type& LM) { assign(*this,LM); return *this; }
    ~LineMinimizerBase() { release(*this); }

  };

  template <typename SpaceDataType, typename ParameterType>
  bool IsAvailable(const LineMinimizerBase<SpaceDataType,ParameterType>& LM) {
    return IsAvailable(LM.RunCoor);
  }

  template <typename SpaceDataType, typename ParameterType>
  void release(LineMinimizerBase<SpaceDataType,ParameterType>& LM) {
    if(LM.state==Allocated) {
      safe_delete(LM.LineSearchCount);
      safe_delete(LM.RunCoor);
      safe_delete(LM.RunGrad);
      safe_delete(LM.RunEnergy);
      safe_delete(LM.RunProject);
      safe_delete(LM.DecreaseFactor);
      safe_delete(LM.CurvatureFactor);
      safe_delete(LM.GradThreshold);
    } else {
      LM.LineSearchCount=NULL;
      LM.RunCoor=NULL;
      LM.RunGrad=NULL;
      LM.RunEnergy=NULL;
      LM.RunProject=NULL;
      LM.DecreaseFactor=NULL;
      LM.CurvatureFactor=NULL;
      LM.GradThreshold=NULL;
    }
    typedef MinimizerKernelBase<SpaceDataType,ParameterType> PType;
    release(static_cast<PType&>(LM));
  }

  template <typename SpaceDataType, typename ParameterType>
  void assign(LineMinimizerBase<SpaceDataType,ParameterType>& dest,
              const LineMinimizerBase<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(src));
    assert(IsAvailable(dest));
    *(dest.LineSearchCount)=*(src.LineSearchCount);
    *(dest.RunCoor)=*(src.RunCoor);
    *(dest.RunGrad)=*(src.RunGrad);
    *(dest.RunEnergy)=*(src.RunEnergy);
    *(dest.RunProject)=*(src.RunProject);
    *(dest.DecreaseFactor)=*(src.DecreaseFactor);
    *(dest.CurvatureFactor)=*(src.CurvatureFactor);
    *(dest.GradThreshold)=*(src.GradThreshold);
    typedef MinimizerKernelBase<SpaceDataType,ParameterType> PType;
    assign(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

  template <typename SpaceDataType, typename ParameterType>
  void allocate(LineMinimizerBase<SpaceDataType,ParameterType>& LM) {
    release(LM);
    LM.LineSearchCount=new unsigned int;
    LM.RunCoor=new SpaceDataType;
    LM.RunGrad=new SpaceDataType;
    LM.RunEnergy=new double;
    LM.RunProject=new double;
    LM.DecreaseFactor=new double;
    LM.CurvatureFactor=new double;
    LM.GradThreshold=new double;
    typedef MinimizerKernelBase<SpaceDataType,ParameterType> PType;
    allocate(static_cast<PType&>(LM));
    *(LM.DecreaseFactor)=1e-4;
    *(LM.CurvatureFactor)=0.4;
    *(LM.GradThreshold)=DRelDelta;
  }

  template <typename SpaceDataType, typename ParameterType>
  void refer(LineMinimizerBase<SpaceDataType,ParameterType>& dest,
             const LineMinimizerBase<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.RunCoor=src.RunCoor;
    dest.RunGrad=src.RunGrad;
    dest.RunEnergy=src.RunEnergy;
    dest.RunProject=src.RunProject;
    dest.DecreaseFactor=src.DecreaseFactor;
    dest.CurvatureFactor=src.CurvatureFactor;
    dest.GradThreshold=src.GradThreshold;
    dest.LineSearchCount=src.LineSearchCount;
    typedef MinimizerKernelBase<SpaceDataType,ParameterType> PType;
    refer(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

}

#endif

