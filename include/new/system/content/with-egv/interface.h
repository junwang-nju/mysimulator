
#ifndef _System_Content_WithEGV_Interface_H_
#define _System_Content_WithEGV_Interface_H_

#include "system/content/with-eg/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithEGV : public SysContentWithEG<T,VecType> {

    public:

      typedef SysContentWithEGV<T,VecType>  Type;
      typedef SysContentWithEG<T,VecType>   ParentType;

      Object<VecType<T> >   Velocity;

      SysContentWithEGV() : ParentType(), Velocity() {}
      ~SysContentWithEGV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(Velocity);
      }

    private:

      SysContentWithEGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentWithEGV<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentWithEGV<T,VT>& S) { return S.isvalid(); }

}

#endif

