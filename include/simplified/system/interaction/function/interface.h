
#ifndef _System_Interaction_Function_Interface_H_
#define _System_Interaction_Function_Interface_H_

#include "system/vec-type-selector.h"
#include "system/interaction/name.h"
#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM>
  class InteractionFunction {

    public:

      typedef InteractionFunction<GT,DIM>   Type;
      typedef Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>
              FXType;
      typedef Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>
              DXType;

    private:

      InteractionName _tag;
      Array<Double> _pre;
      Array<Double> _post;
      DXType _vec;
      Array<Type*> _neighbor;
      InteractionFuncDataState _status;

    public:

      InteractionFunction() : _tag(InteractionName::Unknown), _pre(), _post(),
                              _vec(), _neighbor(),
                              _status(InteractionFuncDataState::NotReady) {}
      InteractionFunction(const Type& F)
        : _tag(F._tag), _pre(F._pre), _post(F._post), _vec(F._vec),
          _neighbor(), _status(InteractionFuncDataState::NotReady) {}
      InteractionFunction(Type&& F) : InteractionFunction() { swap(F); }
      virtual ~InteractionFunction() { reset(); }

      operator bool() const {
        return _tag != InteractionName::Unknown && (bool)_pre &&
               (bool)_post && (bool)_vec;
      }
      InteractionName Name() const { return _tag; }
      void reset() {
        _status = InteractionFuncDataState::NotReady;
        _neighbor.reset();
        _vec.reset();
        _post.reset();
        _pre.reset();
        _tag = InteractionName::Unknown;
      }

      Type& operator=(const Type& F) {
        assert((bool)(*this));
        assert((bool)F);
        assert(Name()==F.Name());
        _pre = F._pre;
        _post = F._post;
        _vec = F._vec;
        _status = InteractionFuncDataState::NotReady;
        return *this;
      }

      void swap(Type& F) {
        std::swap(_tag,F._tag);
        std::swap(_pre,F._pre);
        std::swap(_post,F._post);
        std::swap(_vec,F._vec);
        std::swap(_neighbor,F._neighbor);
        std::swap(_status,F._status);
      }

      virtual void SetNeighbors(Type* NB=nullptr,...) { assert(NB!=nullptr); }
      virtual void allocate() = 0;
      virtual void E(FXType const&, Array<UInt> const&,
                     const InteractionParameter*, GT const&, double&) =0;
      virtual void G(FXType const&, Array<UInt> const&,
                     const InteractionParameter*, GT const&, DXType&) = 0;
      virtual void EG(FXType const&, Array<UInt> const&,
                      const InteractionParameter*, GT const&,
                      double&, DXType&) = 0;

  };

}

namespace std {

  template <typename GT,unsigned int DIM>
  void swap(mysimulator::InteractionFunction<GT,DIM>& F1,
            mysimulator::InteractionFunction<GT,DIM>& F2) {
    F1.swap(F2);
  }

}

#endif

