
#ifndef _Neighbor_List_Interface_H_
#define _Neighbor_List_Interface_H_

#include "neighbor-list-simple/interface.h"
#include "neighbor-list-skin/interface.h"

namespace mysimulator {

  template <typename T,typename GT> class NeighborList;
  template <typename T,typename GT> void Clear(NeighborList<T,GT>&);

  template <typename T,typename GT>
  class NeighborList : public NeighborListSimple<T,GT> {

    public:

      typedef NeighborList<T,GT>  Type;
      typedef NeighborListSimple<T,GT> ParentType;
      friend void Clear<T,GT>(NeighborList<T,GT>&);

      NeighborList() : ParentType(), _Skin() {}
      ~NeighborList() { Clear(*this); }

      bool IsValid() const { return ParentType::IsValid()&&_Skin.IsValid(); }

      void ImprintSkin(const Array2DNumeric<T>& X) { _Skin.Imprint(X); }
      void SetListRadius(const T& CR, const T& SR) {
        _Skin.SetSkinRadius(SR);
        ParentType::SetCutRadius(CR);
        ParentType::SetSkinRadius(SR);
      }

      void Init(const Array2DNumeric<T>& X) { ParentType::Update(X); _Skin.Update(X); }
      void Update(const Array2DNumeric<T>& X) {
        if(_Skin.Check(X,ParentType::_RunInteraction->Geometry())) Init(X);
      }

    protected:

      NeighborListSkin<T> _Skin;

    private:

      NeighborList(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(NeighborList<T,GT>& L) {
    Clear(L._Skin);
    typedef typename NeighborList<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(L));
  }

}

#endif

