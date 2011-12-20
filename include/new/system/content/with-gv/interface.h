
#ifndef _System_Content_WithGV_Interface_H_
#define _System_Content_WithGV_Interface_H_

#include "system/content/with-g/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithGV : public SysContentWithG<T,VecType> {

    public:

      typedef SysContentWithGV<T,VecType>   Type;
      typedef SysContentWithG<T,VecType>    ParentType;

      Object<VecType<T> >   Velocity;

      SysContentWithGV() : ParentType(), Velocity() {}
      ~SysContentWithGV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(Velocity);
      }

    private:

      SysContentWithGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentWithGV<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentWithGV<T,VT>& S) { return S.isvalid(); }

}

#endif

