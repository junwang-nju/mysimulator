
#ifndef _Unique_64Bit_Copy_H_
#define _Unique_64Bit_Copy_H_

#include "unique/64bit/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  void copy(Unique64Bit& U, const Unique64Bit& cU) { copy(U.ull,cU.ull); }

}

#define _COPYV(type) \
  void copy(Unique64Bit& U, const type& val) { copy(U.value<type>(),val); }
#define _COPYU(type) \
  void copy(type& val, const Unique64Bit& U) { copy(val,U.value<type>()); }

#define _COPY(type) \
  _COPYV(type)\
  _COPYU(type)

namespace mysimulator {

  _COPY(double)
  _COPY(float)
  _COPY(long long)
  _COPY(unsigned long long)
  _COPY(int)
  _COPY(unsigned int)
  _COPY(long)
  _COPY(unsigned long)
  _COPY(short)
  _COPY(unsigned short)
  _COPY(char)
  _COPY(unsigned char)

}

#undef _COPY
#undef _COPYU
#undef _COPYV

namespace mysimulator {

  template <typename T>
  void copy(Unique64Bit& U, const T* const& p) { copy(U.ptr[0],p); }

  template <typename T>
  void copy(T*& p, const Unique64Bit& U) { copy(p,U.ptr[0]); }

}

#include "array/1d/content/copy.h"

#define _TYPE(type,a) reinterpret_cast<type*>(a)

#define _COPYU_WithDel(type) \
  void _copy(Unique64Bit* p, type* q, const unsigned int& n,\
             const unsigned int& del, const unsigned int& cdel) {\
    _copy_blas(_TYPE(type,p),q,n,del*sizeof(double)/sizeof(type),cdel);\
  }

#define _COPYV_WithDel(type) \
  void _copy(type* p, Unique64Bit* q, const unsigned int& n,\
             const unsigned int& del, const unsigned int& cdel) {\
    _copy_blas(p,_TYPE(type,q),n,del,cdel*sizeof(double)/sizeof(type));\
  }

#define _COPYU(type) \
  void _copy(Unique64Bit* p, type* q, const unsigned int& n) {\
    _copy_blas(_TYPE(type,p),q,n,sizeof(double)/sizeof(type),uOne);\
  }

#define _COPYV(type) \
  void _copy(type* p, Unique64Bit* q, const unsigned int& n) {\
    _copy_blas(p,_TYPE(type,q),n,uOne,sizeof(double)/sizeof(type));\
  }

#define _COPY(type) \
  _COPYU_WithDel(type)\
  _COPYU(type)\
  _COPYV_WithDel(type)\
  _COPYV(type)

namespace mysimulator {

  void _copy(Unique64Bit* p, Unique64Bit* q, const unsigned int& n,
             const unsigned int& del, const unsigned int& cdel) {
    _copy_blas(_TYPE(double,p),_TYPE(double,q),n,del,cdel);
  }

  void _copy(Unique64Bit* p, Unique64Bit* q, const unsigned int& n) {
    _copy_blas(_TYPE(double,p),_TYPE(double,q),n);
  }

  _COPY(double)
  _COPY(float)
  _COPY(long long)
  _COPY(unsigned long long)
  _COPY(int)
  _COPY(unsigned int)
  _COPY(long)
  _COPY(unsigned long)

}

#undef _COPY
#undef _COPYV
#undef _COPYU
#undef _COPYU_WithDel
#undef _COPYV_WithDel
#undef _TYPE

#endif

