
#ifndef _System_Content_WithMEGV_Interface_H_
#define _System_Content_WithMEGV_Interface_H_

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType>
  struct SysContentWithMEGV : public SysContentWithEGV<T,VecType> {

    public:

      typedef SysContentWithMEGV<T,VecType>   Type;
      typedef SysContentWithEGV<T,VecType>    ParentType;

      VecType<T>  Mass;
      VecType<T>  iMass;

      SysContentWithMEGV() : ParentType(), Mass(), iMass() {}
      ~SysContentWithMEGV() { clearData(); }

      void clearData() {
        release(iMass); release(Mass);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<ParentType*>(this)->isvalid()&&
               IsValid(Mass)&&IsValid(iMass);
      }

    private:

      SysContentWithMEGV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VecType>
  void release(SysContentWithMEGV<T,VecType>& S) { S.clearData(); }

  template <typename T, template<typename> class VecType>
  bool IsValid(const SysContentWithMEGV<T,VecType>& S) { return S.isvalid(); }

}

#endif

