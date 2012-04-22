
#ifndef _System_Content_WithEV_Interface_H_
#define _System_Content_WithEV_Interface_H_

#include "system/content/with-e/interface.h"
#include "system/content/v-base/interface.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentWithEV
      : public SystemContentVBase<T,SystemContentWithE> {

    public:

      typedef SystemContentWithEV<T>   Type;
      typedef SystemContentVBase<T,SystemContentWithE> ParentType;

      SystemContentWithEV() : ParentType() {}
      ~SystemContentWithEV() { Clear(); }

      void Clear() { static_cast<ParentType*>(this)->Clear(); }
      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

    private:

      SystemContentWithEV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

