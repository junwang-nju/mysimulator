
#ifndef _Basic_Constant_H_
#define _Basic_Constant_H_

namespace mysimulator {

  static const float FRelDelta=5.9604644775390625e-8;
  static const float FSqrtRelDelta=0.000244140625;

  static const double DRelDelta=1.1107651257113993e-16;
  static const double DSqrtRelDelta=1.0539284253265965e-8;

  template <typename T>
  const T _RelDelta() {
    fprintf(stderr,"Unknown Type for RelDelta!\n"); return 0;
  }
  template <> const float _RelDelta<float>() { return FRelDelta; }
  template <> const double _RelDelta<double>() { return DRelDelta; }

}

#endif

