
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "interaction/calc.h"
#include "object/allocate.h"
#include "object/copy.h"
#include "intrinsic-type/constant.h"
#include "object/io.h"
#include "object/fill.h"

#define _LOAD(PART) \
  void load##PART(const PART##Type& i##PART) {\
    assert(IsValid(i##PART));\
    imprint(PART,i##PART);\
    copy(PART,i##PART);\
  }

namespace mysimulator {

  template <typename T, typename FuncType, typename IDType, typename ParamType,
            typename GeomType, template <typename> class SpaceType>
  struct System {

    public:

      typedef System<T,FuncType,IDType,ParamType,GeomType,SpaceType>  Type;

      FuncType  Func;
      IDType    ID;
      ParamType Param;
      GeomType  Geom;
      Object<SpaceType<T> >  X;
      Object<SpaceType<T> >  G;
      SpaceType<T>  Mask;
      SpaceType<unsigned int> UMask;
      T   Energy;

      System() : Func(), ID(), Param(), Geom(), X(), G(), Mask(), UMask(),
                 Energy(0) {}
      ~System() { clearData(); }

      void clearData() {
        release(Func);  release(ID);  release(Param); release(Geom);
        release(X); release(G); release(Mask); release(UMask); Energy=0;
      }
      bool isvalid() const {
        return
          IsValid(Func)&&IsValid(ID)&&IsValid(Param)&&IsValid(Geom)&&
          IsValid(X)&&IsValid(G)&&IsValid(Mask)&&IsValid(UMask);
      }

      _LOAD(Func)
      _LOAD(ID)
      _LOAD(Param)
      _LOAD(Geom)
      void loadCoor(const SpaceType<T>& iX) {
        assert(IsValid(iX));
        imprint(X,iX);
        imprint(G,iX);
        copy(X,iX);
        imprint(Mask,iX);
        if(IsValid(UMask))  copy(Mask,UMask);
      }
      void loadCoor(const Object<SpaceType<T> >& iX) { loadCoor(iX()); }
      void loadMask(const SpaceType<unsigned int>& iMask) {
        assert(IsValid(iMask));
        imprint(UMask,iMask);
        copy(UMask,iMask);
        if(IsValid(Mask)) copy(Mask,UMask);
      }
      void loadMask(const Object<SpaceType<unsigned int> >& iMask) {
        loadMask(iMask());
      }

      void UpdateE() { Energy=0; Calc(Func,X(),ID,Param,Geom,Energy); }
      void UpdateG() { fill(G,cZero); Calc(Func,X(),ID,Param,Geom,G()); }
      void Update()  {
        Energy=0; fill(G,cZero); Calc(Func,X(),ID,Param,Geom,Energy,G());
      }

    private:

      System(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename FT, typename IDT, typename PT, typename GT,
            template <typename> class ST>
  bool IsValid(const System<T,FT,IDT,PT,GT,ST>& S) { return S.isvalid(); }

  template <typename T, typename FT, typename IDT, typename PT, typename GT,
            template <typename> class ST>
  void release(System<T,FT,IDT,PT,GT,ST>& S) { S.clearData(); }

}

#undef _LOAD

#endif

