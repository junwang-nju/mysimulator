
#ifndef _Minimize_Condition_H_
#define _Minimize_Condition_H_

#include "operation/basic/error-proc.h"
#include "data/name/minimize-condition.h"
#include <cassert>

namespace std {

  template <typename T>
  bool ArmijoCondition(const T& ry, const T& rp, const T& my, const T& dp,
                       const T& cp, const T& step) {
    return ry<=my+step*dp;
  }

  template <typename T>
  bool WolfeCondition(const T& ry, const T& rp, const T& my, const T& dp,
                      const T& cp, const T& step) {
    assert(cp<0);
    return ArmijoCondition(ry,rp,my,dp,cp,step)&&(rp>=cp);
  }

  template <typename T>
  bool StrongWolfeCondition(const T& ry, const T& rp, const T& my, const T& dp,
                            const T& cp, const T& step) {
    return WolfeCondition(ry,rp,my,dp,cp,step)&&(rp<=-cp);
  }

  template <unsigned int ConditionType>
  bool Condition(const double& ry, const double& rp, const double& my,
                 const double& dp, const double& cp, const double& step) {
    myError("Unknown Condition Type");
    return false;
  }

  template <>
  bool Condition<Armijo>(const double& ry,const double& rp,const double& my,
                         const double& dp,const double& cp,const double& step){
    return ArmijoCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<Wolfe>(const double& ry,const double& rp,const double& my,
                        const double& dp,const double& cp,const double& step) {
    return WolfeCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<StrongWolfe>(const double& ry, const double& rp,
                              const double& my, const double& dp,
                              const double& cp, const double& step) {
    return StrongWolfeCondition(ry,rp,my,dp,cp,step);
  }

  template <unsigned int ConditionType>
  bool Condition(const float& ry, const float& rp, const float& my,
                 const float& dp, const float& cp, const float& step) {
    myError("Unknown Condition Type");
    return false;
  }

  template <>
  bool Condition<Armijo>(const float& ry,const float& rp,const float& my,
                         const float& dp,const float& cp,const float& step) {
    return ArmijoCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<Wolfe>(const float& ry,const float& rp,const float& my,
                        const float& dp,const float& cp,const float& step) {
    return WolfeCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<StrongWolfe>(const float& ry,const float& rp,const float& my,
                              const float& dp,const float& cp,
                              const float& step) {
    return StrongWolfeCondition(ry,rp,my,dp,cp,step);
  }

}

#endif
