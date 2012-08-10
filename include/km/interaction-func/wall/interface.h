
#ifndef _Interaction_Func_Wall_Interface_H_
#define _Interaction_Func_Wall_Interface_H_

#include "interaction-func/interface.h"
#include "distance/calc.h"
#include "interaction-func/wall/pre-name.h"
#include "interaction-func/wall/vec-name.h"

namespace mysimulator {

  template <typename T,typename GeomType,
            template<typename,typename> class PairFunc>
  class InteractionFuncWall : public PairFunc<T,GeomType> {

    public:

      typedef InteractionFuncWall<T,GeomType,PairFunc>     Type;
      typedef PairFunc<T,GeomType>   ParentType;

      InteractionFuncWall() : ParentType() {}
      virtual ~InteractionFuncWall() { Clear(*this); }

      virtual
      void EMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const InteractionParameter<T>* P,const GeomType& Geo,
                   T& Energy) {
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        if((this->_update&EFuncUpdateOK)==EFuncUpdateOK) {
          unsigned int I=ID[0], J=ID[1];
          this->_pre[WallDistance]=Distance2Wall(X[I],X[J],Geo);
          this->Pre2Post4E(P);
        }
        T ee;
        this->EFunc(P,&ee);
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
        if((this->_update&GFuncUpdateOK)==GFuncUpdateOK) {
          this->_pre[WallDistance]=Distance2Wall(X[I],X[J],Geo);
          this->Pre2Post4G(P);
        }
        T ef;
        this->GFunc(P,&ef);
        unsigned int dim=X[J].Size();
        this->_tmvec[WallScaledNormVec].CopyN(X[I],dim);
        this->_tmvec[WallScaledNormVec].Scale(ef);
        Grad[I][dim]=-ef;
        Grad[J].Shift(this->_tmvec[WallScaledNormVec]);
      }
      virtual
      void BMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,
                   const InteractionParameter<T>* P,const GeomType& Geo,
                   T& Energy, ArrayNumeric<ArrayNumeric<T> >& Grad) {
        assert(X.IsValid());
        assert(ID.IsValid());
        assert(P!=NULL);
        assert(Geo.IsValid());
        assert(Grad.IsValid());
        unsigned int I=ID[0], J=ID[1];
        if((this->_update&EGFuncUpdateOK)==EGFuncUpdateOK) {
          this->_pre[WallDistance]=Distance2Wall(X[I],X[J],Geo);
          this->Pre2Post4B(P);
        }
        T ee,ef;
        this->BFunc(P,&ee,&ef);
        Energy+=ee;
        unsigned int dim=X[J].Size();
        this->_tmvec[WallScaledNormVec].CopyN(X[I],dim);
        this->_tmvec[WallScaledNormVec].Scale(ef);
        Grad[I][dim]=-ef;
        Grad[J].Shift(this->_tmvec[WallScaledNormVec]);
      }

    private:

      InteractionFuncWall(const Type&) {}
      Type& operator=(const Type&) {}

  };

  template <typename T,typename GT,template<typename,typename> class PF>
  void Clear(InteractionFuncWall<T,GT,PF>& F) {
    typedef typename InteractionFuncWall<T,GT,PF>::ParentType  PType;
    Clear(static_cast<PType&>(F));
  }

}

#endif

