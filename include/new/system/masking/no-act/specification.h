
#ifndef _System_Masking_NoAct_Specification_H_
#define _System_Masking_NoAct_Specification_H_

#include "system/masking/interface.h"
#include "system/masking/component/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class SpaceType>
  struct SystemMasking<T,SpaceType,SystemNoMask>
      : public Mask4System<T,SpaceType> {

    public:

      typedef SystemMasking<T,SpaceType,SystemNoMask>      Type;
      typedef Mask4System<T,SpaceType>  ParentType;

      SystemMasking() : ParentType() {}
      ~SystemMasking() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() { return static_cast<ParentType*>(this)->isvalid(); }

      void operator()(SpaceType<T>* pV, SpaceType<T>* pG) {}
      void operator()(SpaceType<T>* pV, Object<SpaceType<T> >* pG) {}
      void operator()(Object<SpaceType<T> >* pV, SpaceType<T>* pG) {}
      void operator()(Object<SpaceType<T> >* pV, Object<SpaceType<T> >* pG) {}

    private:

      SystemMasking(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

