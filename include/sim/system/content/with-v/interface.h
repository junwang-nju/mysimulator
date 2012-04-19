
#ifndef _System_Content_WithV_Interface_H_
#define _System_Content_WithV_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/null/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithV : public SystemContentBase<T> {

    public:

      typedef SystemContentWithV<T>       Type;
      typedef SystemContentBase<T>        ParentType;
      typedef SystemContentDataNull       EGDataType;

      T** Velocity;

      SystemContentWithV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentWithV<T>& C) { C.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentWithV<T>& C) { return C.isvalid(); }

}

#endif

