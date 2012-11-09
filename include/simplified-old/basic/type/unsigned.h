
#ifndef _Basic_Type_Unsigned_H_
#define _Basic_Type_Unsigned_H_

namespace mysimulator {

  template <typename T>
  class __unsigned_flag { public: static const bool FG; };

  template<typename T> const bool __unsigned_flag<T>::FG=false;

  template <> const bool __unsigned_flag<unsigned long long>::FG=true;
  template <> const bool __unsigned_flag<unsigned int>::FG=true;
  template <> const bool __unsigned_flag<unsigned long>::FG=true;
  template <> const bool __unsigned_flag<unsigned short>::FG=true;
  template <> const bool __unsigned_flag<unsigned char>::FG=true;
}

#endif

