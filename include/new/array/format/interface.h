
#ifndef _Array_Format_Interface_H_
#define _Array_Format_Interface_H_

#include "pointer/interface.h"

namespace mysimulator {

  template <typename T, template <typename> class ArrayContent>
  struct ArrayFormat : public ArrayContent<T> {

    public:

      typedef ArrayFormat<T,ArrayContent>    Type;
      typedef ArrayContent<T>     ParentType;

      Pointer<T>        data;

      ArrayFormat() : ParentType(), data() {}
      ~ArrayFormat() { clearData(); }

      void clearData() {
        release(*static_cast<ParentType*>(this));
        release(data);
      }
      bool isvalid() const {
        return IsValid(data)&&IsValid(*static_cast<const ParentType*>(this));
      }

    protected:

      ArrayFormat(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template <typename> class AC>
  bool IsValid(const ArrayFormat<T,AC>& AF) { return AF.isvalid(); }

  template <typename T, template <typename> class AC>
  void release(ArrayFormat<T,AC>& AF) { AF.clearData(); }

}

#endif

