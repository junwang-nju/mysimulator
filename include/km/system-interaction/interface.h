
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "interaction-func/interface.h"
#include "interaction-parameter/interface.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class SystemInteraction {

    public:

      typedef SystemInteraction<T,GeomType>   Type;
      template <typename T1,typename GT>
      friend void Clear(SystemInteraction<T1,GT>&);

      SystemInteraction() : _Func(), _ID(), _Param(), _Geom(), _E(), _G() {}
      ~SystemInteraction() { Clear(*this); }

      bool IsValid() const {
        return _Func.IsValid()&&_ID.IsValid()&&_Param.IsValid()&&
               _Geom.IsValid();
      }

      InteractionFunc<T,GeomType>* Function(unsigned int n) const {
        assert(_Func.IsValid());
        assert(_Func[n]!=NULL);
        return _Func[n];
      }
      Unique64Bit& Parameter(unsigned int n,unsigned int l) {
        assert(_Param.IsValid());
        assert(_Param[n]!=NULL);
        return (*_Param[n])[l];
      }
      ArrayNumeric<unsigned int>& Index(unsigned int n) {
        assert(_ID.IsValid());
        return _ID[n];
      }
      GeomType& Geometry() {
        assert(_Geom.IsValid());
        return _Geom;
      }
      const Unique64Bit& Parameter(unsigned int n,unsigned int l) const {
        assert(_Param.IsValid());
        assert(_Param[n]!=NULL);
        return (*_Param[n])[l];
      }
      const ArrayNumeric<unsigned int>& Index(unsigned int n) const {
        assert(_ID.IsValid());
        return _ID[n];
      }
      const GeomType& Geometry() const {
        assert(_Geom.IsValid());
        return _Geom;
      }

      const T& Energy() const { assert(_E.IsValid()); return _E[0]; }
      const Array2DNumeric<T>& Gradient() const {
        assert(_G.IsValid()); return _G;
      }

      void Allocate(const Array<InteractionFuncName>& IFN, unsigned int dim) {
        Clear(*this);
        _Func.Allocate(IFN.Size());
        _ID.Allocate(IFN.Size());
        _Param.Allocate(IFN.Size());
        for(unsigned int i=0;i<IFN.Size();++i) {
          Introduce(_Func[i],IFN[i],dim);
          Introduce(_Param[i],IFN[i]);
          _ID[i].Allocate(InteractionFuncIDSize[IFN[i]]);
        }
        _Geom.Allocate(dim);
      }

      void CalcE(const ArrayNumeric<ArrayNumeric<T> >& X) {
        assert(IsValid()&&_E.IsValid());
        assert(_Func.Size()==_ID.Size());
        assert(_Func.Size()==_Param.Size());
        _E[0]=0;
        for(unsigned int i=0;i<_Func.Size();++i)
          _Func[i]->EMethod(X,_ID[i],_Param[i],_Geom,_E[0]);
      }
      void CalcG(const ArrayNumeric<ArrayNumeric<T> >& X) {
        assert(IsValid()&&_G.IsValid());
        assert(_Func.Size()==_ID.Size());
        assert(_Func.Size()==_Param.Size());
        BlasFill(_G,0);
        for(unsigned int i=0;i<_Func.Size();++i)
          _Func[i]->GMethod(X,_ID[i],_Param[i],_Geom,_G);
      }
      void CalcB(const ArrayNumeric<ArrayNumeric<T> >& X) {
        assert(IsValid()&&_E.IsValid()&&_G.IsValid());
        assert(_Func.Size()==_ID.Size());
        assert(_Func.Size()==_Param.Size());
        _E[0]=0;
        BlasFill(_G,0);
        for(unsigned int i=0;i<_Func.Size();++i)
          _Func[i]->BMethod(X,_ID[i],_Param[i],_Geom,_E[0],_G);
      }

    protected:

      Array<InteractionFunc<T,GeomType>*> _Func;
      Array<Array<unsigned int> >         _ID;
      Array<InteractionParameter<T>*>     _Param;
      GeomType                            _Geom;
      ArrayNumeric<T>                     _E;
      Array2DNumeric<T>                   _G;

    private:

      SystemInteraction(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(SystemInteraction<T,GT>& I) {
    Clear(I._Func);
    Clear(I._ID);
    Clear(I._Param);
    Clear(I._Geom);
    Clear(I._E);
    Clear(I._G);
  }

}

#endif
