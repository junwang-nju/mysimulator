
#ifndef _System_Content_WithG_Interface_H_
#define _System_Content_WithG_Interface_H_

#include "system/content/base/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithG : public SysContentBase<T,VecType> {

    public:

      typedef SysContentWithG<T,VecType>      Type;
      typedef SysContentBase<T,VecType>       ParentType;

      Object<VecType<T> >   Gradient;

      SysContentWithG() : ParentType(), Gradient() {}
      ~SysContentWithG() { clearData(); }

      void clearData() {
        release(Gradient);  static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(Gradient);
      }

    private:

      SysContentWithG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VecType>
  void release(SysContentWithG<T,VecType>& S) { S.clearData(); }

  template <typename T, template<typename> class VecType>
  bool IsValid(const SysContentWithG<T,VecType>& S) { return S.isvalid(); }

}

#endif

