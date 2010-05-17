
#ifndef _Minimizer_SteepestDescent_H_
#define _Minimizer_SteepestDescent_H_

#include "error-proc.h"
#include "util.h"
#include "storage-state-name.h"
#include "constant.h"
#include "minimizer-condition.h"

namespace std {

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod>
  struct SteepestDescentMinimizer
    : public LineMinMethod<SpaceDataType,ParameterType> {

    typedef SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>
            Type;
    typedef LineMinMethod<SpaceDataType,ParameterType>  ParentType;
    
    static const unsigned int DefaultMaxIter;
    
    SpaceDataType *Dirc;

    SteepestDescentMinimizer() : ParentType(), Dirc(NULL) {}
    SteepestDescentMinimizer(const Type&) {
      myError("Cannot create from Steepest-Descent Minimizer");
    }
    Type& operator=(const Type& SM) { assign(*this,SM); return *this; }
    ~SteepestDescentMinimizer() { release(*this); }

    template <unsigned int CondType>
    int Minimize(const unsigned int MaxIter=DefaultMaxIter) {
      *(this->GCalcCount)=0;
      *(this->LineSearchCount)=0;
      double tmd;
      for(unsigned int neval=0;neval<MaxIter;++neval) {
        assign(*Dirc,*(this->MinGrad));
        tmd=norm(*Dirc);
        if(tmd<*(this->GradThreshold)) {
          *(this->LineSearchCount)=neval;
          return 3;
        }
        scale(*Dirc,-1./tmd);
        *(this->MinProject)=-tmd;
        tmd=*(this->MinEnergy);
        if(static_cast<ParentType*>(this)->Minimize(*Dirc)==2) {
          *(this->LineSearchCount)=neval;
          return 1;
        }
        if(2.*(tmd-*(this->MinEnergy))<=(tmd+*(this->MinEnergy))*DRelDelta) {
          *(this->LineSearchCount)=neval;
          return 2;
        }
      }
      *(this->LineSearchCount)=MaxIter;
      return 0;
    }

  };

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod>
  const unsigned int
  SteepestDescentMinimizer<SpaceDataType,ParameterType,
                           LineMinMethod>::DefaultMaxIter=10000;

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod>
  bool IsAvailable(
    const SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>&
    SM) {
    return IsAvailable(SM.Dirc);
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod>
  void release(
      SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>& SM){
    if(SM.state==Allocated) safe_delete(SM.Dirc);
    else SM.Dirc=NULL;
    typedef LineMinMethod<SpaceDataType,ParameterType>  PType;
    release(static_cast<PType&>(SM));
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod>
  void assign(
    SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>& dest,
    const SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>&
      src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    typedef LineMinMethod<SpaceDataType,ParameterType>  PType;
    assign(*(dest.Dirc),*(src.Dirc));
    assign(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

  template<typename SpaceDataType, typename ParameterType,
           template <typename,typename> class LineMinMethod>
  void allocate(
      SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>& SM){
    release(SM);
    SM.Dirc=new SpaceDataType;
    typedef LineMinMethod<SpaceDataType,ParameterType> PType;
    allocate(static_cast<PType&>(SM));
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod>
  void refer(
    SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>& dest,
    const SteepestDescentMinimizer<SpaceDataType,ParameterType,LineMinMethod>&
      src) {
    assert(IsAvailable(src));
    release(dest);
    dest.Dirc=src.Dirc;
    typedef LineMinMethod<SpaceDataType,ParameterType> PType;
    refer(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

}

#endif
