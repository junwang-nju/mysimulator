
#ifndef _Neighbor_Interface_Simple_Interface_H_
#define _Neighbor_Interface_Simple_Interface_H_

#include "system-interaction/interface.h"

namespace mysimulator {

  template <typename T,typename GT> class NeighborListSimple;
  template <typename T,typename GT> void Clear(NeighborListSimple<T,GT>&);
  template <typename T,typename GT> class NeighborListAccelerator_UniqueSkin;

  template <typename T,typename GT>
  class NeighborListSimple {

    public:

      typedef NeighborListSimple<T,GT>  Type;
      friend void Clear<T,GT>(NeighborListSimple<T,GT>&);
      friend class NeighborListAccelerator_UniqueSkin<T,GT>;

      NeighborListSimple() 
        : _FuncPool(),_IDPool(),_ParamPool(),_used(),_nused(0U),_CutR(0),
          _SkinR(0),_RunInteraction(NULL),_Dsp(),_BoundRSQ(0) {}
      ~NeighborListSimple() { Clear(*this); }

      bool IsValid() const {
        return
          _FuncPool.IsValid() && _IDPool.IsValid() && _ParamPool.IsValid() &&
          _used.IsValid() && (_nused==0) && (_CutR>0) && (_SkinR>0) &&
          (_FuncPool.Size()==_IDPool.Size()) &&
          (_FuncPool.Size()==_ParamPool.Size()) && (_RunInteraction!=NULL) &&
          _RadiusCheck();
      }

      Array<unsigned int>& Index(unsigned int i) {
        assert(_IDPool.IsValid());  return _IDPool[i];
      }
      const Array<unsigned int>& Index(unsigned int i) const {
        assert(_IDPool.IsValid());  return _IDPool[i];
      }

      Unique64Bit& Parameter(unsigned int i,unsigned int n) {
        assert(_ParamPool.IsValid());
        assert(_ParamPool[i]!=NULL);
        return (*_ParamPool[i])[n];
      }
      const Unique64Bit& Parameter(unsigned int i,unsigned int n) const {
        assert(_ParamPool.IsValid());
        assert(_ParamPool[i]!=NULL);
        return (*_ParamPool[i])[n];
      }
      void ParameterBuild(unsigned int i) {
        assert(_ParamPool.IsValid());
        assert(_ParamPool[i]!=NULL);
        _ParamPool[i]->Build();
      }

      void Allocate(const Array<InteractionFuncName>& IFN,unsigned int dim) {
        assert(_TagCheck(IFN));
        Clear(*this);
        const unsigned int n=IFN.Size();
        _FuncPool.Allocate(n);
        _IDPool.Allocate(n);
        _ParamPool.Allocate(n);
        for(unsigned int i=0;i<n;++i) {
          Introduce(_FuncPool[i],IFN[i],dim);
          Introduce(_ParamPool[i],IFN[i]);
          _IDPool[i].Allocate(InteractionFuncIDSize[IFN[i]]);
        }
        _used.Allocate(n);
        _nused=0;
        _Dsp.Allocate(dim);
      }
      void LoadTarget(const SystemInteraction<T,GT>& SI) {
        ClearTarget();
        _RunInteraction=const_cast<SystemInteraction<T,GT>*>(&SI);
      }

      template <typename T1>
      void SetCutRadius(const T1& CR) { _Copy(_CutR,CR); UpdateRadius(); }

      void Update(const Array2DNumeric<T>& X) {
        const unsigned int n=_FuncPool.Size();
        _nused=0;
        for(unsigned int i=0;i<n;++i)
          if(DistanceSQ(_Dsp,X[_IDPool[i][0]],X[_IDPool[i][1]],
                        _RunInteraction->Geometry())<_BoundRSQ) {
            _used[_nused]=i;
            ++_nused;
          }
        Clear(_RunInteraction->_Func);
        Clear(_RunInteraction->_ID);
        Clear(_RunInteraction->_Param);
        _RunInteraction->_Func.Allocate(_nused);
        _RunInteraction->_ID.Allocate(_nused);
        _RunInteraction->_Param.Allocate(_nused);
        unsigned int m;
        for(unsigned int i=0;i<_nused;++i) {
          m=_used[i];
          _RunInteraction->_Func[i]=_FuncPool[m];
          _RunInteraction->_ID[i].Refer(_IDPool[m]);
          _RunInteraction->_Param[i]=_ParamPool[m];
        }
      }

    protected:

      Array<InteractionFunc<T,GT>*>   _FuncPool;
      Array<Array<unsigned int> >     _IDPool;
      Array<InteractionParameter<T>*> _ParamPool;
      Array<unsigned int> _used;
      unsigned int _nused;
      T _CutR;
      T _SkinR;
      SystemInteraction<T,GT>* _RunInteraction;

      template <typename T1>
      void SetSkinRadius(const T1& SR) { _Copy(_SkinR,SR); UpdateRadius(); }
      void ClearTarget() {
        if(_RunInteraction!=NULL) Clear(_RunInteraction->_ID);
        _RunInteraction=NULL;
      }
      void ClearTMP() { Clear(_Dsp); _BoundRSQ=0; }

    private:

      ArrayNumeric<T>  _Dsp;
      T _BoundRSQ;

      NeighborListSimple(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      void UpdateRadius() {
        _BoundRSQ=_CutR+_SkinR;
        _BoundRSQ*=_BoundRSQ;
      }
      const T& _ParamCutRadius(unsigned int i) const {
        assert(_FuncPool.IsValid());
        assert(_ParamPool.IsValid());
        unsigned int n=0;
        switch(_FuncPool[i]->Name()) {
          case LJ612Cut: n=LJ612CutCutR;  break;
          case LJ1012Cut: n=LJ1012CutCutR;  break;
          case CoreLJ612: n=CoreLJ612Radius;  break;
          default: fprintf(stderr,"Improper Interaction Func Name!\n");
        }
        assert(n!=0);
        return Value<T>(Parameter(i,n));
      }
      bool _RadiusCheck() const {
        bool check=true;
        for(unsigned int i=0;i<_FuncPool.Size();++i)
          if(_ParamCutRadius(i)>_CutR)  { check=false; break; }
        return check;
      }
      bool _TagCheck(const Array<InteractionFuncName>& IFN) const {
        bool check=true;
        for(unsigned int i=0; check && (i<IFN.Size()); ++i)
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
  void Clear(NeighborListSimple<T,GT>& L) {
    L.ClearTarget();
    L.ClearTMP();
    L._SkinR=0;
    L._CutR=0;
    L._nused=0U;
    Clear(L._used);
    Clear(L._ParamPool);
    Clear(L._IDPool);
    Clear(L._FuncPool);
  }

}

#endif

