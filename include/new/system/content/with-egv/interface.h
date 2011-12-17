
#ifndef _System_Content_WithEGV_H_
#define _System_Content_WithEGV_H_

#include "system/content/with-eg/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithEGV : public SysContentWithEG<T,VecType> {

    public:

      typedef SysContentWithEGV<T,VecType>    Type;
      typedef SysContentWithEG<T,VecType>     ParentType;

      Object<VecType<T> >   Velocity;

      SysContentWithEGV() : ParentType(), Velocity() {}
      ~SysContentWithEGV() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(Velocity);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(Velocity);
      }

    private:

      SysContentWithEGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VecType>
  void release(SysContentWithEGV<T,VecType>& S) { S.clearData(); }

  template <typename T, template<typename> class VecType>
  bool IsValid(const SysContentWithEGV<T,VecType>& S) { return S.isvalid(); }

}

#endif

