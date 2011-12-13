
#ifndef _System_Masking_Interface_H_
#define _System_Masking_Interface_H_

#include "system/masking/mode.h"
#include "io/error.h"

namespace mysimulator {

  template <typename T,template<typename>class SpaceType,SystemMaskModeName MN>
  struct SystemMasking {

    public:

      typedef SystemMasking<T,SpaceType,MN>   Type;

      SystemMasking() { Error("Unknown Mask Mode!"); }
      ~SystemMasking() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

    private:

      SystemMasking(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class ST,SystemMaskModeName MN>
  void release(SystemMasking<T,ST,MN>& S) { S.clearData(); }

  template <typename T,template<typename> class ST,SystemMaskModeName MN>
  bool IsValid(const SystemMasking<T,ST,MN>& S) { return S.isvalid(); }

}

#include "system/masking/no-act/specification.h"
#include "system/masking/fixed/specification.h"
#include "system/masking/free/specification.h"

#endif

