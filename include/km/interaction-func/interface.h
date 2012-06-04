
#ifndef _Interaction_Func_H_
#define _Interaction_Func_H_

#include "array/interface.h"
#include "array2d-numeric/interface.h"
#include "unique/64bit/interface.h"
#include "interaction-func/name.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFunc {

    public:

      typedef InteractionFunc<T,GeomType> Type;
      template <typename T1,typename GT>
      friend void Clear(InteractionFunc<T,GT>&);

      InteractionFunc() : _dim(0), _tag(UnknownInteractionFunc), _pre(),
                          _post(), _tmvec(), _neighbor(), _update(true) {}
      ~InteractionFunc() { Clear(*this); }

      bool IsValid() const {
        return (_dim>0)&&_pre.IsValid()&&_post.IsValid()&&_tmvec.IsValid()&&
               (_tag!=UnknownInteractionFunc);
      }

      virtual
      void EMethod(const ArrayNumeric<ArrayNumeric<T> >&,
                   const Array<unsigned int>&,const Array<Unique64Bit>&,
                   const GeomType&,T&)=0;
      virtual
      void GMethod(const ArrayNumeric<ArrayNumeric<T> >&,
                   const Array<unsigned int>&,const Array<Unique64Bit>&,
                   const GeomType&,ArrayNumeric<ArrayNumeric<T> >&)=0;
      virtual
      void BMethod(const ArrayNumeric<ArrayNumeric<T> >&,
                   const Array<unsigned int>&,const Array<Unique64Bit>&,
                   const GeomType&,T&,ArrayNumeric<ArrayNumeric<T> >&)=0;

    protected:

      unsigned int          _dim;
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
    F._dim=0;
  }

}

#endif

