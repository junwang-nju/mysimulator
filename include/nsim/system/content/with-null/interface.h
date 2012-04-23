
#ifndef _System_Content_WithNull_Interface_H_
#define _System_Content_WithNull_Interface_H_

#include "system/content/eg-base/interface.h"
#include "system/content/data/null/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithNull
      : public SystemContentEGBase<T,SystemContentDataNull> {

    public:

      typedef SystemContentWithNull<T>      Type;
      typedef SystemContentEGBase<T,SystemContentDataNull>        ParentType;
      typedef SystemContentDataNull<T>      EGDataType;

      SystemContentWithNull() : ParentType() {}
      ~SystemContentWithNull() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithNull(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentWithNull<T>& C) {
    Clear(static_cast<typename SystemContentWithNull<T>::ParentType&>(C));
  }

}

#endif

