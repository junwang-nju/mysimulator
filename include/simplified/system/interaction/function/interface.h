
#ifndef _System_Interaction_Function_Interface_H_
#define _System_Interaction_Function_Interface_H_

#include "system/vec-type-selector.h"
#include "system/interaction/name.h"
#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "array-2d/interface.h"

#include "system/interaction/function/pairwise/_E.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM>
  class InteractionFunction {

    public:

      typedef InteractionFunction<GT,DIM>   Type;
      static const ArrayKernelName _VForm = __system_vec_type<DIM>::NAME;
      typedef Array2D<Float,ArrayKernelName::SSE,_VForm>  FVType;
      typedef Array2D<Double,ArrayKernelName::SSE,_VForm> DVType;

      InteractionName _tag;
      Array<Float>  _pre;
      Array<Float>  _post;
      FVType  _vec;
      Array<Type*>  _neighbor;  // cannot be copied
      InteractionFuncDataState _status;

    private:

      typedef float (*_distance_sq_func)(Array<Float>&, Array<Float> const&,
                                         Array<Float> const&, GT const&);
      typedef void (*_pre_post_func)(Array<Float> const&,Array<Float>&,
                                     const InteractionParameter*);
      typedef void (*_kernel_single_func)(Array<Float> const&,
                    const InteractionParameter*,float*);
      typedef void (*_kernel_both_func)(Array<Float> const&,
                    const InteractionParameter*,float*,float*);

      void (*_allocate)(Array<Float>&,Array<Float>&,FVType&,unsigned int);
      _distance_sq_func _distance_sq;
      _pre_post_func    _pre_2_post_for_e;
      _pre_post_func    _pre_2_post_for_g;
      _pre_post_func    _pre_2_post_for_eg;
      _kernel_single_func   _efunc;
      _kernel_single_func   _gfunc;
      _kernel_both_func     _egfunc;
      void (*_E)(FVType const&,Array<UInt> const&,Array<Float>&,Array<Float>&,
                 FVType&, Array<Type*> const&,InteractionFuncDataState,
                 const InteractionParameter*,GT const&,double&,
                 _distance_sq_func,_pre_post_func,_kernel_single_func);
      void (*_G)(FVType const&,Array<UInt> const&,Array<Float>&,Array<Float>&,
                 FVType&,Array<Type*> const&,InteractionFuncDataState,
                 const InteractionParameter*,GT const&,DVType&,
                 _distance_sq_func,_pre_post_func,_kernel_single_func);
      void (*_EG)(FVType const&,Array<UInt> const&,Array<Float>&,Array<Float>&,
                  FVType&,Array<Type*> const&,InteractionFuncDataState,
                  const InteractionParameter*,GT const&,double&,DVType&,
                 _distance_sq_func,_pre_post_func,_kernel_both_func);

    public:

      InteractionFunction()
        : _tag(InteractionName::Unknown), _pre(), _post(), _vec(), _neighbor(),
          _status(InteractionFuncDataState::NotReady),
          _allocate(nullptr), _distance_sq(nullptr),
          _pre_2_post_for_e(nullptr),_pre_2_post_for_g(nullptr),
          _pre_2_post_for_eg(nullptr), _efunc(nullptr),_gfunc(nullptr),
          _egfunc(nullptr),_E(nullptr), _G(nullptr),_EG(nullptr) {}
      InteractionFunction(const Type& F) : InteractionFunction() {
        imprint(F); operator=(F);
      }
      InteractionFunction(Type&& F) : InteractionFunction() { swap(F); }
      ~InteractionFunction() { reset(); }

      operator bool() const {
        return _tag != InteractionName::Unknown &&
               (bool)_pre && (bool)_post && (bool)_vec &&
               _allocate!=nullptr && _distance_sq!=nullptr &&
               _pre_2_post_for_e!=nullptr && _pre_2_post_for_g!=nullptr &&
               _pre_2_post_for_eg!=nullptr && _efunc!=nullptr &&
               _gfunc!=nullptr && _egfunc!=nullptr && _E!=nullptr &&
               _G!=nullptr && _EG!=nullptr;
      }
      InteractionName Name() const { return _tag; }
      void reset() {
        _status = InteractionFuncDataState::NotReady;
        _neighbor.reset();
        _vec.reset();
        _post.reset();
        _pre.reset();
        _tag = InteractionName::Unknown;
        _allocate = nullptr;
        _distance_sq = nullptr;
        _pre_2_post_for_e   = nullptr;
        _pre_2_post_for_g   = nullptr;
        _pre_2_post_for_eg  = nullptr;
        _efunc    = nullptr;
        _gfunc    = nullptr;
        _egfunc   = nullptr;
        _E    = nullptr;
        _G    = nullptr;
        _EG   = nullptr;
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

      void allocate(InteractionName tag) {
        assert(tag!=InteractionName::Unknown);
        reset();
        _tag=tag;
        switch(_tag) {  // not implemented
          case InteractionName::PairHarmonic:
            //_allocate=_pair_harmonic_allocate<DIM>; break;
          default:
            fprintf(stderr,"No Implemented!\n");
        }
        if(_allocate!=nullptr) _allocate(_pre,_post,_vec,DIM);
      }
      void imprint(const Type& F) { allocate(F.Name()); }
      void swap(Type& F) {
        std::swap(_tag,F._tag);
        std::swap(_pre,F._pre);
        std::swap(_post,F._post);
        std::swap(_vec,F._vec);
        std::swap(_neighbor,F._neighbor);
        std::swap(_status,F._status);
      }

      void E(FVType const& X,Array<UInt> const& ID,
             const InteractionParameter* P, GT const& Geo, double& Energy) {
        assert(_E!=nullptr);
        _E(X,ID,_pre,_post,_vec,_neighbor,_status,P,Geo,Energy,
           _distance_sq,_pre_2_post_for_e,_efunc);
      }

      void G(FVType const& X,Array<UInt> const ID,
             const InteractionParameter* P, GT const& Geo, DVType& Gradient) {
        assert(_G!=nullptr);
        _G(X,ID,_pre,_post,_vec,_neighbor,_status,P,Geo,Gradient,
           _distance_sq,_pre_2_post_for_g,_gfunc);
      }
      void EG(FVType const& X, Array<UInt> const& ID,
              const InteractionParameter* P, GT const& Geo, double& Energy,
              DVType& Gradient) {
        assert(_EG!=nullptr);
        _EG(X,ID,_pre,_post,_vec,_neighbor,_status,P,Geo,Gradient,
            _distance_sq,_pre_2_post_for_eg,_egfunc);
      }

  };

  template <typename GT,unsigned int DIM>
  const ArrayKernelName InteractionFunction<GT,DIM>::_VForm;

}

#endif

