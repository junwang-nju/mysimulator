
#ifndef _Minimize_Condition_H_
#define _Minimize_Condition_H_

#include "operation/basic/error-proc.h"
#include <cassert>

namespace std {

  template <typename T>
  bool ArmijoCondition(const T& ry, const T& rp, const T& my, const T& dp,
                       const T& cp, const T& step) {
    ry<=my+step*dp;
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

  template <typename T, unsigned int ConditionType>
  bool Condition(const T& ry, const T& rp, const T& my, const T& dp,
                 const T& cp, const T& step) {
    myError("Unknown Data Type or Condition Type");
    return false;
  }

  template <>
  bool Condition<double,Armijo>(const double& ry, const double& rp,
                                const double& my, const double& dp,
                                const double& cp, const double& step) {
    return ArmijoCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<double,Wolfe>(const double& ry, const double& rp,
                               const double& my, const double& dp,
                               const double& cp, const double& step) {
    return WolfeCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<double,StrongWolfe>(const double& ry, const double& rp,
                                     const double& my, const double& dp,
                                     const double& cp, const double& step) {
    return StrongWolfeCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<float,Armijo>(const float& ry, const float& rp,
                               const float& my, const float& dp,
                               const float& cp, const float& step) {
    return ArmijoCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<float,Wolfe>(const float& ry, const float& rp,
                              const float& my, const float& dp,
                              const float& cp, const float& step) {
    return WolfeCondition(ry,rp,my,dp,cp,step);
  }

  template <>
  bool Condition<float,StrongWolfe>(const float& ry, const float& rp,
                                    const float& my, const float& dp,
                                    const float& cp, const float& step) {
    return StrongWolfeCondition(ry,rp,my,dp,cp,step);
  }

}

#endif
