
#ifndef _System_ContentGrouping_Binding_Interface_H_
#define _System_ContentGrouping_Binding_Interface_H_

#include "array/1d/interface.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct SysContentGroupBinding {

    public:

      typedef SysContentGroupBinding<T,VecType,SysContentType>  Type;

      Array1D<SysContentType<T,VecType> > grpSysContent;

      SysContentGroupBinding() : grpSysContent() {}
      ~SysContentGroupBinding() { clearData(); }

      void clearData() { release(grpSysContent); }
      bool isvalid() const { return IsValid(grpSysContent); }

      void bind(const SysContentType<T,VecType>& S,
                const Array1DContent<Unique64Bit>& MerIDRange) {
        release(grpSysContent);
        allocate(grpSysContent,MerIDRange.size);
        for(unsigned int i=0;i<grpSysContent.size;++i)
          refer(grpSysContent[i],S,MerIDRange[i].u[0],MerIDRange[i].u[2]);
      }

    private:

      SysContentGroupBinding(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class VT,
            template<typename,template<typename> class> class SCT>
  void release(SysContentGroupBinding<T,VT,SCT>& B) { B.clearData(); }

  template <typename T,template<typename> class VT,
            template<typename,template<typename> class> class SCT>
  bool IsValid(const SysContentGroupBinding<T,VT,SCT>& B){ return B.isvalid(); }

}

#endif

