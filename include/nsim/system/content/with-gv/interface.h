
#ifndef _System_Content_WithGV_Interface_H_
#define _System_Content_WithGV_Interface_H_

#include "system/content/with-g/interface.h"
#include "system/content/v-base/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithGV
      : public SystemContentVBase<T,SystemContentWithG> {

    public:

      typedef SystemContentWithGV<T>   Type;
      typedef SystemContentVBase<T,SystemContentWithG> ParentType;

      SystemContentWithGV() : ParentType() {}
      ~SystemContentWithGV() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentWithGV<T>& C) {
    Clear(static_cast<typename SystemContentWithGV<T>::ParentType&>(C));
  }

}

#endif

