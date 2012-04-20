
#ifndef _System_Content_WithEGV_Interface_H_
#define _System_Content_WithEGV_Interface_H_

#include "system/content/with-eg/interface.h"

namespace mysimulator {

  template <typename T, typename DataType>
  struct SystemContentWithEGV : public SystemContentWithEG<T,DataType> {

    public:

      typedef SystemContentWithEGV<T,DataType>  Type;
      typedef SystemContentWithEG<T,DataType>   ParentType;

      DataType Velocity;

      SystemContentWithEGV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithEGV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithEGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename DT>
  void release(SystemContentWithEGV<T,DT>& C) { C.clearData(); }

  template <typename T, typename DT>
  bool IsValid(const SystemContentWithEGV<T,DT>& C) { return C.isvalid(); }

}

#endif

