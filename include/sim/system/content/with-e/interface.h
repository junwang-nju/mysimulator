
#ifndef _System_Content_WithE_Interface_H_
#define _System_Content_WithE_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T, typename DataType>
  struct SystemContentWithE : public SystemContentBase<DataType> {

    public:

      typedef SystemContentWithE<T,DataType>    Type;
      typedef SystemContentBase<DataType>       ParentType;
      typedef SystemContentDataE<T>             EGDataType;

      EGDataType  EGData;

      SystemContentWithE() : ParentType(), EGData() {}
      ~SystemContentWithE() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(EGData);
      }

    private:

      SystemContentWithE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename DT>
  void release(SystemContentWithE<T,DT>& C) { C.clearData(); }

  template <typename T, typename DT>
  bool IsValid(const SystemContentWithE<T,DT>& C) { return C.isvalid(); }

}

#endif

