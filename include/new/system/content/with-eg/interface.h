
#ifndef _System_Content_WithEG_Interface_H_
#define _System_Content_WithEG_Interface_H_

#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithEG : public SysContentWithE<T,VecType> {

    public:

      typedef SysContentWithEG<T,VecType>     Type;
      typedef SysContentWithE<T,VecType>      ParentType;

      Object<VecType<T> > Gradient;

      SysContentWithEG() : ParentType(), Gradient() {}
      ~SysContentWithEG() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(Gradient);
      }
      bool isvalid() const {
        return static_cast<ParentType*>(this)->isvalid()&&IsValid(Gradient);
      }

    private:

      SysContentWithEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VecType>
  void release(SysContentWithEG<T,VecType>& S) { S.clearData(); }

  template <typename T, template<typename> class VecType>
  bool IsValid(const SysContentWithEG<T,VecType>& S) { return S.isvalid(); }

}

#endif

