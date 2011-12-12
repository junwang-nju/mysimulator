
#ifndef _System_Masked_Method_Interface_H_
#define _System_Masked_Method_Interface_H_

#include "system/masked/method/name.h"
#include "system/masked/component/interface.h"
#include "system/masked/method/no-operation/do.h"
#include "system/masked/method/do-mask/do.h"

namespace mysimulator {

  template <SystemMaskMethodName MN,
            typename T, template<typename> class SpaceType>
  struct SystemMaskApply {

    public:

      typedef SystemMaskApply<MN,T,SpaceType>   Type;
      typedef void (*_ApplyType)(SpaceType<T>&,const Mask4System<T,SpaceType>&);

      static const _ApplyType _Apply=
        (MN==SystemNoOperation?_SystemNoOperationApply<T,SpaceType>::Do:
         MN==SystemDoMask?_SystemDoMaskApply<T,SpaceType>::Do:
         NULL);

      SystemMaskApply() {}
      ~SystemMaskApply() { clearData(); }

      void clearData() {}
      bool isvalid() const { return IsValid(_Apply); }

      void Do(SpaceType<T>& V, const Mask4System<T,SpaceType>& M) {
        assert(isvalid());
        _Apply(V,M);
      }
      void Do(Object<SpaceType<T> >& V, const Mask4System<T,SpaceType>& M) {
        Do(V(),M);
      }
      void Do(SpaceType<T>& V, const Object<Mask4System<T,SpaceType> >& M) {
        Do(V,M());
      }
      void Do(Object<SpaceType<T> >& V,
              const Object<Mask4System<T,SpaceType> >& M) { Do(V(),M()); }

    private:

      SystemMaskApply(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <SystemMaskMethodName MN,
            typename T, template<typename> class SpaceType>
  const typename SystemMaskApply<MN,T,SpaceType>::_ApplyType
  SystemMaskApply<MN,T,SpaceType>::_Apply;

  template <SystemMaskMethodName MN,
            typename T, template<typename> class SpaceType>
  void release(SystemMaskApply<MN,T,SpaceType>& A) { A.clearData(); }

  template <SystemMaskMethodName MN,
            typename T, template<typename> class SpaceType>
  bool IsValid(const SystemMaskApply<MN,T,SpaceType>& A) { return A.isvalid(); }

}

//#include "system/masked/method/fixed/specification.h"

#endif

