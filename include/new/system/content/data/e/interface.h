
#ifndef _System_Content_Data_E_Interface_H_
#define _System_Content_Data_E_Interface_H_

#include "object/interface.h"

namespace mysimulator {

  template <typename T>
  struct SysContentDataE {

    public:

      typedef SysContentDataE<T>    Type;

      Object<T> Energy;

      SysContentDataE() : Energy() {}
      ~SysContentDataE() { clearData(); }

      void clearData() { release(Energy); }
      bool isvalid() const { return IsValid(Energy); }

    private:

      SysContentDataE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SysContentDataE<T>& S) { S.clearData(); }

  template <typename T>
  bool IsValid(const SysContentDataE<T>& S) { return S.isvalid(); }

}

#endif

