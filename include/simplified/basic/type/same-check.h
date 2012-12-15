
#ifndef _Basic_Type_Same_Check_H_
#define _Basic_Type_Same_Check_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class __same_type { public: static const bool FLAG; };

  template <typename T1, typename T2>
  const bool __same_type<T1,T2>::FLAG = false;

  template <>
  const bool __same_type<int,long>::FLAG = sizeof(int)==sizeof(long) ;

  template <>
  const bool __same_type<long,int>::FLAG = __same_type<int,long>::FLAG;

  template <>
  const bool __same_type<unsigned int,unsigned long>::FLAG =
      sizeof(unsigned int)==sizeof(unsigned long);

  template <>
  const bool __same_type<unsigned long,unsigned int>::FLAG =
      __same_type<unsigned int,unsigned long>::FLAG;

  template <typename T>
  class __same_type<T,T> { public: static const bool FLAG; };

  template <typename T>
  const bool __same_type<T,T>::FLAG = true;

}

#endif

