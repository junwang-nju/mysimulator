
#ifndef _System_Content_WithEV_Interface_H_
#define _System_Content_WithEV_Interface_H_

#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T, typename DataType>
  struct SystemContentWithEV : public SystemContentWithE<T,DataType> {

    public:

      typedef SystemContentWithEV<T,DataType>  Type;
      typedef SystemContentWithE<T,DataType>   ParentType;

      DataType Velocity;

      SystemContentWithEV() : ParentType(), Velocity(NULL) {}
      ~SystemContentWithEV() { clearData(); }

      void clearData() {
        release(Velocity);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (Velocity!=NULL);
      }

    private:

      SystemContentWithEV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename DT>
  void release(SystemContentWithEV<T,DT>& C) { C.clearData(); }

  template <typename T, typename DT>
  bool IsValid(const SystemContentWithEV<T,DT>& C) { return C.isvalid(); }

}

#endif

