
#ifndef _System_Masked_Method_Interface_H_
#define _System_Masked_Method_Interface_H_

#include "system/masked/method/name.h"

namespace mysimulator {

  template <SystemMaskMethodName MN>
  struct SystemMaskApply {

    public:

      typedef SystemMaskApply<MN>   Type;

      SystemMaskApply() { Error("Unknown Mask Method!"); }
      ~SystemMaskApply() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

    private:

      SystemMaskApply(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <SystemMaskMethodName MN>
  void release(SystemMaskApply<MN>& A) { A.clearData(); }

  template <SystemMaskMethodName MN>
  bool IsValid(const SystemMaskApply<MN>& A) { return A.isvalid(); }

}

#include "system/masked/method/no-operation/specification.h"
#include "system/masked/method/do-mask/specification.h"

#endif

