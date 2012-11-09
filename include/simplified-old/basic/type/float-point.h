
#ifndef _Basic_Type_FloatPoint_H_
#define _Basic_Type_FloatPoint_H_

namespace mysimulator {

  template <typename T>
  class __float_point_flag { public: static const bool FG; };

  template <typename T> const bool __float_point_flag<T>::FG=false;
  template <> const bool __float_point_flag<long double>::FG=true;
  template <> const bool __float_point_flag<double>::FG=true;
  template <> const bool __float_point_flag<float>::FG=true;

}

#endif

