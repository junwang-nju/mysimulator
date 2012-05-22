
#ifndef _Type_IsSame_H_
#define _Type_IsSame_H_

namespace mysimulator {

  template <typename T1, typename T2>
  class IsTypeSame { public: static const bool Status; };

  template <typename T1, typename T2>
  const bool IsTypeSame<T1,T2>::Status=false;

  template <typename T>
  class IsTypeSame<T,T> { public: static const bool Status; };
  template <typename T>
  const bool IsTypeSame<T,T>::Status=true;

}

#endif

