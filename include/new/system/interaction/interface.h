
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "object/allocate.h"
#include "object/copy.h"
#include "interaction/func/allocate.h"
#include "interaction/func/copy.h"

namespace mysimulator {

#define _LoadVal(Part) \
  void load##Part(const Part##Type& i##Part) {\
    assert(IsValid(i##Part));\
    imprint(Part,i##Part);\
    copy(Part,i##Part);\
  }

#define _LoadObj(Part) \
  void load##Part(const Object<Part##Type>& i##Part) { load##Part(i##Part()); }

#define _Load(Part) \
  _LoadVal(Part) \
  _LoadObj(Part)

  template <typename IDType, typename ParamType, typename GeomType, typename T>
  struct SysInteraction {

    public:

      typedef SysInteraction<IDType,ParamType,GeomType,T>     Type;
      typedef InteractionFunc<GeomType,T>   FuncType;

      Object<FuncType>    Func;
      Object<IDType>      ID;
      Object<ParamType>   Param;
      Object<GeomType>    Geom;

      SysInteraction() : Func(), ID(), Param(), Geom() {}
      ~SysInteraction() { clearData(); }

      void clearData() {
        release(Geom); release(Param); release(ID);  release(Func);
      }
      bool isvalid() const {
        return IsValid(Func)&&IsValid(ID)&&IsValid(Param)&&IsValid(Geom);
      }

      _Load(Func)
      _Load(ID)
      _Load(Param)
      _Load(Geom)

    private:

      SysInteraction(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

#undef _Load

  template <typename IDType, typename ParamType, typename GeomType, typename T>
  void release(SysInteraction<IDType,ParamType,GeomType,T>& SI) {
    SI.clearData();
  }

  template <typename IDType, typename ParamType, typename GeomType, typename T>
  bool IsValid(const SysInteraction<IDType,ParamType,GeomType,T>& SI) {
    return SI.isvalid();
  }

}

#endif

