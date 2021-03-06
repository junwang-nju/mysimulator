
#ifndef _System_Content_Base_Interface_H_
#define _System_Content_Base_Interface_H_

#include "object/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentBase {

    public:

      typedef SysContentBase<T,VecType>   Type;

      Object<VecType<T> > X;

      SysContentBase() : X() {}
      ~SysContentBase() { clearData(); }

      void clearData() { release(X); }
      bool isvalid() const { return IsValid(X); }

    private:

      SysContentBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentBase<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentBase<T,VT>& S) { return S.isvalid(); }

}

#endif

