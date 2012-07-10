
#ifndef _Interaction_Func_Angle_Interface_H_
#define _Interaction_Func_Angle_Interface_H_

#include "interaction-func/interface.h"
#include "distance/calc.h"
#include "interaction-func/angle/pre-name.h"
#include "interaction-func/angle/vec-name.h"
#include "interaction-func/angle/neighbor-name.h"
#include "interaction-func/angle/post-name.h"
#include "interaction-func/pairwise/pre-name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncAngle : public InteractionFunc<T,GeomType> {

    public:

      typedef InteractionFuncAngle<T,GeomType> Type;
      typedef InteractionFunc<T,GeomType>   ParentType;

      InteractionFuncAngle() : ParentType() {}
      virtual ~InteractionFuncAngle() { Clear(*this); }

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
          if(this->_neighbor.IsValid())   GetPre4E();
          else {
            unsigned int I=ID[0], J=ID[1], K=ID[2];
            this->_pre[AngleEdgeASQ]=
              DistanceSQ(this->_tmvec[AngleBondVecIJ],X[I],X[J],Geo);
            this->_pre[AngleEdgeBSQ]=
              DistanceSQ(this->_tmvec[AngleBondVecKJ],X[K],X[J],Geo);
          }
          this->_pre[AngleDotAB]=
            Dot(this->_tmvec[AngleBondVecIJ],this->_tmvec[AngleBondVecKJ]);
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
        unsigned int I=ID[0], J=ID[1], K=ID[2];
        if(this->_update) {
          DisplacementCalc(this->_tmvec[AngleBondVecIJ],X[I],X[J],Geo);
          DisplacementCalc(this->_tmvec[AngleBondVecKJ],X[K],X[J],Geo);
          if(this->_neighbor.IsValid())   GetPre4G();
          else {
            this->_pre[AngleEdgeASQ]=this->_tmvec[AngleBondVecIJ].NormSQ();
            this->_pre[AngleEdgeBSQ]=this->_tmvec[AngleBondvecKJ].NormSQ();
          }
          this->_pre[AngleDotAB]=
            Dot(this->_tmvec[AngleBondVecIJ],this->_tmvec[AngleBondVecKJ]);
          Pre2Post4G(P);
          this->_tmvec[AngleNormVecI].Copy(this->_tmvec[AngleBondVecKJ]);
          this->_tmvec[AngleNormVecI].Scale(this->_post[AngleIvRabSin]);
          this->_tmvec[AngleNormVecI].Shift(-this->_post[AngleIvRaSQCtg],
                                            this->_tmvec[AngleBondVecIJ]);
          this->_tmvec[AngleNormVecK].Copy(this->_tmvec[AngleBondVecIJ]);
          this->_tmvec[AngleNormVecK].Scale(this->_post[AngleIvRabSin]);
          this->_tmvec[AngleNormVecK].Shift(-this->_post[AngleIvRbSQCtg],
                                            this->tmvec[AngleBondVecKJ]);
        }
        T ef;
        GFunc(P,&ef);
        this->_tmvec[AngleScaledNormVecI].Copy(this->_tmvec[AngleNormVecI]);
        this->_tmvec[AngleScaledNormVecI].Scale(ef);
        this->_tmvec[AngleScaledNormVecK].Copy(this->_tmvec[AngleNormVecK]);
        this->_tmvec[AngleScaledNormVecK].Scale(ef);
        Grad[I].Shift(this->_tmvec[AngleScaledNormVecI]);
        Grad[J].NegShift(this->_tmvec[AngleScaledNormVecI]);
        Grad[K].Shift(this->_tmvec[AngleScaledNormVecK]);
        Grad[J].NegShift(this->_tmvec[AngleScaledNormVecK]);
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
        unsigned int I=ID[0], J=ID[1], K=ID[2];
        if(this->_update) {
          DisplacementCalc(this->_tmvec[AngleBondVecIJ],X[I],X[J],Geo);
          DisplacementCalc(this->_tmvec[AngleBondVecKJ],X[K],X[J],Geo);
          if(this->_neighbor.IsValid())   GetPre4B();
          else {
            this->_pre[AngleEdgeASQ]=this->_tmvec[AngleBondVecIJ].NormSQ();
            this->_pre[AngleEdgeBSQ]=this->_tmvec[AngleBondvecKJ].NormSQ();
          }
          this->_pre[AngleDotAB]=
            Dot(this->_tmvec[AngleBondVecIJ],this->_tmvec[AngleBondVecKJ]);
          Pre2Post4B(P);
          this->_tmvec[AngleNormVecI].Copy(this->_tmvec[AngleBondVecKJ]);
          this->_tmvec[AngleNormVecI].Scale(this->_post[AngleIvRabSin]);
          this->_tmvec[AngleNormVecI].Shift(-this->_post[AngleIvRaSQCtg],
                                            this->_tmvec[AngleBondVecIJ]);
          this->_tmvec[AngleNormVecK].Copy(this->_tmvec[AngleBondVecIJ]);
          this->_tmvec[AngleNormVecK].Scale(this->_post[AngleIvRabSin]);
          this->_tmvec[AngleNormVecK].Shift(-this->_post[AngleIvRbSQCtg],
                                            this->tmvec[AngleBondVecKJ]);
        }
        T ee,ef;
        BFunc(P,&ee,&ef);
        Energy+=ee;
        this->_tmvec[AngleScaledNormVecI].Copy(this->_tmvec[AngleNormVecI]);
        this->_tmvec[AngleScaledNormVecI].Scale(ef);
        this->_tmvec[AngleScaledNormVecK].Copy(this->_tmvec[AngleNormVecK]);
        this->_tmvec[AngleScaledNormVecK].Scale(ef);
        Grad[I].Shift(this->_tmvec[AngleScaledNormVecI]);
        Grad[J].NegShift(this->_tmvec[AngleScaledNormVecI]);
        Grad[K].Shift(this->_tmvec[AngleScaledNormVecK]);
        Grad[J].NegShift(this->_tmvec[AngleScaledNormVecK]);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>*,T*) = 0;
      virtual void GFunc(const InteractionParameter<T>*,T*) = 0;
      virtual void BFunc(const InteractionParameter<T>*,T*,T*) = 0;

      virtual void Pre2Post4E(const InteractionParameter<T>*) {
        assert(this->IsValid());
        this->_post[AngleCosine]=
          this->pre[AngleDotAB]/__SqRoot(this->_pre[AngleEdgeASQ]*
                                         this->_pre[AngleEdgeBSQ]);
        this->_update=true;
      }
      virtual void Pre2Post4G(const InteractionParameter<T>*) {
        assert(this->IsValid());
        T tmda=1./this->_pre[AngleEdgeASQ];
        T tmdb=1./this->_pre[AngleEdgeBSQ];
        T tmd=__SqRoot(tmda*tmdb);
        T tmd1=tmd*this->_pre[AngleDotAB];
        T tmd2=1./__SqRoot(1-tmd1*tmd1);
        T tmd3=tmd1*tmd2;
        this->_post[AngleCosine]=tmd1;
        this->_post[AngleIvRabSin]=tmd*tmd2;
        this->_post[AngleIvRaSQCtg]=tmd3*tmda;
        this->_post[AngleIvRbSQCtg]=tmd3*tmdb;
        this->_update=false;
      }
      virtual void Pre2Post4B(const InteractionParameter<T>* P) {
        Pre2Post4G(P);
      }

    private:

      InteractionFuncAngle(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      void GetPre4E() {
        assert(this->_neighbor.IsValid());
        InteractionFunc<T,GeomType>* P;
        P=this->_neighbor[AngleNeighbor4EdgeA];
        assert(P!=NULL);
        this->_pre[AngleEdgeASQ]=P->_pre[PairwiseDistanceSQ];
        P=this->_neighbor[AngleNeighbor4EdgeB];
        assert(P!=NULL);
        this->_pre[AngleEdgeBSQ]=P->_pre[PairwiseDistanceSQ];
      }
      void GetPre4G() { GetPre4E(); }
      void GetPre4B() { GetPre4E(); }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncAngle<T,GT>& F) {
    typedef typename InteractionFuncAngle<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncAngle<T1,GT1>& F,
             const InteractionFuncAngle<T2,GT2>& BF) {
    typedef typename InteractionFuncAngle<T1,GT1>::ParentType PType1;
    typedef typename InteractionFuncAngle<T2,GT2>::ParentType PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

