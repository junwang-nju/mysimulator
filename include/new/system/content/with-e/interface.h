
#ifndef _System_Content_With_Energy_Interface_H_
#define _System_Content_With_Energy_Interface_H_

#include "system/content/base/interface.h"
#include "interaction/func/allocate.h"
#include "interaction/func/copy.h"

#define _LoadOp(_PART,_PART_Type) \
  void load##_PART(const _PART_Type& i##_PART) {\
    assert(IsValid(i##_PART));\
    imprint(_PART,i##_PART);\
    copy(_PART,i##_PART);\
  }

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template <typename> class SpaceType>
  struct SystemWithE : public SystemBase<T,SpaceType> {

    public:

      typedef SystemWithE<T,IDType,ParamType,GeomType,SpaceType>  Type;
      typedef SystemBase<T,SpaceType> ParentType;
      typedef InteractionFunc<GeomType,T> FuncType;

      FuncType Func;
      IDType  ID;
      ParamType Param;
      GeomType  Geo;
      T Energy;

      SystemWithE() : ParentType(), Func(), ID(), Param(), Geo(), Energy(0) {}
      ~SystemWithE() { clearData(); }

      void clearData() {
        Energy=0;
        release(Geo);
        release(Param);
        release(ID);
        release(Func);
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return IsValid(Func)&&IsValid(ID)&&IsValid(Param)&&IsValid(Geo)&&
               static_cast<const ParentType*>(this)->isvalid();
      }

      _LoadOp(Func,FuncType)
      _LoadOp(ID,IDType)
      _LoadOp(Param,ParamType)
      _LoadOp(Geo,GeomType)

      void UpdateE() { Energy=0; Calc(Func,this->X(),ID,Param,Geo,Energy); }
      void Update() { UpdateE(); }

    private:

      SystemWithE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template<typename> class SpaceType>
  void release(SystemWithE<T,IDType,ParamType,GeomType,SpaceType>& S) {
    S.clearData();
  }

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template<typename> class SpaceType>
  bool IsValid(const SystemWithE<T,IDType,ParamType,GeomType,SpaceType>& S) {
    return S.isvalid();
  }

}

#undef _LoadOp

#endif

