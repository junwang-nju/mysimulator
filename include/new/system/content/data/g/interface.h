
#ifndef _System_Content_Data_G_Interface_H_
#define _System_Content_Data_G_Interface_H_

#include "object/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentDataG {

    public:

      typedef SysContentDataG<T,VecType>  Type;

      Object<VecType<T> >   Gradient;

      SysContentDataG() : Gradient() {}
      ~SysContentDataG() { clearData(); }

      void clearData() { release(Gradient); }
      bool isvalid() const { return IsValid(Gradient); }

    private:

      SysContentDataG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentDataG<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentDataG<T,VT>& S) { return S.isvalid(); }

}

#endif

