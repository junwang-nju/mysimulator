
#ifndef _System_Masking_Free_Specification_H_
#define _System_Masking_Free_Specification_H_

#include "system/masking/interface.h"
#include "system/masking/component/interface.h"
#include "intrinsic-type/valid.h"

namespace mysimulator {

  template <typename T, template <typename> class SpaceType>
  struct SystemMasking<T,SpaceType,SystemFree> {

    public:

      typedef SystemMasking<T,SpaceType,SystemFree>   Type;
      typedef Mask4System<T,SpaceType>    ParentType;

      SystemMasking() : ParentType() {}
      ~SystemMasking() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const { return static_cast<ParentType*>(this)->isvalid(); }

      void operator()(SpaceType<T>*, SpaceType<T>* pG) {
        assert(IsValid(pG));
        scale(*pG,this->Mask());
      }
      void operator()(Object<SpaceType<T> >*,SpaceType<T>* pG) {
        operator()(NULL,pG);
      }
      void operator()(SpaceType<T>*,Object<SpaceType<T> >* pG) {
        assert(IsValid(pG));
        operator()(NULL,pG->ptr);
      }
      void operator()(Object<SpaceType<T> >*,Object<SpaceType<T> >* pG) {
        operator()(NULL,pG);
      }

  };

}

#endif

