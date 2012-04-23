
#ifndef _System_Content_WithEG_Interface_H_
#define _System_Content_WithEG_Interface_H_

#include "system/content/eg-base/interface.h"
#include "system/content/data/eg/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithEG
      : public SystemContentEGBase<T,SystemContentDataEG> {

    public:

      typedef SystemContentWithEG<T>    Type;
      typedef SystemContentEGBase<T,SystemContentDataEG>    ParentType;
      typedef SystemContentDataEG<T>    EGDataType;

      SystemContentWithEG() : ParentType() {}
      ~SystemContentWithEG() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentWithEG<T>& C) {
    Clear(static_cast<typename SystemContentWithEG<T>::ParentType&>(C));
  }

}

#endif

