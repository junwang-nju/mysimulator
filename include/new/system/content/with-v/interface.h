
#ifndef _System_Content_WithV_Interface_H_
#define _System_Content_WithV_Interface_H_

#include "system/content/base/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithV : public SysContentBase<T,VecType> {

    public:

      typedef SysContentWithV<T,VecType>    Type;
      typedef SysContentBase<T,VecType>     ParentType;

      Object<VecType<T> >   Velocity;

      SysContentWithV() : ParentType(), Velocity() {}
      ~SysContentWithV() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData(); release(Velocity);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(Velocity);
      }

    private:

      SysContentWithV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VecType>
  void release(SysContentWithV<T,VecType>& S) { S.clearData(); }

  template <typename T, template<typename> class VecType>
  bool IsValid(const SysContentWithV<T,VecType>& S) { return S.isvalid(); }

}

#endif

