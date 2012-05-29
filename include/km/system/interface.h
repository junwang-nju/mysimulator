
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "grouped-interaction/interface.h"
#include "system/monomer-kind-name.h"

namespace mysimulator {

  template <typename T,typename GT> class System;
  template <typename T,typename GT> void Clear(System<T,GT>&);

  template <typename T,typename GeomType>
  class System {

    public:

      typedef System<T,GeomType> Type;
      friend void Clear<T,GeomType>(System<T,GeomType>&);

      System() : _Kind(),_X(), _G(), _V(), _E(), _F(), _GF() {}
      ~System() { Clear(*this); }

      bool IsValid() const {
        return _Kind.IsValid()&&_X.IsValid()&&_F.IsValid()&&_GF.IsValid();
      }

      void AllocateKind(unsigned int n) { Clear(_Kind); _Kind.Allocate(n); }

      void AllocateXVGE(unsigned int dim) {
        assert(_Kind.IsValid());
        ArrayNumeric<unsigned int> sz;
        sz.ImprintStructure(_Kind);
        sz.Fill(dim);
        for(unsigned int i=0;i<sz.Size();++i)
          sz[i]+=MonomerAltDimension[_Kind[i]];
        Clear(_X);
        _X.Allocate(sz);
        _CreateGVE();
        if(_F.IsValid())
          for(unsigned int i=0;i<_F.Size();++i) _F[i].ImprintGE(_X);
      }
      template <typename T1,template<typename> class AF>
      void ImprintXVGE(const Array2DBase<T1,AF>& A) {
        Clear(_X);
        _X.ImprintStructure(A);
        _CreateGVE();
        if(_F.IsValid())
          for(unsigned int i=0;i<_F.Size();++i) _F[i].ImprintGE(_X);
      }
      void AllocateInteraction(const Array<Array<InteractionFuncName> >& FN,
                               unsigned int dim) {
        Clear(_F);
        _F.Allocate(FN.Size());
        for(unsigned int i=0;i<_F.Size();++i) _F[i].Allocate(FN[i],dim);
        if(_X.IsValid())
          for(unsigned int i=0;i<_F.Size();++i) _F[i].ImprintGE(_X);
      }
      void AssignNumberInteractionGroup(unsigned int n) {
        assert(_F.IsValid());
        _GF.Allocate(n);
        for(unsigned int i=0;i<n;++i) _GF[i].Introduce(_F);
      }

      MonomerKindName& Kind(unsigned int n) {
        assert(_Kind.IsValid());  return _Kind[n];
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

      const MonomerKindName Kind(unsigned int n) const {
        assert(_Kind.IsValid());  return _Kind[n];
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
      const ArrayNumeric<T>& EnergyStorage() const {
        assert(_E.IsValid()); return _E;
      }
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

      Array<MonomerKindName>  _Kind;
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
    Clear(S._Kind);
  }

}

#endif

