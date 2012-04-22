
#ifndef _Boundary_FreeSpace_Interface_H_
#define _Boundary_FreeSpace_Interface_H_

namespace mysimulator {

  struct FreeSpace {

    public:

      typedef FreeSpace Type;

      FreeSpace() {}
      ~FreeSpace() {}

      void Clear() {}
      bool IsValid() const { return true; }

      void Allocate(unsigned int) {}
      void Refer(const Type&) {}

    private:

      FreeSpace(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#include "displacement/free/calc.h"

#endif

