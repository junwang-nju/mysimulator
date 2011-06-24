
#ifndef _Minimizer_Line_Condition_Evaluate_H_
#define _Minimizer_Line_Condition_Evaluate_H_


namespace mysimulator {

  template <typename T>
  bool ArmijoCondition(const T& ry,const T&,const T& my,const T& dp,const T&,
                       const T& step) {
    return ry<=my+step*dp;
  }

  template <typename T>
  bool WolfeCondition(const T& ry,const T& rp,const T& my,const T& dp,
                      const T& cp, const T& step) {
    return ArmijoCondition(ry,rp,my,dp,cp,step)&&(rp>=cp);
  }

  template <typename T>
  bool StrongWolfeCondition(const T& ry,const T& rp,const T& my,const T& dp,
                            const T& cp, const T& step) {
    return WolfeCondition(ry,rp,my,dp,cp,step)&&(rp<=-cp);
  }

}

#endif

