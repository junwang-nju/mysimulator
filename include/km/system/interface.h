
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system-interaction/interface.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class System {

    public:

      typedef System<T,GeomType> Type;
      template <typename T1,typename GT>
      friend void Clear(System<T1,GT>&);

      System() : _X(), _G(), _V(), _E(), _F() {}
      ~System() { Clear(*this); }

      bool IsValid() const { return _X.IsValid()&&_F.IsValid(); }

      Array2DNumeric<T>& Location() { assert(_X.IsValid()); return _X; }
      Array2DNumeric<T>& Velocity() { assert(_V.IsValid()); return _V; }
      SystemInteraction<T,GeomType>& Interaction() {
        assert(_F.IsValid());
        return _F;
      }

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
      const SystemInteraction<T,GeomType>& Interaction() const {
        assert(_F.IsValid());
        return _F;
      }

    protected:

      Array2DNumeric<T>  _X;
      Array2DNumeric<T>  _G;
      Array2DNumeric<T>  _V;
      ArrayNumeric<T>    _E;
      SystemInteraction<T,GeomType> _F;

    private:

      System(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GeomType>
  void Clear(System<T,GeomType>& S) {
    Clear(S._F);
    Clear(S._X);
    Clear(S._G);
    Clear(S._V);
    Clear(S._E);
  }

}

#endif

