
#ifndef _Basic_Type_NumericCheck_H_
#define _Basic_Type_NumericCheck_H_

namespace mysimulator {

  template <typename T>
  class __numeric { public: static const bool FLAG; };

  template <typename T>
  const bool __numeric<T>::FLAG = false;

  template <>
  const bool __numeric<long double>::FLAG = true;

  template <>
  const bool __numeric<double>::FLAG = true;

  template <>
  const bool __numeric<float>::FLAG = true;

  template <>
  const bool __numeric<long long>::FLAG = true;

  template <>
  const bool __numeric<unsigned long long>::FLAG = true;

  template <>
  const bool __numeric<int>::FLAG = true;

  template <>
  const bool __numeric<unsigned int>::FLAG = true;

  template <>
  const bool __numeric<long>::FLAG = true;

  template <>
  const bool __numeric<unsigned long>::FLAG = true;

  template <>
  const bool __numeric<short>::FLAG = true;

  template <>
  const bool __numeric<unsigned short>::FLAG = true;

  template <>
  const bool __numeric<char>::FLAG = true;

  template <>
  const bool __numeric<unsigned char>::FLAG = true;

}

#endif

