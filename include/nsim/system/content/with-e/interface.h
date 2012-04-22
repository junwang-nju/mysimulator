
#ifndef _System_Content_WithE_Interface_H_
#define _System_Content_WithE_Interface_H_

#include "system/content/eg-base/interface.h"
#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithE : public SystemContentEGBase<T,SystemContentDataE> {

    public:

      typedef SystemContentWithE<T>     Type;
      typedef SystemContentEGBase<T,SystemContentDataE>    ParentType;
      typedef SystemContentDataE<T>     EGDataType;

      SystemContentWithE() : ParentType() {}
      ~SystemContentWithE() { Clear(); }

      void Clear() { static_cast<ParentType*>(this)->Clear(); }
      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

