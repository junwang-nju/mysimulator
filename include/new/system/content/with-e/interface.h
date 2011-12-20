
#ifndef _System_Content_WithE_Interface_H_
#define _System_Content_WithE_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithE : public SysContentBase<T,VecType> {

    public:

      typedef SysContentWithE<T,VecType>    Type;
      typedef SysContentBase<T,VecType>     ParentType;
      typedef SysContentDataE<T>            EGDataType;

      EGDataType  EGData;

      SysContentWithE() : ParentType(), EGData() {}
      ~SysContentWithE() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&IsValid(EGData);
      }

    private:

      SysContentWithE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentWithE<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentWithE<T,VT>& S) { return S.isvalid(); }

}

#endif

