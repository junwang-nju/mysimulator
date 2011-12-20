
#ifndef _System_Content_WithV_Interface_H_
#define _System_Content_WithV_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/null/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithV : public SysContentBase<T,VecType> {

    public:

      typedef SysContentWithV<T,VecType>    Type;
      typedef SysContentBase<T,VecType>     ParentType;
      typedef SysContentDataNull            EGDataType;

      Object<VecType<T> >   Velocity;

      SysContentWithV() : ParentType(), Velocity() {}
      ~SysContentWithV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(Velocity);
      }

    private:

      SysContentWithV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentWithV<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentWithV<T,VT>& S) { return S.isvalid(); }

}

#endif

