
/**
 * @file boundary/free/interface.h
 * @brief boundary condition representing free space
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Boundary_Free_Interface_H_
#define _Boundary_Free_Interface_H_

namespace mysimulator {

  class FreeSpace {

    public:

      typedef FreeSpace Type;

      FreeSpace() {}
      ~FreeSpace() {}

      bool IsValid() const { return true; }
      void Allocate(unsigned int) {}
      void Refer(const Type&) {}

    private:

      FreeSpace(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(FreeSpace&) {}

}

#include "displacement/free/calc.h"

#endif

