
#ifndef _System_Base_Interface_H_
#define _System_Base_Interface_H_

#include "object/copy.h"
#include "object/allocate.h"
namespace mysimulator {

  template <typename T, template<typename> class SpaceType>
  struct SystemBase {

    public:

      typedef SystemBase<T,SpaceType>   Type;

      Object<SpaceType<T> > X;

      SystemBase() : X() {}
      ~SystemBase() { clearData(); }

      virtual void loadCoor(const SpaceType<T>& rX) {
        assert(IsValid(rX));
        imprint(X,rX);
        copy(X,rX);
      }
      void loadCoor(const Object<SpaceType<T> >& iX) {
        loadCoor(iX());
      }

      void clearData() { release(X); }
      bool isvalid() const { return IsValid(X); }

    private:

      SystemBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class SpaceType>
  void release(SystemBase<T,SpaceType>& S) { S.clearData(); }

  template <typename T, template<typename> class SpaceType>
  bool IsValid(const SystemBase<T,SpaceType>& S) { return S.isvalid(); }

}

#endif

