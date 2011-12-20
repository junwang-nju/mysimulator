
#ifndef _System_Content_WithG_Interface_H_
#define _System_Content_WithG_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/g/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithG : public SysContentBase<T,VecType> {

    public:

      typedef SysContentWithG<T,VecType>    Type;
      typedef SysContentBase<T,VecType>     ParentType;
      typedef SysContentDataG<T,VecType>    EGDataType;

      EGDataType  EGData;

      SysContentWithG() : ParentType(), EGData() {}
      ~SysContentWithG() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&IsValid(EGData);
      }

    private:

      SysContentWithG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentWithG<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentWithG<T,VT>& S) { return S.isvalid(); }

}

#endif

