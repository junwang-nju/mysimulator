
#ifndef _System_Content_WithG_Interface_H_
#define _System_Content_WithG_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/g/interface.h"

namespace mysimulator {

  template <typename T,typename DataType>
  struct SystemContentWithG : public SystemContentBase<DataType> {

    public:

      typedef SystemContentWithG<T,DataType>  Type;
      typedef SystemContentBase<DataType>     ParentType;
      typedef SystemContentDataG<DataType>    EGDataType;

      EGDataType  EGData;

      SystemContentWithG() : ParentType(), EGData() {}
      ~SystemContentWithG() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(EGData);
      }

    private:

      SystemContentWithG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename DT>
  void release(SystemContentWithG<T,DT>& C) { C.clearData(); }

  template <typename T,typename DT>
  bool IsValid(const SystemContentWithG<T,DT>& C) { return C.isvalid(); }

}

#endif

