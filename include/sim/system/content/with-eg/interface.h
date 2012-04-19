
#ifndef _System_Content_WithEG_Interface_H_
#define _System_Content_WithEG_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/eg/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithEG : public SystemContentBase<T> {

    public:

      typedef SystemContentWithEG<T>      Type;
      typedef SystemContentBase<T>        ParentType;
      typedef SystemContentDataEG<T>      EGDataType;

      EGDataType EGData;

      SystemContentWithEG() : ParentType(), EGData() {}
      ~SystemContentWithEG() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(EGData);
      }

    private:

      SystemContentWithEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentWithEG<T>& C) { C.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentWithEG<T>& C) { return C.isvalid(); }

}

#endif

