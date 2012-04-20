
#ifndef _System_Content_WithV_Interface_H_
#define _System_Content_WithV_Interface_H_

#include "system/content/base/interface.h"
#include "system/content/data/null/interface.h"

namespace mysimulator {

  template <typename T, typename DataType>
  struct SystemContentWithV : public SystemContentBase<DataType> {

    public:

      typedef SystemContentWithV<T,DataType>    Type;
      typedef SystemContentBase<DataType>       ParentType;
      typedef SystemContentDataNull             EGDataType;

      DataType Velocity;

      SystemContentWithV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithV() { clearData(); }

      void clearData() {
        release(DataType);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename DT>
  void release(SystemContentWithV<T,DT>& C) { C.clearData(); }

  template <typename T, typename DT>
  bool IsValid(const SystemContentWithV<T,DT>& C) { return C.isvalid(); }

}

#endif

