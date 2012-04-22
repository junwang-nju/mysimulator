
#ifndef _System_Content_WithV_Interface_H_
#define _System_Content_WithV_Interface_H_

#include "system/content/with-null/interface.h"
#include "system/content/v-base/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithV
      : public SystemContentVBase<T,SystemContentWithNull> {

    public:

      typedef SystemContentWithV<T>   Type;
      typedef SystemContentVBase<T,SystemContentWithNull> ParentType;

      SystemContentWithV() : ParentType() {}
      ~SystemContentWithV() { Clear(); }

      void Clear() { static_cast<ParentType*>(this)->Clear(); }
      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

