
#ifndef _System_Content_WithG_Interface_H_
#define _System_Content_WithG_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/g/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithG : public SystemContentBase<T> {

    public:

      typedef SystemContentWithG<T>     Type;
      typedef SystemContentBase<T>      ParentType;
      typedef SystemContentDataG<T>     EGDataType;

      EGDataType  EGData;

      SystemContentWithG() : ParentType(), EGData() {}
      ~SystemContentWithG() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(EGData);
      }

    private:

      SystemContentWithG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentWithG<T>& C) { C.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentWithG<T>& C) { return C.isvalid(); }

}

#endif

