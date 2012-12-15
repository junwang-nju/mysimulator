
#ifndef _Geometry_Boundary_FreeSpace_Interface_H_
#define _Geometry_Boundary_FreeSpace_Interface_H_

namespace mysimulator {

  template <unsigned int DIM>
  class FreeSpace {

    public:

      typedef FreeSpace Type;

      static const unsigned int Dimension=DIM;

      FreeSpace() {}
      FreeSpace(const Type&) {}
      FreeSpace(Type&&) {}
      ~FreeSpace() {}

      Type& operator=(const Type&) { return *this; }

      operator bool() const { return true; }
      void reset() {}

      void allocate() {}

      void swap(Type&) {}

  };

  template <unsigned int DIM>
  const unsigned int FreeSpace<DIM>::Dimension;

}

#include <algorithm>

namespace std {

  template <unsigned int DIM>
  void swap(mysimulator::FreeSpace<DIM>& FA,mysimulator::FreeSpace<DIM>& FB) {
    FA.swap(FB);
  }

}

#endif

