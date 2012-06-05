
/**
 * @file type/is-included.h
 * @brief checking if the range of one type can cover that of another type
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsIncluded_H_
#define _Type_IsIncluded_H_

namespace mysimulator {

  /** @class IsIncludedFlag
   */
  template <typename T1, typename T2>
  class IsIncludedFlag {
    public:
      /** @var Flag
       */
      static const bool Flag;
  };

  /** @var IsIncludedFlag::Flag
   */
  template <typename T1, typename T2>
  const bool IsIncludedFlag<T1,T2>::Flag=false;

}

/** @def _IncDEF_
 */
#ifndef _IncDEF_
#define _IncDEF_(T1,T2) \
  template <> class IsIncludedFlag<T1,T2> { public: static const bool Flag; }; \
  const bool IsIncludedFlag<T1,T2>::Flag=true;
#else
#error "Duplicate _IncDEF_"
#endif

namespace mysimulator {

  _IncDEF_(long double, double)
  _IncDEF_(long double, float)
  _IncDEF_(long double, long long)
  _IncDEF_(long double, unsigned long long)
  _IncDEF_(long double, int)
  _IncDEF_(long double, unsigned int)
  _IncDEF_(long double, long)
  _IncDEF_(long double, unsigned long)
  _IncDEF_(long double, short)
  _IncDEF_(long double, unsigned short)
  _IncDEF_(long double, char)
  _IncDEF_(long double, unsigned char)

  _IncDEF_(double, float)
  _IncDEF_(double, long long)
  _IncDEF_(double, unsigned long long)
  _IncDEF_(double, int)
  _IncDEF_(double, unsigned int)
  _IncDEF_(double, long)
  _IncDEF_(double, unsigned long)
  _IncDEF_(double, short)
  _IncDEF_(double, unsigned short)
  _IncDEF_(double, char)
  _IncDEF_(double, unsigned char)

  _IncDEF_(float, long long)
  _IncDEF_(float, unsigned long long)
  _IncDEF_(float, int)
  _IncDEF_(float, unsigned int)
  _IncDEF_(float, long)
  _IncDEF_(float, unsigned long)
  _IncDEF_(float, short)
  _IncDEF_(float, unsigned short)
  _IncDEF_(float, char)
  _IncDEF_(float, unsigned char)

  _IncDEF_(long long, int)
  _IncDEF_(long long, unsigned int)
  _IncDEF_(long long, long)
  _IncDEF_(long long, unsigned long)
  _IncDEF_(long long, short)
  _IncDEF_(long long, unsigned short)
  _IncDEF_(long long, char)
  _IncDEF_(long long, unsigned char)

  _IncDEF_(unsigned long long, unsigned int)
  _IncDEF_(unsigned long long, unsigned long)
  _IncDEF_(unsigned long long, unsigned short)
  _IncDEF_(unsigned long long, unsigned char)

  _IncDEF_(int, long)
  _IncDEF_(int, short)
  _IncDEF_(int, unsigned short)
  _IncDEF_(int, char)
  _IncDEF_(int, unsigned char)

  _IncDEF_(unsigned int, unsigned long)
  _IncDEF_(unsigned int, unsigned short)
  _IncDEF_(unsigned int, unsigned char)

  _IncDEF_(long, int)
  _IncDEF_(long, short)
  _IncDEF_(long, unsigned short)
  _IncDEF_(long, char)
  _IncDEF_(long, unsigned char)

  _IncDEF_(unsigned long, unsigned int)
  _IncDEF_(unsigned long, unsigned short)
  _IncDEF_(unsigned long, unsigned char)

  _IncDEF_(short, char)
  _IncDEF_(short, unsigned char)

  _IncDEF_(unsigned short, unsigned char)

}

#ifdef _IncDEF_
#undef _IncDEF_
#endif

namespace mysimulator {

  template <typename T>
  class IsIncludedFlag<T,T> {
    public:
      /** @var Flag
       */
      static const bool Flag;
  };

  /** @var IsIncludedFlag<T,T>::Flag
   */
  template <typename T>
  const bool IsIncludedFlag<T,T>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsIncluded
   */
  template <typename T1,typename T2>
  class IsIncluded {
    public:
      /** @typedef Type
       */
      typedef typename Check<IsIncludedFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

