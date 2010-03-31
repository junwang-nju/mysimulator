
#ifndef _Minimizer_Condition_H_
#define _Minimizer_Condition_H_

namespace std {

  enum ConditionType {
    Armijo=0,
    Wolfe,
    StrongWolfe
  };

  template <int CondType>
  bool Condition(const double&, const double&, const double&,
                 const double&, const double&, const double&) {
    myError("Unknown Condition Type!");
    return false;
  }

  template <>
  bool Condition<Armijo>(const double& ry, const double& rp,
                         const double& my,
                         const double& dp, const double& cp,
                         const double& step) {
    return ry<=my+step*dp;
  }

  template <>
  bool Condition<Wolfe>(const double& ry, const double& rp,
                        const double& my,
                        const double& dp, const double& cp,
                        const double& step) {
    assert(cp<0);
    return Condition<Armijo>(ry,rp,my,dp,cp,step)&&(rp>=cp);
  }

  template <>
  bool Condition<StrongWolfe>(const double& ry, const double& rp,
                              const double& my,
                              const double& dp, const double& cp,
                              const double& step) {
    return Condition<Wolfe>(ry,rp,my,dp,cp,step)&&(rp<=-cp);
  }

}

#endif

