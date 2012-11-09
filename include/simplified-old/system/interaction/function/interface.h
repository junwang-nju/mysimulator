
#ifndef _System_Interaction_Function_Interface_H_
#define _System_Interaction_Function_Interface_H_

#include "system/interaction/name.h"
#include "system/spatial-field/interface.h"
#include "system/hessian/interface.h"
#include "system/interaction/parameter/interface.h"

namespace mysimulator {

  class FunctionDataState {
    public:
      static const unsigned int NotReady;
      static const unsigned int EDataOK;
      static const unsigned int GDataOK;
      static const unsigned int HDataOK;
      static const unsigned int EGDataOK;
  };

  const unsigned int FunctionDataState::NotReady   = 0;
  const unsigned int FunctionDataState::EDataOK    = 1;
  const unsigned int FunctionDataState::GDataOK    = 2;
  const unsigned int FunctionDataState::HDataOK    = 4;
  const unsigned int FunctionDataState::EGDataOK   =
      FunctionDataState::EDataOK + FunctionDataState::GDataOK;

  template <typename T,typename BdType>
  class InteractionFunction {
    public:
      typedef InteractionFunction<T,BdType> Type;
      InteractionFunction() = delete;
      InteractionFunction(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~InteractionFunction() {}
  };

  template <typename T,typename BdType>
  class InteractionFunction<Intrinsic<T>,BdType> {

    public:

      static_assert(__float_point_flag<T>::FG,
                    "This Function Works for Floating-point case!\n");

      typedef InteractionFunction<Intrinsic<T>,BdType>   Type;

    private:

      InteractionName _tag;
      unsigned int dim;
      Array<Intrinsic<T>>  _pre;
      Array<Intrinsic<T>>  _post;
      SpatialField<Intrinsic<T>>  _vec;
      Array<Type*>  _neighbor;
      unsigned int  _status;

    public:

      InteractionFunction() : _tag(InteractionName::UnknownInteraction),
                              dim(0), _pre(), _post(), _vec(), _neighbor(),
                              _status(FunctionDataState::NotReady) {}
      InteractionFunction(const Type& F) : InteractionFunction() {
        allocate(F.Dimension());
        operator=(F);
      }
      InteractionFunction(Type&& F) : InteractionFunction() { swap(F); }
      virtual ~InteractionFunction() { reset(); }

      operator bool() const {
        return _tag!=InteractionName::UnknownInteraction && (bool)_pre &&
               (bool)_post && (bool)_vec && dim>0;
      }
      InteractionName Name() const { return _tag; }
      unsigned int Dimension() const { return dim; }

      Type& operator=(const Type& F) {
        assert((bool)(*this));
        assert((bool)F);
        assert(Name()==F.Name());
        assert(Dimension()==F.Dimension());
        _pre=F._pre;
        _post=F._post;
        _vec=F._vec;
        _status=F._status;
        return *this;
      }

      void reset() {
        _tag=InteractionName::UnknownInteraction;
        _neighbor.reset();
        _vec.reset();
        _post.reset();
        _pre.reset();
        dim=0;
        _status=FunctionDataState::NotReady;
      }
      void swap(Type& F) {
        std::swap(_tag,F._tag);
        std::swap(dim,F.dim);
        std::swap(_pre,F._pre);
        std::swap(_post,F._post);
        std::swap(_vec,F._vec);
        std::swap(_neighbor,F._neighbor);
        std::swap(_status,F._status);
      }

      virtual
      void SetNeighbors(Type* NB1=nullptr,...) { assert(NB1!=nullptr); }

      virtual
      void allocate(unsigned int DIM) = 0;

      virtual
      void E(SpatialField<Intrinsic<T>> const&, Array<UInt> const&,
             const InteractionParameter<Intrinsic<T>>*, BdType const&, T&) = 0;

      virtual
      void G(SpatialField<Intrinsic<T>> const&, Array<UInt> const&,
             const InteractionParameter<Intrinsic<T>>*, BdType const&,
             SpatialField<Intrinsic<T>>&) = 0;
      virtual
      void EG(SpatialField<Intrinsic<T>> const&, Array<UInt> const&,
              const InteractionParameter<Intrinsic<T>>*, BdType const&,
              T&,SpatialField<Intrinsic<T>>&) = 0;
      virtual
      void H(SpatialField<Intrinsic<T>> const&, Array<UInt> const&,
             const InteractionParameter<Intrinsic<T>>*, BdType const&,
             Hessian<Intrinsic<T>>&) = 0;

  };

}

namespace std {

  template <typename T,typename BT>
  void swap(mysimulator::InteractionFunction<mysimulator::Intrinsic<T>,BT>& F1,
            mysimulator::InteractionFunction<mysimulator::Intrinsic<T>,BT>& F2){
    F1.swap(F2);
  }

}

#endif

