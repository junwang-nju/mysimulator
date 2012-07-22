
#ifndef _Interaction_Func_H_
#define _Interaction_Func_H_

#include "array2d-numeric/interface.h"
#include "unique/64bit/interface.h"
#include "interaction-func/name.h"
#include "interaction-parameter/interface.h"

namespace mysimulator {

  template <typename T> class InteractionParameter;

  template <typename T,typename GT> class InteractionFunc;
  template <typename T,typename GT> void Clear(InteractionFunc<T,GT>&);
  template <typename T,typename GT> class InteractionFuncAngle;
  template <typename T,typename GT> class InteractionFuncDihedral;

  template <typename T,typename GeomType>
  class InteractionFunc {

    public:

      typedef InteractionFunc<T,GeomType> Type;
      typedef typename IsNumeric<T>::Type NumericCheck;
      friend void Clear<T,GeomType>(InteractionFunc<T,GeomType>&);
      friend class InteractionFuncAngle<T,GeomType>;
      friend class InteractionFuncDihedral<T,GeomType>;

      InteractionFunc() : _tag(UnknownInteractionFunc), _pre(),
                          _post(), _tmvec(), _neighbor(), _update(true) {}
      virtual ~InteractionFunc() { Clear(*this); }

      bool IsValid() const {
        return _pre.IsValid()&&_post.IsValid()&&_tmvec.IsValid()&&
               (_tag!=UnknownInteractionFunc);
      }
      void ClearFlag() { _update=true; }
      InteractionFuncName Name() const { return _tag; }

      template <typename T1,typename GT>
      void Copy(const InteractionFunc<T1,GT>& F) {
        assert(_tag==F._tag);
        _pre.Copy(F._pre);
        _post.Copy(F._post);
        _tmvec.Copy(F._tmvec);
        _update=F._update;
      }

      virtual void SetNeighbor(InteractionFunc<T,GeomType>* PF1=NULL,...) {
        fprintf(stderr,"No Neighbors Available!\n");
      }
      void ClearNeighbor() { Clear(_neighbor); }
      virtual
      void Allocate(unsigned int)=0;
      virtual
      void EMethod(const ArrayNumeric<ArrayNumeric<T> >&,
                   const Array<unsigned int>&,const InteractionParameter<T>*,
                   const GeomType&,T&)=0;
      virtual
      void GMethod(const ArrayNumeric<ArrayNumeric<T> >&,
          const Array<unsigned int>&,const InteractionParameter<T>*,
                   const GeomType&,ArrayNumeric<ArrayNumeric<T> >&)=0;
      virtual
      void BMethod(const ArrayNumeric<ArrayNumeric<T> >&,
          const Array<unsigned int>&,const InteractionParameter<T>*,
                   const GeomType&,T&,ArrayNumeric<ArrayNumeric<T> >&)=0;

    protected:

      InteractionFuncName   _tag;
      ArrayNumeric<T>       _pre;
      ArrayNumeric<T>       _post;
      Array2DNumeric<T>     _tmvec;
      Array<Type*>          _neighbor;
      bool                  _update;

    private:

      InteractionFunc(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFunc<T,GT>& F) {
    F._update=true;
    Clear(F._neighbor);
    Clear(F._tmvec);
    Clear(F._post);
    Clear(F._pre);
    F._tag=UnknownInteractionFunc;
  }

  template <typename T1,typename T2,typename GT1,typename GT2>
  void _Copy(InteractionFunc<T1,GT1>& F,const InteractionFunc<T2,GT2>& BF) {
    F.Copy(BF);
  }

}

#include "interaction-func/pairwise/core12/interface.h"
#include "interaction-func/pairwise/corelj612/interface.h"
#include "interaction-func/pairwise/coulomb/interface.h"
#include "interaction-func/pairwise/dist-coulomb/interface.h"
#include "interaction-func/pairwise/harmonic/interface.h"
#include "interaction-func/pairwise/lj1012/interface.h"
#include "interaction-func/pairwise/lj1012cut/interface.h"
#include "interaction-func/pairwise/lj612/interface.h"
#include "interaction-func/pairwise/lj612cut/interface.h"
#include "interaction-func/wall/harmonic/interface.h"
#include "interaction-func/wall/core12/interface.h"
#include "interaction-func/angle/harmonic/interface.h"
#include "interaction-func/dihedral/periodic/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  void Introduce(InteractionFunc<T,GT>*& P, const InteractionFuncName& FN,
                 unsigned int dim) {
    if(P!=NULL) { delete P; P=NULL; }
    switch(FN) {
      case Harmonic:
        P=new InteractionFuncPairwiseHarmonic<T,GT>;  break;
      case Core12:
        P=new InteractionFuncPairwiseCore12<T,GT>;  break;
      case CoreLJ612:
        P=new InteractionFuncPairwiseCoreLJ612<T,GT>; break;
      case Coulomb:
        P=new InteractionFuncPairwiseCoulomb<T,GT>; break;
      case DistDielCoulomb:
        P=new InteractionFuncPairwiseDistDielCoulomb<T,GT>; break;
      case LJ1012:
        P=new InteractionFuncPairwiseLJ1012<T,GT>;  break;
      case LJ1012Cut:
        P=new InteractionFuncPairwiseLJ1012Cut<T,GT>; break;
      case LJ612:
        P=new InteractionFuncPairwiseLJ612<T,GT>; break;
      case LJ612Cut:
        P=new InteractionFuncPairwiseLJ612Cut<T,GT>;  break;
      case WallHarmonic:
        P=new InteractionFuncWallHarmonic<T,GT>;  break;
      case WallCore12:
        P=new InteractionFuncWallCore12<T,GT>;  break;
      case AngleHarmonic:
        P=new InteractionFuncAngleHarmonic<T,GT>; break;
      case DihedralPeriodic:
      case DihedralPeriodic2P:
        P=new InteractionFuncDihedralPeriodic<T,GT>;  break;
      case UnknownInteractionFunc:
      default:
        fprintf(stderr,"Unknown Interaction!\n");
    }
    if(P!=NULL) P->Allocate(dim);
  }

}

#endif

