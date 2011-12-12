
#ifndef _System_Masked_Component_Interface_H_
#define _System_Masked_Component_Interface_H_

#include "object/allocate.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, template <typename> class SpaceType>
  struct Mask4System {

    public:

      typedef Mask4System<T,SpaceType>   Type;

      Object<SpaceType<unsigned int> > iMask;
      Object<SpaceType<T> > Mask;

      Mask4System() : iMask(), Mask() {}
      ~Mask4System() { clearData(); }

      void clearData() { release(Mask); release(iMask); }
      bool isvalid() const { return IsValid(iMask)&&isvalid(Mask); }

      void loadMask(const SpaceType<unsigned int>& rMask) {
        imprint(Mask,rMask);
        copy(Mask,rMask);
        _imprint_structure(iMask,rMask);
        copy(iMask,rMask);
      }
      void loadMask(const Object<SpaceType<unsigned int> >& rMask) {
        loadMask(rMask());
      }

    private:

      Mask4System(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template <typename> class SpaceType>
  void release(Mask4System<T,SpaceType>& M) { M.clearData(); }

  template <typename T, template <typename> class SpaceType>
  bool IsValid(const Mask4System<T,SpaceType>& M) { return M.isvalid(); }

}

#endif

