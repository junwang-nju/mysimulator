
#ifndef _Boundary_Free_Interface_H_
#define _Boundary_Free_Interface_H_

namespace mysimulator {

  struct FreeSpace {

    public:

      typedef FreeSpace Type;

      FreeSpace() {}
      ~FreeSpace() {}

      void clearData() {}
      bool isvalid() const { return true; }

    private:

      FreeSpace(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const FreeSpace& F) { return F.isvalid(); }
  void release(FreeSpace& F) { F.clearData(); }

}

#include "displacement/free/calc.h"

#endif

