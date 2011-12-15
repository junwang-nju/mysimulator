
#ifndef _System_Masked_Method_NoOperation_Specification_H_
#define _System_Masked_Method_NoOperation_Specification_H_

#include "system/masked/method/interface.h"

namespace mysimulator {

  template <>
  struct SystemMaskApply<SystemNoOperation> {

    public:

      typedef SystemMaskApply<SystemNoOperation>  Type;

      SystemMaskApply() {}
      ~SystemMaskApply() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

      template <typename T, template<typename> class SpaceType>
      void Do(SpaceType<T>& V, const Mask4System<T,SpaceType>& M) {}

      template <typename T, template<typename> class SpaceType>
      void Do(Object<SpaceType<T> >& V, const Mask4System<T,SpaceType>& M) {}

      template <typename T, template<typename> class SpaceType>
      void Do(SpaceType<T>& V, const Object<Mask4System<T,SpaceType> >& M) {}

      template <typename T, template<typename> class SpaceType>
      void Do(Object<SpaceType<T> >& V,
              const Object<Mask4System<T,SpaceType> >& M) {}

    private:

      SystemMaskApply(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

