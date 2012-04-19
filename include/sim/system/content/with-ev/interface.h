
#ifndef _System_Content_WithEV_Interface_H_
#define _System_Content_WithEV_Interface_H_

#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithEV : public SystemContentWithE<T> {

    public:

      typedef SystemContentWithEV<T>    Type;
      typedef SystemContentWithE<T>     ParentType;

      T** Velocity;

      SystemContentWithEV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithEV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithEV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentWithEV<T>& C) { C.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentWithEV<T>& C) { return C.isvalid(); }

}

#endif

