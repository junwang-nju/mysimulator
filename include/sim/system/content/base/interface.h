
#ifndef _System_Content_Base_Interface_H_
#define _System_Content_Base_Interface_H_

#include "array/1d/release.h"

namespace mysimulator {

  template <typename DataType>
  struct SystemContentBase {

    public:
      
      typedef SystemContentBase<DataType>  Type;

      DataType* X;

      SystemContentBase() : X(NULL) {}
      ~SystemContentBase() { clearData(); }

      void clearData() { release(*X); release(X); }
      bool isvalid() const { return X!=NULL; }

    private:

      SystemContentBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename DT>
  void release(SystemContentBase<DT>& C) { C.clearData(); }

  template <typename DT>
  void IsValid(const SystemContentBase<DT>& C) { return C.isvalid(); }

}

#endif

