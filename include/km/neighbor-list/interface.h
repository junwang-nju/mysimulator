
#ifndef _Neighbor_List_Interface_H_
#define _Neighbor_List_Interface_H_

#include "system-interaction/interface.h"

namespace mysimulator {

  template <typename T,typename GT> class NeighborList;
  template <typename T,typename GT> void Clear(NeighborList<T,GT>&);

  template <typename T,typename GT>
  class NeighborList {

    public:

      typedef NeighborList<T,GT>    Type;
      friend void Clear<T,GT>(NeighborList<T,GT>&);

      NeighborList() : _FuncPool(),_IDPool(),_ParamPool(),_Used(),_NUsed(0U),
                       _CutR(0),_SkinR(0),_BoundRSQ(0),_HfSkinRSQ(0),Dsp() {}
      ~NeighborList() { Clear(*this); }

      bool IsValid() const {
        return
          _FuncPool.IsValid() && _IDPool.IsValid() && _ParamPool.IsValid() &&
          _Used.IsValid() && (_NUsed>0) && (_CutR>0) && (_SkinR>0) &&
          (_FuncPool.Size()==_IDPool.Size()) &&
          (_FuncPool.Size()==_ParamPool.Size()) &&
          (_FuncPool.Size()==_Used.Size()) && _RadiusCheck();
      }

      void Allocate(const Array<InteractionFuncName>& IFN, unsigned int dim) {
        assert(_TagCheck(IFN));
        Clear(*this);
        const unsigned int n=IFN.Size();
        _FuncPool.Allocate(n);
        _IDPool.Allocate(n);
        _ParamPool.Allocate(n);
        for(unsigned int i=0;i<n;++i) {
          Introduce(_FuncPool[i],IFN[i],dim);
          Introduce(_ParamPool[i],IFN[i]);
          _ID[i].Allocate(InteractionFuncIDSize[IFN[i]]);
        }
        _Used.Allocate(n);
        _NUsed=0;
        Dsp.Allocate(dim);
      }

      Array<unsigned int>& Index(unsigned int i) {
        assert(_IDPool.IsValid());  return _IDPool[i];
      }
      const Array<unsigned int>& Index(unsigned int i) {
        assert(_IDPool.IsValid());  return _IDPool[i];
      }

      Unique64Bit& Parameter(unsigned int n,unsigned int l) {
        assert(_ParamPool.IsValid());
        assert(_ParamPool[n]!=NULL);
        return (*_ParamPool[n])[l];
      }
      const Unique64Bit& Parameter(unsigned int n,unsigned int l) const {
        assert(_ParamPool.IsValid());
        assert(_ParamPool[n]!=NULL);
        return (*_ParamPool[n])[l];
      }

      void SetRadius(const T& CR, const T& SR) {
        _CutR=CR;
        _SkinR=SR;
        _HfSkinRSQ=_SkinR*0.5;
        _HfSkinRSQ*=_HfSkinRSQ;
        _BoundRSQ=_CutR+_SkinR;
        _BoundRSQ*=_BoundRSQ;
      }

      const T& ThresholdDistance() const { return _HfSkinRSQ; }

      void Update(const Array2DNumeric<T>& X, SystemInteraction<T,GT>& SI) {
        const unsigned int n=_FuncPool.Size();
        unsigned int I,J;
        T dist;
        _NUsed=0;
        for(unsigned int i=0;i<n;++i) {
          I=_IDPool[i][0];
          J=_IDPool[i][1];
          dist=DistanceSQ(Dsp,X[I],X[J],SI.Geometry());
          if(dist<_BoundRSQ) { _Used[_NUsed]=i; ++_NUsed; }
        }
        Clear(SI._Func);
        Clear(SI._ID);
        Clear(SI._Param);
        SI._Func.Allocate(_NUsed);
        SI._ID.Allocate(_NUsed);
        SI._Param.Allocate(_NUsed);
        unsigned int m;
        for(unsigned int i=0;i<_NUsed;++i) {
          m=_Used[i];
          SI._Func[i]=_FuncPool[m];
          SI._ID[i].Refer(_IDPool[m]);
          SI._Param[i]=_ParamPool[m];
        }
      }

    protected:

      Array<InteractionFunc<T,GT>*>   _FuncPool;
      Array<Array<unsigned int>* >    _IDPool;
      Array<InteractionParameter<T>*> _ParamPool;
      Array<unsigned int> _Used;
      unsigned int _NUsed;
      T _CutR;
      T _SkinR;
      T _BoundRSQ;
      T _HfSkinRSQ;

    private:

      NeighborList(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      const T& _CutRadius(unsigned int i) const {
        assert(_FuncPool.IsValid());
        assert(_ParamPool.IsValid());
        unsigned int n=0;
        switch(_FuncPool[i]->Name()) {
          case LJ612Cut: n=LJ612CutCutR;  break;
          case LJ1012Cut: n=LJ1012CutCutR; break;
          case CoreLJ612: n=CoreLJ612Radius; break;
          default: fprintf(stderr,"Improper Interaction Func Name!\n");
        }
        assert(n!=0);
        return Value<T>(Parameter(i,n));
      }

      bool _RadiusCheck() const {
        bool check=true;
        for(unsigned int i=0;i<_FuncPool.Size();++i)
          if(_CutRadius(i)>_CutR) { check=false; break; }
        return check;
      }
      bool _TagCheck(const Array<InteractionFuncName>& IFN) const {
        bool check=true;
        for(unsigned int i=0;check && (i<IFN.Size()) ;++i)
          switch(IFN[i]) {
            case LJ612Cut:
            case LJ1012Cut:
            case CoreLJ612: break;
            default: check=false;
          }
        return check;
      }
      
  };

  template <typename T,typename GT>
  void Clear(NeighborList<T,GT>& L) {
    L._HfSkinRSQ=0;
    L._SkinR=0;
    L._CutR=0;
    L._NUsed=0;
    Clear(L._Used);
    Clear(L._ParamPool);
    Clear(L._IDPool);
    Clear(L._FuncPool);
    Clear(L.Dsp);
  }

}

#endif

