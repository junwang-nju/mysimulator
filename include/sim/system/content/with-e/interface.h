
#ifndef _System_Content_WithE_Interface_H_
#define _System_Content_WithE_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithE : public SystemContentBase<T> {

    public:

      typedef SystemContentWithE<T>       Type;
      typedef SystemContentBase<T>        ParentType;
      typedef SystemContentDataE<T>       EGDataType;

      EGDataType  EGData;

      SystemContentWithE() : ParentType(), EGData() {}
      ~SystemContentWithE() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(EGData);
      }

    private:

      SystemContentWithE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentWithE<T>& C) { C.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentWithE<T>& C) { return C.isvalid(); }

}

#endif

