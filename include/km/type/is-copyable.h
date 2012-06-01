
#ifndef _Type_IsCopyAble_H_
#define _Type_IsCopyAble_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyableFlag {  public: static const bool Flag; };
  template <typename T1, typename T2> const bool IsCopyableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

  template <typename T>
  class IsCopyableFlag<T*,T*> { public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<T*,T*>::Flag=true;

  template <typename T>
  class IsCopyableFlag<void*,T*> {  public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<void*,T*>::Flag=true;

  template <typename T>
  class IsCopyableFlag<T*,void*> {  public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<T*,void*>::Flag=true;

}

#include "type/is-integer.h"

namespace mysimulator {

  template <typename T>
  class IsCopyableFlag<bool,T> {  public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<bool,T>::Flag=
    IsIntegerFlag<T>::Flag;


  template <typename T> class ArrayData;
  template <typename T1, typename T2>
  class IsCopyableFlag<ArrayData<T1>,ArrayData<T2> > {
    public: static const bool Flag;
  };
  template <typename T1, typename T2>
  const bool IsCopyableFlag<ArrayData<T1>,ArrayData<T2> >::Flag=
    IsCopyableFlag<T1,T2>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyable {
    public:
      typedef typename Check<IsCopyableFlag<T1,T2>::Flag>::Type  Type;
  };

}

#endif

