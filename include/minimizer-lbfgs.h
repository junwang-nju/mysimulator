
#ifndef _Minimizer_LBFGS_H_
#define _Minimizer_LBFGS_H_

#include "minimizer-condition.h"

namespace std {

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr=6>
  struct LBFGSMinimizer : public LineMinMethod<SpaceDataType,ParameterType> {

    typedef LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>
            Type;
    typedef LineMinMethod<SpaceDataType,ParameterType> ParentType;

    static const unsigned int DefaultMaxIter;

    SpaceDataType *Dirc;
    SpaceDataType *dX;
    SpaceDataType *dG;
    double *alpha;
    double *rho;
    SpaceDataType *lastX;
    SpaceDataType *lastG;

    LBFGSMinimizer()
      : ParentType(), Dirc(NULL), dX(NULL), dG(NULL), alpha(NULL), rho(NULL),
        lastX(NULL), lastG(NULL) {}
    LBFGSMinimizer(const Type&) {
      myError("Cannot create from LBFGS Minimizer");
    }
    Type& operator=(const Type& LM) { assign(*this,LM); return *this; }
    ~LBFGSMinimizer() { release(*this); }

    template <unsigned int CondType>
    int Minimize(const unsigned int MaxIter=DefaultMaxIter) {
      return 0;
    }

  };

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  const unsigned int
  LBFGSMinimizer<SpaceDataType,ParameterType,
                 LineMinMethod,MaxCorr>::DefaultMaxIter=1000;

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  bool IsAvailable(
      const LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>&
            LM) {
    return IsAvailable(LM.Dirc);
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  void release(
      LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>& LM) {
    if(LM.state==Allocated) {
      safe_delete(LM.Dirc);
      safe_delete_array(LM.dX);
      safe_delete_array(LM.dG);
      safe_delete_array(LM.dG);
      safe_delete_array(LM.alpha);
      safe_delete_array(LM.rho);
      safe_delete(LM.lastX);
      safe_delete(LM.lastG);
    } else {
      LM.Dirc=NULL;
      LM.dX=NULL;
      LM.dG=NULL;
      LM.alpha=NULL;
      LM.rho=NULL;
      LM.lastX=NULL;
      LM.lastG=NULL;
    }
    typedef LineMinMethod<SpaceDataType,ParameterType> PType;
    release(static_cast<PType&>(LM));
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  void assign(
      LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>& ferdt,
      const LBFGSMinimizer<SpaceDataType,ParameterType,LineMin,maxCorr>& src) {
  }
}

#endif

