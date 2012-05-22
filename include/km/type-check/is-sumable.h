
#ifndef _Type_Check_IsSumable_H_
#define _Type_Check_IsSumable_H_

namespace mysimulator {

  template <typename T>
  class IsSumable {};

}

#ifndef _SumDEF_
#define _SumDEF_(T) \
  template <> class IsSumable<T> { \
    public: typedef IsSumable<T>  Type; \
  };
#else
#error "Duplicate _SumDEF_"
#endif

namespace mysimulator {

  _SumDEF_(long double)
  _SumDEF_(double)

}

#ifdef _SumDEF_
#undef _SumDEF_
#endif

namespace mysimulator {

  template <typename T> class ArrayNumeric;
  template <typename T> class IsSumable<ArrayNumeric<T> > {
    typedef IsSumable<ArrayNumeric<T> >   Type;
  };

}

#endif

