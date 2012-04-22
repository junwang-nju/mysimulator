
#ifndef _System_Content_VBase_Interface_H_
#define _System_Content_VBase_Interface_H_

#include "array/2d/interface.h"

namespace mysimulator {

  template <typename T,template<typename>class EGType>
  struct SystemContentVBase : public EGType<T> {

    public:

      typedef SystemContentVBase<T,EGType>    Type;
      typedef EGType<T>   ParentType;

      Array2D<T> Velocity;

      SystemContentVBase() : ParentType(), Velocity() {}
      ~SystemContentVBase() { Clear(); }

      void Clear() {
        Velocity.Clear(); static_cast<ParentType*>(this)->Clear();
      }
      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               Velocity.IsValid();
      }

      void Refer(const Type& C) {
        static_cast<ParentType*>(this)->Refer(
            static_cast<const ParentType&>(C));
        Velocity.Refer(C.Velocity);
      }
      void Refer(const Type& C,unsigned int b,unsigned int n) {
        static_cast<ParentType*>(this)->Refer(
            static_cast<const ParentType&>(C),b,n);
        Velocity.Refer(C.Velocity,b,n);
      }

    private:

      SystemContentVBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

