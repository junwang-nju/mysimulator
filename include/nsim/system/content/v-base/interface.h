
#ifndef _System_Content_VBase_Interface_H_
#define _System_Content_VBase_Interface_H_

#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T,template<typename>class EGType>
  struct SystemContentVBase : public EGType<T> {

    public:

      typedef SystemContentVBase<T,EGType>    Type;
      typedef EGType<T>   ParentType;

      Array2D<T> Velocity;

      SystemContentVBase() : ParentType(), Velocity() {}
      ~SystemContentVBase() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               Velocity.IsValid();
      }

      template <typename T1>
      void Allocate(const Array2D<T1>& iX) {
        static_cast<ParentType*>(this)->Allocate(iX);
        ImprintStructure(Velocity,iX);
      }
      void Refer(Type& C) {
        static_cast<ParentType*>(this)->Refer(static_cast<ParentType&>(C));
        Velocity.Refer(C.Velocity);
      }
      void Refer(Type& C,unsigned int b,unsigned int n) {
        static_cast<ParentType*>(this)->Refer(static_cast<ParentType&>(C),b,n);
        Velocity.Refer(C.Velocity,b,n);
      }

    private:

      SystemContentVBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename>class EGT>
  void Clear(SystemContentVBase<T,EGT>& C) {
    Clear(C.Velocity);
    Clear(static_cast<typename SystemContentVBase<T,EGT>::ParentType&>(C));
  }
}

#endif

