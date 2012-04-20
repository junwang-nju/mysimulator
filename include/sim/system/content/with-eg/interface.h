
#ifndef _System_Content_WithEG_Interface_H_
#define _System_Content_WithEG_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/eg/interface.h"

namespace mysimulator {

  template <typename T, typename DataType>
  struct SystemContentWithEG : public SystemContentBase<DataType> {

    public:

      typedef SystemContentWithEG<T,DataType>   Type;
      typedef SystemContentBase<DataType>       ParentType;
      typedef SystemContentDataEG<T,DataType>   EGDataType;

      EGDataType EGData;

      SystemContentWithEG() : ParentType(), EGData() {}
      ~SystemContentWithEG() { clearData(); }

      void clearData() {
        release(EGData);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(EGData);
      }

    private:

      SystemContentWithEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename DT>
  void release(SystemContentWithEG<T,DT>& C) { C.clearData(); }

  template <typename T, typename DT>
  bool IsValid(const SystemContentWithEG<T,DT>& C) { return C.isvalid(); }

}

#endif

