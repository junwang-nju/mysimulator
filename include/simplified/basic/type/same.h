
#ifndef _Basic_Type_Same_H_
#define _Basic_Type_Same_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class __same_type { public: static const bool FG; };

  template <typename T1,typename T2>
  const bool __same_type<T1,T2>::FG=false;

  template <typename T>
  class __same_type<T,T> { public: static const bool FG; };

  template <typename T>
  const bool __same_type<T,T>::FG=true;

  template <>
  const bool __same_type<int,long>::FG = (sizeof(int)==sizeof(long));

  template <>
  const bool __same_type<unsigned int,unsigned long>::FG =
      (sizeof(unsigned int)==sizeof(unsigned long));

}

#endif

