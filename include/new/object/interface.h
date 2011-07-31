
#ifndef _Object_Interface_H_
#define _Object_Interface_H_

#include "pointer/interface.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  struct Object : public Pointer<T> {

    public:

      typedef Object<T>   Type;
      typedef Pointer<T>  ParentType;

      Object() : ParentType() {}
      ~Object() { clearData(); }

      bool _isparentvalid() {return static_cast<ParentType*>(this)->isvalid();}

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const { return _isparentvalid()&&IsValid(operator()()); }

      T& operator()() { assert(_isparentvalid()); return *(this->ptr); }
      const T& operator()() const {
        assert(_isparentvalid());
        return *(this->ptr);
      }

    private:

      Object(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Object<T>& O) { return O.isvalid(); }

  template <typename T>
  void release(Object<T>& O) { O. clearData(); }

}

#endif

