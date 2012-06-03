
#ifndef _Neighbor_List_Accelerator_UniqueSkin_Interface_H_
#define _Neighbor_List_Accelerator_UniqueSkin_Interface_H_

#include "neighbor-list-accelerator/interface.h"
#include "neighbor-list-simple/interface.h"
#include "neighbor-list-skin/interface.h"

namespace mysimulator {

  template <typename T,typename GT> class NeighborListAccelerator_UniqueSkin;
  template <typename T,typename GT>
  void Clear(NeighborListAccelerator_UniqueSkin<T,GT>&);

  template <typename T,typename GT>
  class NeighborListAccelerator_UniqueSkin : public NeighborListAccelerator<T,GT> {

    public:

      typedef NeighborListAccelerator_UniqueSkin<T,GT>    Type;
      typedef NeighborListAccelerator<T,GT>   ParentType;
      friend void Clear<T,GT>(NeighborListAccelerator_UniqueSkin<T,GT>&);

      NeighborListAccelerator_UniqueSkin() : ParentType(),_List(),_Skin() {}
      virtual ~NeighborListAccelerator_UniqueSkin() { Clear(*this); }

      virtual bool IsValid() const { return _List.IsValid() && _Skin.IsValid(); }
      virtual void ImprintX(const Array2DNumeric<T>& X) { _Skin.Imprint(X); }
      virtual void Init(const Array2DNumeric<T>& X) {
        for(unsigned int i=0;i<_List.Size();++i)  _List[i].Update(X);
        _Skin.Update(X);
      }
      virtual void Update(const Array2DNumeric<T>& X){
        if(_Skin.Check(X,_List[0]._RunInteraction->Geometry())) Init(X);
      }

      template <typename T1>
      void SetSkinRadius(const T1& SR) {
        _Skin.SetSkinRadius(SR);
        for(unsigned int i=0;i<_List.Size();++i) _List[i].SetSkinRadius(SR);
      }
      void Allocate(unsigned int n) { _List.Allocate(n); }
      NeighborListSimple<T,GT>& List(unsigned int i) { return _List[i]; }
      const NeighborListSimple<T,GT>& List(unsigned int i) const{ return _List[i]; }

    protected:

      Array<NeighborListSimple<T,GT> > _List;
      NeighborListSkin<T> _Skin;

    private:

      NeighborListAccelerator_UniqueSkin(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(NeighborListAccelerator_UniqueSkin<T,GT>& A) {
    Clear(A._Skin);
    Clear(A._List);
  }

}

#endif

