
#ifndef _Interaction_Func_Dihedral_Interface_H_
#define _Interaction_Func_Dihedral_Interface_H_

#include "interaction-func/interface.h"
#include "distance/calc.h"
#include "interaction-func/dihedral/pre-name.h"
#include "interaction-func/dihedral/post-name.h"
#include "interaction-func/dihedral/vec-name.h"
#include "interaction-func/dihedral/neighbor-name.h"
#include "interaction-func/pairwise/pre-name.h"
#include "interaction-func/angle/pre-name.h"
#include "interaction-func/angle/post-name.h"
#include "basic/acos.h"

#ifndef _NAME_
#define _NAME_(U) Dihedral##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _VEC_
#define _VEC_(U)  this->_tmvec[_NAME_(U)]
#else
#error "Duplicate _VEC_"
#endif

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncDihedral : public InteractionFunc<T,GeomType> {

    public:

      typedef InteractionFuncDihedral<T,GeomType>   Type;
      typedef InteractionFunc<T,GeomType> ParentType;

      InteractionFuncDihedral() : ParentType() {}
      virtual ~InteractionFuncDihedral() { Clear(*this); }

      virtual
      void EMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const InteractionParameter<T>* P,const GeomType& Geo,
                   T& Energy) {
        assert(this->IsValid());
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        if(this->_update) {
          unsigned int I=ID[0], J=ID[1], K=ID[2], L=ID[3];
          DisplacementCalc(_VEC_(BondVecJI),X[J],X[I],Geo);
          DisplacementCalc(_VEC_(BondVecKJ),X[K],X[J],Geo);
          DisplacementCalc(_VEC_(BondVecLK),X[L],X[K],Geo);
          Cross(_VEC_(NormVecA), _VEC_(BondVecJI), _VEC_(BondVecKJ));
          Cross(_VEC_(NormVecB), _VEC_(BondVecKJ), _VEC_(BondVecLK));
          Cross(_VEC_(CrossNormVec), _VEC_(NormVecA), _VEC_(NormVecB));
          if(this->_neighbor.IsValid()) GetPre4E();
          else {
            this->_pre[DihedralIvNormASQ]=1./_VEC_(NormVecA).NormSQ();
            this->_pre[DihedralIvNormBSQ]=1./_VEC_(NormVecB).NormSQ();
          }
          this->_pre[DihedralDotNormAB]=_Dot(_VEC_(NormVecA),_VEC_(NormVecB));
          this->_pre[DihedralCrossNormAB]=_Dot(_VEC_(BondVecKJ),
                                               _VEC_(CrossNormVec));
          Pre2Post4E(P);
        }
        T ee;
        EFunc(P,&ee);
        Energy+=ee;
      }

      virtual
      void GMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const InteractionParameter<T>* P,const GeomType& Geo,
                   ArrayNumeric<ArrayNumeric<T> >& Grad) {
        assert(this->IsValid());
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        assert(Grad.IsValid());
        unsigned int I=ID[0], J=ID[1], K=ID[2], L=ID[3];
        if(this->_update) {
          DisplacementCalc(_VEC_(BondVecJI),X[J],X[I],Geo);
          DisplacementCalc(_VEC_(BondVecKJ),X[K],X[J],Geo);
          DisplacementCalc(_VEC_(BondVecLK),X[L],X[K],Geo);
          Cross(_VEC_(NormVecA), _VEC_(BondVecJI), _VEC_(BondVecKJ));
          Cross(_VEC_(NormVecB), _VEC_(BondVecKJ), _VEC_(BondVecLK));
          Cross(_VEC_(CrossNormVec), _VEC_(NormVecA), _VEC_(NormVecB));
          if(this->_neighbor.IsValid()) GetPre4G();
          else {
            this->_pre[DihedralIvNormASQ]=1./_VEC_(NormVecA).NormSQ();
            this->_pre[DihedralIvNormBSQ]=1./_VEC_(NormVecB).NormSQ();
            this->_pre[DihedralAxisSQ]=_VEC_(BondVecKJ).NormSQ();
            this->_pre[DihedralDotBondAB]=_Dot(_VEC_(BondVecJI),
                                               _VEC_(BondVecKJ));
            this->_pre[DihedralDotBondBC]=_Dot(_VEC_(BondVecKJ),
                                               _VEC_(BondVecLK));
          }
          this->_pre[DihedralDotNormAB]=_Dot(_VEC_(NormVecA),_VEC_(NormVecB));
          this->_pre[DihedralCrossNormAB]=_Dot(_VEC_(BondVecKJ),
                                               _VEC_(CrossNormVec));
          Pre2Post4G(P);
        }
        T ef;
        GFunc(P,&ef);
        T efi=ef*this->_post[DihedralFactorI];
        T efj=ef*this->_post[DihedralFactorJ];
        T efk=ef*this->_post[DihedralFactorK];
        T efl=ef*this->_post[DihedralFactorL];
        Grad[I].Shift(efi,_VEC_(NormVecA));
        Grad[L].Shift(efl,_VEC_(NormVecB));
        Grad[J].Shift(-efi-efj,_VEC_(NormVecA));
        Grad[J].Shift(+efk,_VEC_(NormVecB));
        Grad[K].Shift(+efj,_VEC_(NormVecA));
        Grad[K].Shift(-efl-efk,_VEC_(NormVecB));
      }

      virtual
      void BMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const InteractionParameter<T>* P,const GeomType& Geo,
                   T& Energy, ArrayNumeric<ArrayNumeric<T> >& Grad) {
        assert(this->IsValid());
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        assert(Grad.IsValid());
        unsigned int I=ID[0], J=ID[1], K=ID[2], L=ID[3];
        if(this->_update) {
          DisplacementCalc(_VEC_(BondVecJI),X[J],X[I],Geo);
          DisplacementCalc(_VEC_(BondVecKJ),X[K],X[J],Geo);
          DisplacementCalc(_VEC_(BondVecLK),X[L],X[K],Geo);
          Cross(_VEC_(NormVecA), _VEC_(BondVecJI), _VEC_(BondVecKJ));
          Cross(_VEC_(NormVecB), _VEC_(BondVecKJ), _VEC_(BondVecLK));
          Cross(_VEC_(CrossNormVec), _VEC_(NormVecA), _VEC_(NormVecB));
          if(this->_neighbor.IsValid()) GetPre4B();
          else {
            this->_pre[DihedralIvNormASQ]=1./_VEC_(NormVecA).NormSQ();
            this->_pre[DihedralIvNormBSQ]=1./_VEC_(NormVecB).NormSQ();
            this->_pre[DihedralAxisSQ]=_VEC_(BondVecKJ).NormSQ();
            this->_pre[DihedralDotBondAB]=_Dot(_VEC_(BondVecJI),
                                               _VEC_(BondVecKJ));
            this->_pre[DihedralDotBondBC]=_Dot(_VEC_(BondVecKJ),
                                               _VEC_(BondVecLK));
          }
          this->_pre[DihedralDotNormAB]=_Dot(_VEC_(NormVecA),_VEC_(NormVecB));
          this->_pre[DihedralCrossNormAB]=_Dot(_VEC_(BondVecKJ),
                                               _VEC_(CrossNormVec));
          Pre2Post4B(P);
        }
        T ee,ef;
        BFunc(P,&ee,&ef);
        Energy+=ee;
        T efi=ef*this->_post[DihedralFactorI];
        T efj=ef*this->_post[DihedralFactorJ];
        T efk=ef*this->_post[DihedralFactorK];
        T efl=ef*this->_post[DihedralFactorL];
        Grad[I].Shift(efi,_VEC_(NormVecA));
        Grad[L].Shift(efl,_VEC_(NormVecB));
        Grad[J].Shift(-efi-efj,_VEC_(NormVecA));
        Grad[J].Shift(+efk,_VEC_(NormVecB));
        Grad[K].Shift(+efj,_VEC_(NormVecA));
        Grad[K].Shift(-efl-efk,_VEC_(NormVecB));
      }

      virtual void SetNeighbor(InteractionFunc<T,GeomType>* PF1,...) {
        this->_neighbor.Allocate(DihedralNumberNeighbor);
        this->_neighbor[DihedralNeighbor4NormA]=PF1;
        va_list vl;
        va_start(vl,PF1);
        this->_neighbor[DihedralNeighbor4NormB]=va_arg(vl,Type*);
        this->_neighbor[DihedralNeighbor4Axis]=va_arg(vl,Type*);
        this->_neighbor[DihedralNeighbor4DotAB]=va_arg(vl,Type*);
        this->_neighbor[DihedralNeighbor4DotBC]=va_arg(vl,Type*);
        va_end(vl);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>*,T*) = 0;
      virtual void GFunc(const InteractionParameter<T>*,T*) = 0;
      virtual void BFunc(const InteractionParameter<T>*,T*,T*) = 0;

      virtual void Pre2Post4E(const InteractionParameter<T>*) {
        T csDih=this->_pre[DihedralDotNormAB]*
                __SqRoot(this->_pre[DihedralIvNormASQ]*
                         this->_pre[DihedralIvNormBSQ]);
        this->_post[DihedralValue]=_ACos(csDih)*
                                   (this->_pre[DihedralCrossNormAB]>0?1:-1);
        this->_update=true;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>*) {
        T tmda=this->_pre[DihedralIvNormASQ];
        T tmdb=this->_pre[DihedralIvNormBSQ];
        T csDih=this->_pre[DihedralDotNormAB]*__SqRoot(tmda*tmdb);
        this->_post[DihedralValue]=_ACos(csDih)*
                                   (this->_pre[DihedralCrossNormAB]>0?1:-1);
        T tmd1=this->_pre[DihedralAxisSQ];
        T tmd=__SqRoot(tmd1);
        tmd1=tmd/tmd1;
        this->_post[DihedralFactorI]=-tmd*tmda;
        this->_post[DihedralFactorJ]=-this->_pre[DihedralDotBondAB]*tmda*tmd1;
        this->_post[DihedralFactorK]= this->_pre[DihedralDotBondBC]*tmdb*tmd1;
        this->_post[DihedralFactorL]= tmd*tmdb;
        this->_update=false;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4G(P);
      }

    private:

      InteractionFuncDihedral(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      void GetPre4E() {
        assert(this->_neighbor.IsValid());
        InteractionFunc<T,GeomType>* P;
        P=this->_neighbor[DihedralNeighbor4NormA];
        assert(P!=NULL);
        this->_pre[DihedralIvNormASQ]=
          (P->_update?1./_VEC_(NormVecA).NormSQ():
                      P->_post[AngleIvRabSin]*P->_post[AngleIvRabSin]);
        P=this->_neighbor[DihedralNeighbor4NormB];
        assert(P!=NULL);
        this->_pre[DihedralIvNormBSQ]=
          (P->_update?1./_VEC_(NormVecB).NormSQ():
                      P->_post[AngleIvRabSin]*P->_post[AngleIvRabSin]);
      }
      void GetPre4G() {
        GetPre4E();
        InteractionFunc<T,GeomType>* P;
        P=this->_neighbor[DihedralNeighbor4Axis];
        assert(P!=NULL);
        this->_pre[DihedralAxisSQ]=P->_pre[PairwiseDistanceSQ];
        P=this->_neighbor[DihedralNeighbor4DotAB];
        assert(P!=NULL);
        this->_pre[DihedralDotBondAB]=-(P->_pre[AngleDotAB]);
        P=this->_neighbor[DihedralNeighbor4DotBC];
        assert(P!=NULL);
        this->_pre[DihedralDotBondBC]=-(P->_pre[AngleDotAB]);
      }
      void GetPre4B() { GetPre4G(); }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncDihedral<T,GT>& F) {
    typedef typename InteractionFuncDihedral<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncDihedral<T1,GT1>& F,
             const InteractionFuncDihedral<T2,GT2>& BF) {
    typedef typename InteractionFuncDihedral<T1,GT1>::ParentType  PType1;
    typedef typename InteractionFuncDihedral<T2,GT2>::ParentType  PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#ifdef _VEC_
#undef _VEC_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

