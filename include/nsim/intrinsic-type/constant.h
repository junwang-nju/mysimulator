
#ifndef _Intrinsic_Type_Constant_H_
#define _Intrinsic_Type_Constant_H_

namespace mysimulator {

  static const float  FRelDelta=5.9604644775390625e-8;
  static const float  FSqrtRelDelta=0.000244140625;

  static const double DRelDelta=1.1107651257113993e-16;
  static const double DSqrtRelDelta=1.0539284253265965e-8;

  template <typename T>
  const T RelDelta() { fprintf(stderr,"Unknown Type!\n");  return 0; }

  template <> const float RelDelta<float>()  { return FRelDelta; }
  template <> const double RelDelta<double>() { return DRelDelta; }

  static const double Golden=0.618033988749894848205;
  static const double IvGolden=1.618033988749894848205;

  template <typename T>
  const T GoldenValue() { fprintf(stderr,"Unknown Type!\n"); return 0; }

  template <> const double GoldenValue<double>() { return Golden; }

}

#endif
