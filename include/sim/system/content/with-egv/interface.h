
#ifndef _System_Content_WithEGV_Interface_H_
#define _System_Content_WithEGV_Interface_H_

#include "system/content/with-eg/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithEGV : public SystemContentWithEG<T> {

    public:

      typedef SystemContentWithEGV<T>  Type;
      typedef SystemContentWithEG<T>   ParentType;

      T** Velocity;

      SystemContentWithEGV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithEGV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithEGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentWithEGV<T>& C) { C.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentWithEGV<T>& C) { return C.isvalid(); }

}

#endif

