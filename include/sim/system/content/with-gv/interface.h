
#ifndef _System_Content_WithGV_Interface_H_
#define _System_Content_WithGV_Interface_H_

#include "system/content/with-g/interface.h"

namespace mysimulator {

  template <typename T, typename DataType>
  struct SystemContentWithGV : public SystemContentWithG<T,DataType> {

    public:

      typedef SystemContentWithGV<T,DataType>  Type;
      typedef SystemContentWithG<T,DataType>   ParentType;

      DataType Velocity;

      SystemContentWithGV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithGV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename DT>
  void release(SystemContentWithGV<T,DT>& C) { C.clearData(); }

  template <typename T, typename DT>
  bool IsValid(const SystemContentWithGV<T,DT>& C) { return C.isvalid(); }

}

#endif

