
#ifndef _Neighbor_List_Accelerator_MultiSkin_Interface_H_
#define _Neighbor_List_Accelerator_MultiSkin_Interface_H_

#include "neighbor-list-accelerator/interface.h"
#include "neighbor-list/interface.h"

namespace mysimulator {

  template <typename T,typename GT> class NeighborListAccelerator_MultiSkin;
  template <typename T,typename GT>
  void Clear(NeighborListAccelerator_MultiSkin<T,GT>&);

  template <typename T,typename GT>
  class NeighborListAccelerator_MultiSkin : public NeighborListAccelerator<T,GT> {

    public:

      typedef NeighborListAccelerator_MultiSkin<T,GT> Type;
      typedef NeighborListAccelerator<T,GT> ParentType;
      friend void Clear<T,GT>(NeighborListAccelerator_MultiSkin<T,GT>&);

      NeighborListAccelerator_MultiSkin() : ParentType(), _List() {}
      virtual ~NeighborListAccelerator_MultiSkin() { Clear(*this); }

      virtual bool IsValid() const { return _List.IsValid(); }
      virtual void ImprintX(const Array2DNumeric<T>& X) {
        assert(_List.IsValid());
        for(unsigned int i=0;i<_List.Size();++i) _List[i].ImprintSkin(X);
      }
      virtual void Init(const Array2DNumeric<T>& X) {
        for(unsigned int i=0;i<_List.Size();++i) _List[i].Init(X);
      }
      virtual void Update(const Array2DNumeric<T>& X) {
        for(unsigned int i=0;i<_List.Size();++i) _List[i].Update(X);
      }

      void Allocate(unsigned int n) { _List.Allocate(n); }
      NeighborList<T,GT>& List(unsigned int i) { return _List[i]; }
      const NeighborList<T,GT>& List(unsigned int i) const { return _List[i]; }

    protected:

      Array<NeighborList<T,GT> >  _List;

    private:

      NeighborListAccelerator_MultiSkin(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(NeighborListAccelerator_MultiSkin<T,GT>& A) { Clear(A._List); }

}

#endif

