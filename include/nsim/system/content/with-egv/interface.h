
#ifndef _System_Content_WithEGV_Interface_H_
#define _System_Content_WithEGV_Interface_H_

#include "system/content/with-eg/interface.h"
#include "system/content/v-base/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithEGV
      : public SystemContentVBase<T,SystemContentWithEG> {

    public:

      typedef SystemContentWithEGV<T>   Type;
      typedef SystemContentVBase<T,SystemContentWithEG> ParentType;

      SystemContentWithEGV() : ParentType() {}
      ~SystemContentWithEGV() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithEGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentWithEGV<T>& C) {
    Clear(static_cast<typename SystemContentWithEGV<T>::ParentType&>(C));
  }

}

#endif

