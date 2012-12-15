
#ifndef _Geometry_Boundary_FreeSpace_Interface_H_
#define _Geometry_Boundary_FreeSpace_Interface_H_

namespace mysimulator {

  class FreeSpace {

    public:

      typedef FreeSpace   Type;

      FreeSpace() {}
      FreeSpace(const Type&) {}
      ~FreeSpace() {}

      Type& operator=(const Type&) { return *this; }

      operator bool() const { return true; }
      void reset() {}

  };

}

#endif

