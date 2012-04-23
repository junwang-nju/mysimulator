
#ifndef _Interaction_Func_Interface_H_
#define _Interaction_Func_Interface_H_

#include "interaction/buffer/interface.h"

#include "interaction/func/impl/pairwise/func.h"
#include "interaction/func/impl/pairwise/diff.h"
#include "interaction/func/impl/pairwise/both.h"

#include "interaction/func/impl/angle/func.h"
#include "interaction/func/impl/angle/diff.h"
#include "interaction/func/impl/angle/both.h"

#include "interaction/func/method/pairwise/energy.h"
#include "interaction/func/method/pairwise/gradient.h"
#include "interaction/func/method/pairwise/both.h"

#include "interaction/func/method/angle/energy.h"
#include "interaction/func/method/angle/gradient.h"
#include "interaction/func/method/angle/both.h"

#if !(defined(_FUNC_DCL)||defined(_METHOD_DCL))
#define _FUNC_DCL const Array1D<T>&,const Array1D<Unique64Bit>&
#define _METHOD_DCL const Array1D<Array1D<T> >&,const Array1D<unsigned int>&,const Array1D<Unique64Bit>&,InteractionBuffer<T>&,const GeomType&
#else
#error "Duplicate Definition for Macro _FUNC_DCL, _METHOD_DCL"
#endif

namespace mysimulator {

  template <typename GeomType,typename T>
  struct InteractionFunc {

    public:

      typedef InteractionFunc<GeomType,T>   Type;

      typedef void (*EFuncType)(_FUNC_DCL,T*);
      typedef void (*GFuncType)(_FUNC_DCL,T*);
      typedef void (*BFuncType)(_FUNC_DCL,T*,T*);
      typedef void (*EMethodType)(_METHOD_DCL,T&,EFuncType);
      typedef void (*GMethodType)(_METHOD_DCL,Array1D<Array1D<T> >&,GFuncType);
      typedef void (*BMethodType)(_METHOD_DCL,T&,Array1D<Array1D<T> >&,
                                  BFuncType);

      InteractionFuncName       tag;
      EFuncType                 EFunc;
      GFuncType                 GFunc;
      BFuncType                 BFunc;
      EMethodType               EMethod;
      GMethodType               GMethod;
      BMethodType               BMethod;

      InteractionFunc()
        : tag(UnknownInteactionFunc), EFunc(NULL), GFunc(NULL), BFunc(NULL),
          EMethod(NULL), GMethod(NULL), BMethod(NULL) {}
      ~InteractionFunc() { Clear(*this); }

      void IsValid() const {
        return (tag!=UnknownInteactionFunc)&&
               ((EMethod!=NULL)||(GMethod!=NULL)||(BMethod!=NULL));
      }

      void Allocate(const InteractionFuncName itag) {
        Clear(*this);
        tag=itag;
        switch(itag) {
          case Harmonic:
            EFunc=FuncHarmonic<T>;
            GFunc=DiffHarmonic<T>;
            BFunc=BothHarmonic<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case LJ612:
            EFunc=FuncLJ612<T>;
            GFunc=DiffLJ612<T>;
            BFunc=BothLJ612<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case LJ612Cut:
            EFunc=FuncLJ612Cut<T>;
            GFunc=DiffLJ612Cut<T>;
            BFunc=BothLJ612Cut<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case LJ1012:
            EFunc=FuncLJ1012<T>;
            GFunc=DiffLJ1012<T>;
            BFunc=BothLJ1012<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case LJ1012Cut:
            EFunc=FuncLJ1012Cut<T>;
            GFunc=DiffLJ1012Cut<T>;
            BFunc=BothLJ1012Cut<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case Core12:
            EFunc=FuncCore12<T>;
            GFunc=DiffCore12<T>;
            BFunc=BothCore12<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case CoreLJ612:
            EFunc=FuncCoreLJ612<T>;
            GFunc=DiffCoreLJ612<T>;
            BFunc=BothCoreLJ612<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case Coulomb:
            EFunc=FuncCoulomb<T>;
            GFunc=DiffCoulomb<T>;
            BFunc=BothCoulomb<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case DistCoulomb:
            EFunc=FuncDistCoulomb<T>;
            GFunc=DiffDistCoulomb<T>;
            BFunc=BothDistCoulomb<T>;
            EMethod=EMethodPairwise<GeomType,T>;
            GMethod=GMethodPairwise<GeomType,T>;
            BMethod=BMethodPairwise<GeomType,T>;
            break;
          case AngleHarmonic:
            EFunc=FuncAngleHarmonic<T>;
            GFunc=DiffAngleHarmonic<T>;
            BFunc=BothAngleHarmonic<T>;
            EMethod=EMethodAngle<GeomType,T>;
            GMethod=GMethodAngle<GeomType,T>;
            BMethod=BMethodAngle<GeomType,T>;
            break;
          case DihedralPeriodic:
            break;
          default:
            fprintf(stderr,"Unknown Interaction Func Name!\n");
        }
      }

      void Energy(const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
                  const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,
                  const GeomType& Geo, T& E) const {
        assert(EMethod!=NULL);
        EMethod(X,ID,P,Buf,Geo,E,EFunc);
      }
      void Gradient(const Array1D<Array1D<T> >& X,
                    const Array1D<unsigned int>& ID,
                    const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,
                    const GeomType& Geo, Array1D<Array1D<T> >& Grad) const {
        assert(GMethod!=NULL);
        GMethod(X,ID,P,Buf,Geo,Grad,GFunc);
      }
      void Both(const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
                const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,
                const GeomType& Geo, T& E,Array1D<Array1D<T> >& Grad) const {
        assert(BMethod!=NULL);
        BMethod(X,ID,P,Buf,Geo,E,Grad,BFunc);
      }

    private:

      InteractionFunc(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#if defined(_FUNC_DCL)||defined(_METHOD_DCL)
#undef _FUNC_DCL
#undef _METHOD_DCL
#endif

namespace mysimulator {

  template <typename GT,typename T>
  void Clear(InteractionFunc<GT,T>& F) {
    F.tag=UnknownInteactionFunc;
    F.EFunc=NULL; F.GFunc=NULL; F.BFunc=NULL; F.EMethod=NULL; F.GMethod=NULL;
    F.BMethod=NULL;
  }

}
#endif

