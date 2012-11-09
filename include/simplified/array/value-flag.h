
#ifndef _Array_Value_Flag_H_
#define _Array_Value_Flag_H_

namespace mysimulator {

  template <typename MT>
  class __array_value { public: static const bool FLAG; };

  template <typename MT>
  const bool __array_value<MT>::FLAG = false;

}

namespace mysimulator {

  template <typename T> class Intrinsic;

  template <typename T>
  class __array_value<Intrinsic<T>> { public: static const bool FLAG; };

  template <typename T>
  const bool __array_value<Intrinsic<T>>::FLAG = true;

}

namespace mysimulator {

  template <typename T, bool _vflag> class Array;

  template <typename T>
  class __array_value<Array<T,true>> { public: static const bool FLAG; };

  template <typename T>
  const bool __array_value<Array<T,true>>::FLAG = true;

}

#endif

