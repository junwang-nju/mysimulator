
#ifndef _Interaction_Func_Pairwise_Interface_H_
#define _Interaction_Func_Pairwise_Interface_H_

#include "interaction-func/interface.h"
#include "distance/calc.h"
#include "interaction-func/pairwise/pre-name.h"
#include "interaction-func/pairwise/vec-name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwise : public InteractionFunc<T,GeomType> {

    public:

      typedef InteractionFuncPairwise<T,GeomType> Type;
      typedef InteractionFunc<T,GeomType>   ParentType;

      InteractionFuncPairwise() : ParentType() {}
      virtual ~InteractionFuncPairwise() { Clear(*this); }

      virtual
      void EMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const InteractionParameter<T>* P,const GeomType& Geo,
                   T& Energy) {
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        if(this->_update) {
          unsigned int I=ID[0], J=ID[1];
          this->_pre[PairwiseDistanceSQ]=
            DistanceSQ(this->_tmvec[PairwiseBondVecIJ],X[I],X[J],Geo);
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
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        assert(Grad.IsValid());
        unsigned int I=ID[0], J=ID[1];
        if(this->_update) {
          this->_pre[PairwiseDistanceSQ]=
            DistanceSQ(this->_tmvec[PairwiseBondVecIJ],X[I],X[J],Geo);
          Pre2Post4G(P);
        }
        T ef;
        GFunc(P,&ef);
        this->_tmvec[PairwiseScaledBondVecIJ].Copy(
            this->_tmvec[PairwiseBondVecIJ]);
        this->_tmvec[PairwiseScaledBondVecIJ].Scale(ef);
        Grad[I].Shift(this->_tmvec[PairwiseScaledBondVecIJ]);
        Grad[J].NegShift(this->_tmvec[PairwiseScaledBondVecIJ]);
      }
      virtual
      void BMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const InteractionParameter<T>* P,const GeomType& Geo,
                   T& Energy,ArrayNumeric<ArrayNumeric<T> >& Grad) {
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        assert(Grad.IsValid());
        unsigned int I=ID[0], J=ID[1];
        if(this->_update) {
          this->_pre[PairwiseDistanceSQ]=
            DistanceSQ(this->_tmvec[PairwiseBondVecIJ],X[I],X[J],Geo);
          Pre2Post4B(P);
        }
        T ee,ef;
        BFunc(P,&ee,&ef);
        Energy+=ee;
        this->_tmvec[PairwiseScaledBondVecIJ].Copy(
            this->_tmvec[PairwiseBondVecIJ]);
        this->_tmvec[PairwiseScaledBondVecIJ].Scale(ef);
        Grad[I].Shift(this->_tmvec[PairwiseScaledBondVecIJ]);
        Grad[J].NegShift(this->_tmvec[PairwiseScaledBondVecIJ]);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>*,T*)=0;
      virtual void GFunc(const InteractionParameter<T>*,T*)=0;
      virtual void BFunc(const InteractionParameter<T>*,T*,T*)=0;

      virtual void Pre2Post4E(const InteractionParameter<T>*)=0;
      virtual void Pre2Post4G(const InteractionParameter<T>*)=0;
      virtual void Pre2Post4B(const InteractionParameter<T>*)=0;

    private:

      InteractionFuncPairwise(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwise<T,GT>& F) {
    typedef typename InteractionFuncPairwise<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename T2,typename GT1,typename GT2>
  void _Copy(InteractionFuncPairwise<T1,GT1>& F,
             const InteractionFuncPairwise<T2,GT2>& BF) {
    typedef typename InteractionFuncPairwise<T1,GT1>::ParentType  PType1;
    typedef typename InteractionFuncPairwise<T2,GT2>::ParentType  PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

