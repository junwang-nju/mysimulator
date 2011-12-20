
#ifndef _System_Content_WithEG_Interface_H_
#define _System_Content_WithEG_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/eg/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithEG : public SysContentBase<T,VecType> {

    public:

      typedef SysContentWithEG<T,VecType>   Type;
      typedef SysContentBase<T,VecType>     ParentType;
      typedef SysContentDataEG<T,VecType>   EGDataType;

      EGDataType  EGData;

      SysContentWithEG() : ParentType(), EGData() {}
      ~SysContentWithEG() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&IsValid(EGData);
      }

    private:

      SysContentWithEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(SysContentWithEG<T,VT>& S) { S.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const SysContentWithEG<T,VT>& S) { return S.isvalid(); }

}

#endif

