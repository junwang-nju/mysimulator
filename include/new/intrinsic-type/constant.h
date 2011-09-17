
#ifndef _Intrinsic_Type_Constant_H_
#define _Intrinsic_Type_Constant_H_

namespace mysimulator {

  static const char cZero=0;
  static const char cOne=1;

  static const unsigned char ucZero=0;

  static const int iZero=0;
  static const int iOne=1;
  static const int iNOne=-1;

  static const unsigned int uZero=0U;
  static const unsigned int uOne=1U;
  static const unsigned int uTwo=2U;

  static const long lZero=0;
  static const long lOne=1;
  static const long lTwo=2;
  static const long lThree=3;
  static const long lFour=4;

  static const float fOne=1.;
  static const float fNOne=-1.;
  static const float fHalf=0.5;

  static const float FRelDelta=5.9604644775390625e-8;
  static const float FSqrtRelDelta=0.000244140625;

  static const double dOne=1.;
  static const double dNOne=-1.;
  static const double dTwo=2.;
  static const double dHalf=0.5;

  static const double DRelDelta=1.1107651257113993e-16;
  static const double DSqrtRelDelta=1.0539284253265965e-8;
  static const double Gold=0.618033988749894848205;
  static const double IvGold=1.618033988749894848205;

}

#include "io/error.h"

namespace mysimulator {

  template <typename T>
  const T& RelativeDelta() {
    Error("Unknown Type for Relative Delta!");
    return static_cast<T>(cZero);
  }
  
  template <> const double& RelativeDelta<double>() { return DRelDelta; }
  template <> const float& RelativeDelta<float>() { return FRelDelta; }

  template <typename T>
  const T& ValueGolden() {
    Error("Unknown Type for Golden Value!");
    return static_cast<T>(cZero);
  }

  template <> const double& ValueGolden<double>() { return Gold; }

  template <typename T>
  const T& ValueOne() {
    Error("Unknown Type to have a value of one!");
    return static_cast<T>(cOne);
  }

  template <> const double& ValueOne<double>() { return dOne; }
  template <> const float& ValueOne<float>() { return fOne; }

  template <typename T>
  const T& ValueHalf() {
    Error("Unknown Type to have a value of half!");
    return static_cast<T>(fHalf);
  }

  template <> const double& ValueHalf<double>() { return dHalf; }
  template <> const float& ValueHalf<float>() { return fHalf; }

}

#endif

