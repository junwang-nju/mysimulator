
#ifndef _System_Content_WithG_Interface_H_
#define _System_Content_WithG_Interface_H_

#include "system/content/eg-base/interface.h"
#include "system/content/data/g/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithG : public SystemContentEGBase<T,SystemContentDataG> {

    public:

      typedef SystemContentWithG<T>     Type;
      typedef SystemContentEGBase<T,SystemContentDataG>    ParentType;
      typedef SystemContentDataG<T>     EGDataType;

      SystemContentWithG() : ParentType() {}
      ~SystemContentWithG() { Clear(); }

      void Clear() { static_cast<ParentType*>(this)->Clear(); }
      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

