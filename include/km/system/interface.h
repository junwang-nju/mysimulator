
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "array2d-numeric/interface.h"

namespace mysimulator {

  template <typename T>
  class System {

    public:

      typedef System<T> Type;

      System() : _X(), _G(), _V(), _E() {}
      ~System() { Clear(*this); }

      Array2DNumeric<T>& Location() { assert(_X.IsValid()); return _X; }
      Array2DNumeric<T>& Gradient() { assert(_G.IsValid()); return _G; }
      Array2DNumeric<T>& Velocity() { assert(_V.IsValid()); return _V; }
      T& Energy() { assert(_E.IsValid()); return _E[0]; }

      const Array2DNumeric<T>& Location() const {
        assert(_X.IsValid()); return _X;
      }
      const Array2DNumeric<T>& Gradient() const {
        assert(_G.IsValid()); return _G;
      }
      const Array2DNumeric<T>& Velocity() const {
        assert(_V.IsValid()); return _V;
      }
      const T& Energy() const { assert(_E.IsValid()); return _E[0]; }

    private:

      Array2DNumeric<T>  _X;
      Array2DNumeric<T>  _G;
      Array2DNumeric<T>  _V;
      ArrayNumeric<T>    _E;

  };

}

#endif

