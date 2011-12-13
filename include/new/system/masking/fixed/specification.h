
#ifndef _System_Masking_Fixed_Specification_H_
#define _System_Masking_Fixed_Specification_H_

#include "system/masking/interface.h"
#include "system/masking/component/interface.h"
#include "intrinsic-type/valid.h"

namespace mysimulator {

  template <typename T, template <typename> class SpaceType>
  struct SystemMasking<T,SpaceType,SystemFixed>
      : public Mask4System<T,SpaceType> {

    public:

      typedef SystemMasking<T,SpaceType,SystemFixed>   Type;
      typedef Mask4System<T,SpaceType> ParentType;

      SystemMasking() : ParentType() {}
      ~SystemMasking() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const { return static_cast<ParentType*>(this)->isvalid(); }

      void operator()(SpaceType<T>* pV, SpaceType<T>*) {
        assert(IsValid(pV));
        scale(*pV,this->Mask());
      }
      void operator()(Object<SpaceType<T> >* pV, SpaceType<T>* pG) {
        assert(IsValid(pV));
        operator()(pV->ptr,pG);
      }
      void operator()(SpaceType<T>* pV, Object<SpaceType<T> >* pG) {
        operator()(pV,static_cast<SpaceType<T>*>(NULL));
      }
      void operator()(Object<SpaceType<T> >* pV, Object<SpaceType<T> >* pG) {
        operator()(pV(),pG);
      }

    private:

      SystemMasking(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

