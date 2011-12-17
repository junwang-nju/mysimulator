
#ifndef _System_Content_WithE_Interface_H_
#define _System_Content_WithE_Interface_H_

#include "system/content/base/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithE : public SysContentBase<T,VecType> {

    public:

      typedef SysContentWithE<T,VecType>    Type;
      typedef SysContentBase<T,VecType>     ParentType;

      Object<T> Energy;

      SysContentWithE() : ParentType(), Energy() {}
      ~SysContentWithE() { clearData(); }

      void clearData() {
        release(Energy);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }

    private:

      SysContentWithE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VecType>
  void release(SysContentWithE<T,VecType>& S) { S.clearData(); }

  template <typename T, template<typename> class VecType>
  bool IsValid(const SysContentWithE<T,VecType>& S) { return S.isvalid(); }

}

#endif

