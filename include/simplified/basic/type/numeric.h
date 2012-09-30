
#ifndef _Basic_Type_Numeric_H_
#define _Basic_Type_Numeric_H_

namespace mysimulator {

  template <typename T>
  class __numeric_flag { public: static const bool FG; };

  template <typename T> const bool __numeric_flag<T>::FG=false;
  template <> const bool __numeric_flag<long double>::FG=true;
  template <> const bool __numeric_flag<double>::FG=true;
  template <> const bool __numeric_flag<float>::FG=true;
  template <> const bool __numeric_flag<long long>::FG=true;
  template <> const bool __numeric_flag<unsigned long long>::FG=true;
  template <> const bool __numeric_flag<int>::FG=true;
  template <> const bool __numeric_flag<unsigned int>::FG=true;
  template <> const bool __numeric_flag<long>::FG=true;
  template <> const bool __numeric_flag<unsigned long>::FG=true;
  template <> const bool __numeric_flag<short>::FG=true;
  template <> const bool __numeric_flag<unsigned short>::FG=true;
  template <> const bool __numeric_flag<char>::FG=true;
  template <> const bool __numeric_flag<unsigned char>::FG=true;

}

#endif

