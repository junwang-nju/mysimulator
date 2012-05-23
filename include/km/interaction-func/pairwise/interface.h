
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
      ~InteractionFuncPairwise() { Clear(*this); }

      virtual
      void EMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const Array<Unique64Bit>& P,const GeomType& Geo,
                   T& Energy) {
        if(this->_update) {
          unsigned int I=ID[0], J=ID[1];
          this->pre[PairwiseDistanceSQ]=
            DistanceSQ(this->_tmvec[PairwiseBondVecIJ],X[I],X[J],Geo);
          Pre2Post4E(P);
        }
        T ee;
        EFunc(this->_post,P,&ee);
        Energy+=ee;
      }
      virtual
      void GMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const Array<Unique64Bit>& P,const GeomType& Geo,
                   ArrayNumeric<ArrayNumeric<T> >& Grad) {
        unsigned int I=ID[0], J=ID[1];
        if(this->_update) {
          this->_pre[PairwiseDistanceSQ]=
            DistanceSQ(this->_tmvec[PairwiseBondVecIJ],X[I],X[J],Geo);
          Pre2Post4G(P);
        }
        T ef;
        GFunc(this->_post,P,&ef);
        this->_tmvec[PairwiseScaledBondVecIJ].Copy(
            this->tmvec[PairwiseBondVecIJ]);
        this->_tmvec[PairwiseScaledBondVecIJ].Scale(ef);
        Grad[I].Shift(this->_tmvec[PairwiseScaledBondVecIJ]);
        Grad[J].NegShift(this->_tmvec[PairwiseScaledBondVecIJ]);
      }
      virtual
      void BMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const Array<Unique64Bit>& P,const GeomType& Geo,
                   T& Energy,ArrayNumeric<ArrayNumeric<T> >& Grad) {
        unsigned int I=ID[0], J=ID[1];
        if(this->_update) {
          this->_pre[PairwiseDistanceSQ]=
            DistanceSQ(this->_tmvec[PairwiseBondVecIJ],X[I],X[J],Geo);
          Pre2Post4B(P);
        }
        T ee,ef;
        BFunc(this->_post,P,ee,ef);
        Energy+=ee;
        this->_tmvec[PairwiseScaledBondVecIJ].Copy(
            this->_tmvec[PairwiseBondVecIJ]);
        this->_tmvec[PairwiseScaledBondVecIJ].Scale(ef);
        Grad[I].Shift(this->_tmvec[PairwiseScaledBondVecIJ]);
        Grad[J].NegShift(this->_tmvec[PairwiseScaledBondVecIJ]);
      }

    protected:

      virtual
      void EFunc(const ArrayNumeric<T>&,const Array<Unique64Bit>&,T*)=0;
      virtual
      void GFunc(const ArrayNumeric<T>&,const Array<Unique64Bit>&,T*)=0;
      virtual
      void BFunc(const ArrayNumeric<T>&,const Array<Unique64Bit>&,T*,T*)=0;

      virtual void Pre2Post4E(const Array<Unique64Bit>&)=0;
      virtual void Pre2Post4G(const Array<Unique64Bit>&)=0;
      virtual void Pre2Post4B(const Array<Unique64Bit>&)=0;

    private:

      InteractionFuncPairwise(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncPairwise<T,GT>& F) {
    typedef typename InteractionFuncPairwise<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

}

#endif

