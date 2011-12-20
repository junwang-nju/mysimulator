
#ifndef _System_Content_Data_EG_Interface_H_
#define _System_Content_Data_EG_Interface_H_

#include "object/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentDataEG {

    public:

      typedef SysContentDataEG<T,VecType>   Type;

      Object<T> Energy;
      Object<VecType<T> >   Gradient;

      SysContentDataEG() : Energy(), Gradient() {}
      ~SysContentDataEG() { clearData(); }

      void clearData() { release(Gradient); release(Energy); }
      bool isvalid() const { return IsValid(Energy)&&IsValid(Gradient); }

    private:

      SysContentDataEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentDataEG<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentDataEG<T,VT>& S) { return S.isvalid(); }

}

#endif

