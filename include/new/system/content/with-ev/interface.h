
#ifndef _System_Content_WithEV_Interface_H_
#define _System_Content_WithEV_Interface_H_

#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithEV : public SysContentWithE<T,VecType> {

    public:

      typedef SysContentWithEV<T,VecType>   Type;
      typedef SysContentWithE<T,VecType>     ParentType;

      Object<VecType<T> >   Velocity;

      SysContentWithEV() : ParentType(), Velocity() {}
      ~SysContentWithEV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(Velocity);
      }

    private:

      SysContentWithEV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentWithEV<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentWithEV<T,VT>& S) { return S.isvalid(); }

}

#endif

