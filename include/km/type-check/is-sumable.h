
#ifndef _Type_Check_IsSumable_H_
#define _Type_Check_IsSumable_H_

namespace mysimulator {

  template <typename T>
  class IsSumable {};

}

#define _SumDEF_(T) \
  template <> class IsSumable<T> { \
    public: typedef IsSumable<T>  Type; \
  };

namespace mysimulator {

  _SumDEF_(double)

}

#undef _SumDEF_

namespace mysimulator {

  template <typename T> class ArrayNumeric;
  template <typename T> class IsSumable<ArrayNumeric<T> > {
    typedef IsSumable<ArrayNumeric<T> >   Type;
  };

}

#endif

