
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "grouped-interaction/interface.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class System {

    public:

      typedef System<T,GeomType> Type;
      template <typename T1,typename GT>
      friend void Clear(System<T1,GT>&);

      System() : _X(), _G(), _V(), _E(), _F(), _GF() {}
      ~System() { Clear(*this); }

      bool IsValid() const { return _X.IsValid()&&_F.IsValid()&&_GF.IsValid(); }

      void AllocateXVGE(unsigned int n, unsigned int dim) {
        Clear(_X);
        _X.Allocate(n,dim);
        _CreateGVE();
      }
      void AllocateXVGE(const Array<unsigned int>& sz) {
        Clear(_X);
        _X.Allocate(sz);
        _CreateGVE();
      }
      template <typename T1,template<typename> class AF>
      void ImprintXVGE(const Array2DBase<T1,AF>& A) {
        Clear(_X);
        _X.ImprintStructure(A);
        _CreateGVE();
      }
      void AllocateInteraction(const Array<Array<InteractionFuncName> >& FN,
                               unsigned int dim) {
        Clear(_F);
        _F.Allocate(FN.Size());
        for(unsigned int i=0;i<_F.Size();++i) _F[i].Allocate(FN[i],dim);
      }
      void AssignNumberInteractionGroup(unsigned int n) {
        assert(_F.IsValid());
        _GF.Allocate(n);
        for(unsigned int i=0;i<n;++i) _GF[i].Introduce(_F);
      }

      Array2DNumeric<T>& Location() { assert(_X.IsValid()); return _X; }
      Array2DNumeric<T>& Gradient() { assert(_G.IsValid()); return _G; }
      Array2DNumeric<T>& Velocity() { assert(_V.IsValid()); return _V; }
      T& Energy() { assert(_E.IsValid()); return _E[0]; }
      SystemInteraction<T,GeomType>& Interaction(unsigned int n) {
        assert(_F.IsValid());
        return _F[n];
      }
      GroupedInteraction<T,GeomType>& InteractionGroup(unsigned int n) {
        assert(_GF.IsValid());
        return _GF[n];
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
      const SystemInteraction<T,GeomType>& Interaction(unsigned int n) const {
        assert(_F.IsValid());
        return _F[n];
      }
      const GroupedInteraction<T,GeomType>&
      InteractionGroup(unsigned int n) const {
        assert(_GF.IsValid());
        return _GF[n];
      }

      void UpdateE(unsigned int n) {
        assert(_X.IsValid());
        assert(_G.IsValid());
        assert(_GF.IsValid());
        _GF[n].Calc(_X,_E[0]);
      }
      void UpdateG(unsigned int n) {
        assert(_X.IsValid());
        assert(_G.IsValid());
        assert(_GF.IsValid());
        _GF[n].Calc(_X,_G);
      }
      void UpdateB(unsigned int n) {
        assert(_X.IsValid());
        assert(_G.IsValid());
        assert(_GF.IsValid());
        _GF[n].Calc(_X,_E[0],_G);
      }

    protected:

      Array2DNumeric<T>  _X;
      Array2DNumeric<T>  _G;
      Array2DNumeric<T>  _V;
      ArrayNumeric<T>    _E;
      Array<SystemInteraction<T,GeomType> > _F;
      Array<GroupedInteraction<T,GeomType> >  _GF;

    private:

      void _CreateGVE() {
        assert(_X.IsValid());
        Clear(_G);  _G.ImprintStructure(_X);
        Clear(_V);  _V.ImprintStructure(_X);
        Clear(_E);  _E.Allocate(1);
      }

      System(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GeomType>
  void Clear(System<T,GeomType>& S) {
    Clear(S._GF);
    Clear(S._F);
    Clear(S._X);
    Clear(S._G);
    Clear(S._V);
    Clear(S._E);
  }

}

#endif

