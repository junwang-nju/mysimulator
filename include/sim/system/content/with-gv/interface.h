
#ifndef _System_Content_WithGV_Interface_H_
#define _System_Content_WithGV_Interface_H_

#include "system/content/with-g/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithGV : public SystemContentWithG<T> {

    public:

      typedef SystemContentWithGV<T>    Type;
      typedef SystemContentWithG<T>     ParentType;

      T** Velocity;

      SystemContentWithGV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithGV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentWithGV<T>& C) { C.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentWithGV<T>& C) { return C.isvalid(); }

}

#endif

