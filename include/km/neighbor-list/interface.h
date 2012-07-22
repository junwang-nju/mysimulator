
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

      NeighborList() : _IDPool(), _ParamPool(), _Used(), _Tag(), _CutR(0),
                       _SkinR(0), _BoundRSQ(0) {}
      ~NeighborList() { Clear(*this); }

      bool IsValid() const {
        return _IDPool.IsValid()&&_ParamPool.IsValid()&&_Used.IsValid()&&
               (_IDPool.Size()==_ParamPool.Size())&&
               (_IDPool.Size()==_Used.Size())&&(_CutR>0)&&(_SkinR>0)&&
               _CheckRadius();
      }
      void Allocate(const Array<InteractionFuncName>& PIFN) {
        assert(_CheckType(PIFN));
        Clear(*this);
        _Tag.Allocate(PIFN.Size());
        _Tag.Copy(PIFN);
        _IDPool.Allocate(PIFN.Size());
        _ParamPool.Allocate(PIFN.Size());
        for(unsigned int i=0;i<PIFN.Size();++i) {
          Introduce(_ParamPool[i],PIFN[i]);
          _ID[i].Allocate(InteractionFuncIDSize[PIFN[i]]);
        }
        _Used.Allocate(PIFN.Size());
      }

      Array<unsigned int>& Index(unsigned int i) {
        assert(_IDPool.IsValid()); return _IDPool[i];
      }
      Unique64Bit& Parameter(unsigned int n,unsigned int l) {
        assert(_ParamPool.IsValid());
        assert(_ParamPool[n]!=NULL);
        return (*_ParamPool[n])[l];
      }
      const Array<unsigned int>& Index(unsigned int i) const {
        assert(_IDPool.IsValid()); return _IDPool[i];
      }
      const Unique64Bit& Parameter(unsigned int n,unsigned int l) const {
        assert(_ParamPool.IsValid());
        assert(_ParamPool[n]!=NULL);
        return (*_ParamPool[n])[l];
      }

      void SetRadius(const T& CR, const T& SR) {
        _CutR=CR;
        _SkinR=SR;
        _BoundRSQ=_CutR+_SkinR;
        _BoundRSQ*=_BoundRSQ;
      }
      void Update(SystemInteraction<T,GT>& SI) {
      }

    protected:

      Array<Array<unsigned int> >     _IDPool;
      Array<InteractionParameter<T>*> _ParamPool;
      Array<bool>                     _Used;
      Arrag<InteractionFuncName>      _Tag;
      T _CutR;
      T _SkinR;
      T _BoundRSQ;

    private:

      NeighborList(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      bool _CheckRadius() const {
        bool _check=true;
        for(unsigned int i=0;_check&&(i<_ParamPool.Size());++i)
          switch(_Tag[i]) {
            case LJ612Cut:
              if(Parameter(i,LJ612CutCutR)>_CutR) _check=false;
              break;
            case LJ1012Cut:
              if(Parameter(i,LJ1012CutCutR)>_CutR)  _check=false;
              break;
            case CoreLJ612:
              if(Parameter(i,CoreLJ612Radius)>_CutR)  _check=false;
              break;
            default:
              fprintf(stderr,"Improper Interaction Func Name!\n");
          }
        return _check;
      }
      bool _CheckType(const SystemInteraction<T,GT>& SI) const {
        assert(IsValid());
        assert(SI._Func.Size()==_Tag.Size());
        bool _check=true;
        for(unsigned int i=0;i<SI._Func.Size();++i)
          if(SI._Func[i]->Name()!=_Tag[i]) { _check=false; break; }
        return _check;
      }
      bool _CheckType(const Array<InteractionFuncName>& IFN) {
        bool _check=true;
        for(unsigned int i=0;_check&&(i<IFN.Size());++i)
          switch(IFN[i]) {
            case LJ612Cut:
            case LJ1012Cut:
            case CoreLJ612: break;
            default:  _check=false;
          }
        return _check;
      }

      bool _Check(const SystemInteraction<T,GT>& S) const {
        assert(_CheckType(S));
        bool _check=false;
        for(unsigned int i=0;i<S._Func.Size();++i) {
          if(S._Func[i]->_pre[PairwiseDistanceSQ]>_BoundRSQ) {
            _check=true; break;
          }
          return _check;
      }

  };

  template <typename T,typename GT>
  void Clear(NeighborList<T,GT>& L) {
    L._BoundRSQ=0;
    L._SkinR=0;
    L._CutR=0;
    Clear(L._Used);
    Clear(L._ParamPool);
    Clear(L._IDPool);
  }

}

#endif

