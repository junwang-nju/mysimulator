
#ifndef _System_Content_EGBase_Interface_H_
#define _System_Content_EGBase_Interface_H_

#include "system/content/base/interface.h"

namespace mysimulator {

  template <typename T,template<typename>class EGDataType>
  struct SystemContentEGBase : public SystemContentBase<T> {

    public:

      typedef SystemContentEGBase<T,EGDataType> Type;
      typedef SystemContentBase<T>  ParentType;

      EGDataType<T>  EGData;

      SystemContentEGBase() : ParentType(), EGData() {}
      ~SystemContentEGBase() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               EGData.IsValid();
      }

      void Refer(const Type& C) {
        static_cast<ParentType*>(this)->Refer(
            static_cast<const ParentType&>(C));
        EGData.Refer(C.EGData);
      }
      void Refer(const Type& C,unsigned int b,unsigned int n) {
        static_cast<ParentType*>(this)->Refer(
            static_cast<const ParentType&>(C),b,n);
        EGData.Refer(C.EGData,b,n);
      }

    private:

      SystemContentEGBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename>class EGT>
  void Clear(SystemContentEGBase<T,EGT>& C) {
    Clear(EGData);
    Clear(static_cast<typename SystemContentEGBase<T,EGT>::ParentType&>(C));
  }

}

#endif
