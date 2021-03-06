
#ifndef _System_Interaction_Function_Interface_H_
#define _System_Interaction_Function_Interface_H_

#include "system/vec-type-selector.h"
#include "system/interaction/name.h"
#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "geometry/distance/calc.h"
#include "array-2d/interface.h"

#include "system/interaction/function/pairwise/_E.h"
#include "system/interaction/function/pairwise/_G.h"
#include "system/interaction/function/pairwise/_EG.h"

#include "system/interaction/function/pairwise/harmonic/_allocate.h"
#include "system/interaction/function/pairwise/harmonic/_pre_2_post_for_e.h"
#include "system/interaction/function/pairwise/harmonic/_pre_2_post_for_g.h"
#include "system/interaction/function/pairwise/harmonic/_pre_2_post_for_eg.h"
#include "system/interaction/function/pairwise/harmonic/_e_func.h"
#include "system/interaction/function/pairwise/harmonic/_g_func.h"
#include "system/interaction/function/pairwise/harmonic/_eg_func.h"

#include "system/interaction/function/pairwise/lj612/_allocate.h"
#include "system/interaction/function/pairwise/lj612/_pre_2_post_for_e.h"
#include "system/interaction/function/pairwise/lj612/_pre_2_post_for_g.h"
#include "system/interaction/function/pairwise/lj612/_pre_2_post_for_eg.h"
#include "system/interaction/function/pairwise/lj612/_e_func.h"
#include "system/interaction/function/pairwise/lj612/_g_func.h"
#include "system/interaction/function/pairwise/lj612/_eg_func.h"

#include "system/interaction/function/pairwise/corelj612/_allocate.h"
#include "system/interaction/function/pairwise/corelj612/_pre_2_post_for_e.h"
#include "system/interaction/function/pairwise/corelj612/_pre_2_post_for_g.h"
#include "system/interaction/function/pairwise/corelj612/_pre_2_post_for_eg.h"
#include "system/interaction/function/pairwise/corelj612/_e_func.h"
#include "system/interaction/function/pairwise/corelj612/_g_func.h"
#include "system/interaction/function/pairwise/corelj612/_eg_func.h"

#include "system/interaction/function/pairwise/core12/_allocate.h"
#include "system/interaction/function/pairwise/core12/_pre_2_post_for_e.h"
#include "system/interaction/function/pairwise/core12/_pre_2_post_for_g.h"
#include "system/interaction/function/pairwise/core12/_pre_2_post_for_eg.h"
#include "system/interaction/function/pairwise/core12/_e_func.h"
#include "system/interaction/function/pairwise/core12/_g_func.h"
#include "system/interaction/function/pairwise/core12/_eg_func.h"

#include "system/interaction/function/pairwise/lj1012/_allocate.h"
#include "system/interaction/function/pairwise/lj1012/_pre_2_post_for_e.h"
#include "system/interaction/function/pairwise/lj1012/_pre_2_post_for_g.h"
#include "system/interaction/function/pairwise/lj1012/_pre_2_post_for_eg.h"
#include "system/interaction/function/pairwise/lj1012/_e_func.h"
#include "system/interaction/function/pairwise/lj1012/_g_func.h"
#include "system/interaction/function/pairwise/lj1012/_eg_func.h"

#include "system/interaction/function/pairwise/lj612cut/_allocate.h"
#include "system/interaction/function/pairwise/lj612cut/_pre_2_post_for_e.h"
#include "system/interaction/function/pairwise/lj612cut/_pre_2_post_for_g.h"
#include "system/interaction/function/pairwise/lj612cut/_pre_2_post_for_eg.h"
#include "system/interaction/function/pairwise/lj612cut/_e_func.h"
#include "system/interaction/function/pairwise/lj612cut/_g_func.h"
#include "system/interaction/function/pairwise/lj612cut/_eg_func.h"

#include "system/interaction/function/pairwise/step-continuous/_allocate.h"
#include "system/interaction/function/pairwise/step-continuous/_pre_2_post_for_e.h"
#include "system/interaction/function/pairwise/step-continuous/_pre_2_post_for_g.h"
#include "system/interaction/function/pairwise/step-continuous/_pre_2_post_for_eg.h"
#include "system/interaction/function/pairwise/step-continuous/_e_func.h"
#include "system/interaction/function/pairwise/step-continuous/_g_func.h"
#include "system/interaction/function/pairwise/step-continuous/_eg_func.h"

#include "system/interaction/function/angle/_E.h"
#include "system/interaction/function/angle/_G.h"
#include "system/interaction/function/angle/_EG.h"

#include "system/interaction/function/angle/harmonic/_allocate.h"
#include "system/interaction/function/angle/harmonic/_pre_2_post_for_e.h"
#include "system/interaction/function/angle/harmonic/_pre_2_post_for_g.h"
#include "system/interaction/function/angle/harmonic/_pre_2_post_for_eg.h"
#include "system/interaction/function/angle/harmonic/_e_func.h"
#include "system/interaction/function/angle/harmonic/_g_func.h"
#include "system/interaction/function/angle/harmonic/_eg_func.h"

#include "system/interaction/function/dihedral/_E.h"
#include "system/interaction/function/dihedral/_G.h"
#include "system/interaction/function/dihedral/_EG.h"
#include "system/interaction/function/dihedral/_pre_2_post_for_e.h"
#include "system/interaction/function/dihedral/_pre_2_post_for_g.h"
#include "system/interaction/function/dihedral/_pre_2_post_for_eg.h"

#include "system/interaction/function/dihedral/periodic/_allocate.h"
#include "system/interaction/function/dihedral/periodic/_e_func.h"
#include "system/interaction/function/dihedral/periodic/_g_func.h"
#include "system/interaction/function/dihedral/periodic/_eg_func.h"

#include "system/interaction/function/dihedral/multi-periodic/_allocate.h"
#include "system/interaction/function/dihedral/multi-periodic/_e_func.h"
#include "system/interaction/function/dihedral/multi-periodic/_g_func.h"
#include "system/interaction/function/dihedral/multi-periodic/_eg_func.h"

#include "system/interaction/function/dihedral/multi-periodic-common-phase/_allocate.h"
#include "system/interaction/function/dihedral/multi-periodic-common-phase/_e_func.h"
#include "system/interaction/function/dihedral/multi-periodic-common-phase/_g_func.h"
#include "system/interaction/function/dihedral/multi-periodic-common-phase/_eg_func.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM=GT::Dimension>
  class InteractionFunction {

    public:

      typedef InteractionFunction<GT,DIM>   Type;
      static const ArrayKernelName _VForm = __system_vec_type<DIM>::NAME;
      typedef Array2D<Double,ArrayKernelName::SSE,_VForm> DVType;

      InteractionName _tag;
      Array<Double>  _pre;
      Array<Double>  _post;
      DVType  _vec;
      Array<Type*>  _neighbor;  // cannot be copied
      InteractionFuncDataState _status;

    private:

      typedef double (*_distance_sq_func)(
          Array<Double,_VForm>&,Array<Double,_VForm> const&,
          Array<Double,_VForm> const&, GT const&);
      typedef void (*_displacement_func)(
          Array<Double,_VForm>&,Array<Double,_VForm> const&,
          Array<Double,_VForm> const&, GT const&);
      typedef void (*_pre_post_func)(Array<Double> const&,Array<Double>&,
                                     InteractionFuncDataState&,
                                     const InteractionParameter&);
      typedef void (*_kernel_single_func)(Array<Double> const&,
                    const InteractionParameter&,double*);
      typedef void (*_kernel_both_func)(Array<Double> const&,
                    const InteractionParameter&,double*,double*);

      void (*_allocate)(Array<Double>&,Array<Double>&,DVType&);
      _distance_sq_func   _distance_sq;
      _displacement_func  _displacement;
      _pre_post_func      _pre_2_post_for_e;
      _pre_post_func      _pre_2_post_for_g;
      _pre_post_func      _pre_2_post_for_eg;
      _kernel_single_func   _efunc;
      _kernel_single_func   _gfunc;
      _kernel_both_func     _egfunc;
      void (*_E)(DVType const&,Array<UInt> const&,Array<Double>&,Array<Double>&,
                 DVType&, Array<Type*> const&,InteractionFuncDataState&,
                 const InteractionParameter&,GT const&,double&,
                 _distance_sq_func,_displacement_func,_pre_post_func,
                 _kernel_single_func);
      void (*_G)(DVType const&,Array<UInt> const&,Array<Double>&,Array<Double>&,
                 DVType&,Array<Type*> const&,InteractionFuncDataState&,
                 const InteractionParameter&,GT const&,DVType&,
                 _distance_sq_func,_displacement_func,_pre_post_func,
                 _kernel_single_func);
      void (*_EG)(DVType const&,Array<UInt>const&,Array<Double>&,Array<Double>&,
                  DVType&,Array<Type*> const&,InteractionFuncDataState&,
                  const InteractionParameter&,GT const&,double&,DVType&,
                 _distance_sq_func,_displacement_func,_pre_post_func,
                 _kernel_both_func);

    public:

      InteractionFunction()
        : _tag(InteractionName::Unknown), _pre(), _post(), _vec(), _neighbor(),
          _status(),
          _allocate(nullptr), _distance_sq(nullptr), _displacement(nullptr),
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
               _displacement!=nullptr &&
               _pre_2_post_for_e!=nullptr && _pre_2_post_for_g!=nullptr &&
               _pre_2_post_for_eg!=nullptr && _efunc!=nullptr &&
               _gfunc!=nullptr && _egfunc!=nullptr && _E!=nullptr &&
               _G!=nullptr && _EG!=nullptr;
      }
      InteractionName Name() const { return _tag; }
      void reset() {
        _status.reset();
        _neighbor.reset();
        _vec.reset();
        _post.reset();
        _pre.reset();
        _tag = InteractionName::Unknown;
        _allocate = nullptr;
        _distance_sq = nullptr;
        _displacement = nullptr;
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
        _status.reset();
        return *this;
      }

      void allocate(InteractionName tag) {
        assert(tag!=InteractionName::Unknown);
        reset();
        _tag=tag;
        switch(_tag) {
          case InteractionName::PairHarmonic:
            _allocate=_allocate_func_pair_harmonic<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
              double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_pair_harmonic;
            _pre_2_post_for_g=_pre_2_post_for_g_pair_harmonic;
            _pre_2_post_for_eg=_pre_2_post_for_eg_pair_harmonic;
            _efunc=_efunc_pair_harmonic;
            _gfunc=_gfunc_pair_harmonic;
            _egfunc=_egfunc_pair_harmonic;
            _E=_E_pairwise<GT,DIM>;
            _G=_G_pairwise<GT,DIM>;
            _EG=_EG_pairwise<GT,DIM>;
            break;
          case InteractionName::PairLJ612:
            _allocate=_allocate_func_pair_lj612<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_pair_lj612;
            _pre_2_post_for_g=_pre_2_post_for_g_pair_lj612;
            _pre_2_post_for_eg=_pre_2_post_for_eg_pair_lj612;
            _efunc=_efunc_pair_lj612;
            _gfunc=_gfunc_pair_lj612;
            _egfunc=_egfunc_pair_lj612;
            _E=_E_pairwise<GT,DIM>;
            _G=_G_pairwise<GT,DIM>;
            _EG=_EG_pairwise<GT,DIM>;
            break;
          case InteractionName::PairCore12:
            _allocate=_allocate_func_pair_core12<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_pair_core12;
            _pre_2_post_for_g=_pre_2_post_for_g_pair_core12;
            _pre_2_post_for_eg=_pre_2_post_for_eg_pair_core12;
            _efunc=_efunc_pair_core12;
            _gfunc=_gfunc_pair_core12;
            _egfunc=_egfunc_pair_core12;
            _E=_E_pairwise<GT,DIM>;
            _G=_G_pairwise<GT,DIM>;
            _EG=_EG_pairwise<GT,DIM>;
            break;
          case InteractionName::PairLJ1012:
            _allocate=_allocate_func_pair_lj1012<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_pair_lj1012;
            _pre_2_post_for_g=_pre_2_post_for_g_pair_lj1012;
            _pre_2_post_for_eg=_pre_2_post_for_eg_pair_lj1012;
            _efunc=_efunc_pair_lj1012;
            _gfunc=_gfunc_pair_lj1012;
            _egfunc=_egfunc_pair_lj1012;
            _E=_E_pairwise<GT,DIM>;
            _G=_G_pairwise<GT,DIM>;
            _EG=_EG_pairwise<GT,DIM>;
            break;
          case InteractionName::PairLJ612Cut:
            _allocate=_allocate_func_pair_lj612cut<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_pair_lj612cut;
            _pre_2_post_for_g=_pre_2_post_for_g_pair_lj612cut;
            _pre_2_post_for_eg=_pre_2_post_for_eg_pair_lj612cut;
            _efunc=_efunc_pair_lj612cut;
            _gfunc=_gfunc_pair_lj612cut;
            _egfunc=_egfunc_pair_lj612cut;
            _E=_E_pairwise<GT,DIM>;
            _G=_G_pairwise<GT,DIM>;
            _EG=_EG_pairwise<GT,DIM>;
            break;
          case InteractionName::PairCoreLJ612:
            _allocate=_allocate_func_pair_corelj612<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_pair_corelj612;
            _pre_2_post_for_g=_pre_2_post_for_g_pair_corelj612;
            _pre_2_post_for_eg=_pre_2_post_for_eg_pair_corelj612;
            _efunc=_efunc_pair_corelj612;
            _gfunc=_gfunc_pair_corelj612;
            _egfunc=_egfunc_pair_corelj612;
            _E=_E_pairwise<GT,DIM>;
            _G=_G_pairwise<GT,DIM>;
            _EG=_EG_pairwise<GT,DIM>;
            break;
          case InteractionName::PairStepContinuous:
            _allocate=_allocate_func_pair_step_continuous<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_pair_step_continuous;
            _pre_2_post_for_g=_pre_2_post_for_g_pair_step_continuous;
            _pre_2_post_for_eg=_pre_2_post_for_eg_pair_step_continuous;
            _efunc=_efunc_pair_step_continuous;
            _gfunc=_gfunc_pair_step_continuous;
            _egfunc=_egfunc_pair_step_continuous;
            _E=_E_pairwise<GT,DIM>;
            _G=_G_pairwise<GT,DIM>;
            _EG=_EG_pairwise<GT,DIM>;
            break;
          case InteractionName::AngleHarmonic:
            _allocate=_allocate_func_angle_harmonic<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_angle_harmonic;
            _pre_2_post_for_g=_pre_2_post_for_g_angle_harmonic;
            _pre_2_post_for_eg=_pre_2_post_for_eg_angle_harmonic;
            _efunc=_efunc_angle_harmonic;
            _gfunc=_gfunc_angle_harmonic;
            _egfunc=_egfunc_angle_harmonic;
            _E=_E_angle<GT,DIM>;
            _G=_G_angle<GT,DIM>;
            _EG=_EG_angle<GT,DIM>;
            break;
          case InteractionName::DihedralPeriodic:
            _allocate=_allocate_func_dihedral_periodic<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_dihedral;
            _pre_2_post_for_g=_pre_2_post_for_g_dihedral;
            _pre_2_post_for_eg=_pre_2_post_for_eg_dihedral;
            _efunc=_efunc_dihedral_periodic;
            _gfunc=_gfunc_dihedral_periodic;
            _egfunc=_egfunc_dihedral_periodic;
            _E=_E_dihedral<GT,DIM>;
            _G=_G_dihedral<GT,DIM>;
            _EG=_EG_dihedral<GT,DIM>;
            break;
          case InteractionName::DihedralDualPeriodic:
            _allocate=_allocate_func_dihedral_multi_periodic<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_dihedral;
            _pre_2_post_for_g=_pre_2_post_for_g_dihedral;
            _pre_2_post_for_eg=_pre_2_post_for_eg_dihedral;
            _efunc=_efunc_dihedral_multi_periodic;
            _gfunc=_gfunc_dihedral_multi_periodic;
            _egfunc=_egfunc_dihedral_multi_periodic;
            _E=_E_dihedral<GT,DIM>;
            _G=_G_dihedral<GT,DIM>;
            _EG=_EG_dihedral<GT,DIM>;
            break;
          case InteractionName::DihedralDualPeriodicCommonPhase:
            _allocate=_allocate_func_dihedral_multi_periodic_common_phase<DIM>;
            _distance_sq=
              DistanceSQ<SystemKindName::Particle,SystemKindName::Particle,
                         double,_VForm,double,_VForm,double,_VForm,GT>;
            _displacement=
              DisplacementCalc<SystemKindName::Particle,
                               SystemKindName::Particle,double,_VForm,
                               double,_VForm,double,_VForm,GT>;
            _pre_2_post_for_e=_pre_2_post_for_e_dihedral;
            _pre_2_post_for_g=_pre_2_post_for_g_dihedral;
            _pre_2_post_for_eg=_pre_2_post_for_eg_dihedral;
            _efunc=_efunc_dihedral_multi_periodic_common_phase;
            _gfunc=_gfunc_dihedral_multi_periodic_common_phase;
            _egfunc=_egfunc_dihedral_multi_periodic_common_phase;
            _E=_E_dihedral<GT,DIM>;
            _G=_G_dihedral<GT,DIM>;
            _EG=_EG_dihedral<GT,DIM>;
            break;
          default:
            fprintf(stderr,"No Implemented!\n");
        }
        if(_allocate!=nullptr) _allocate(_pre,_post,_vec);
      }
      void imprint(const Type& F) { allocate(F.Name()); }
      void swap(Type& F) {
        std::swap(_tag,F._tag);
        std::swap(_pre,F._pre);
        std::swap(_post,F._post);
        std::swap(_vec,F._vec);
        std::swap(_neighbor,F._neighbor);
        std::swap(_status,F._status);
        std::swap(_allocate,F._allocate);
        std::swap(_distance_sq,F._distance_sq);
        std::swap(_displacement,F._displacement);
        std::swap(_pre_2_post_for_e,F._pre_2_post_for_e);
        std::swap(_pre_2_post_for_g,F._pre_2_post_for_g);
        std::swap(_pre_2_post_for_eg,F._pre_2_post_for_eg);
        std::swap(_efunc,F._efunc);
        std::swap(_gfunc,F._gfunc);
        std::swap(_egfunc,F._egfunc);
        std::swap(_E,F._E);
        std::swap(_G,F._G);
        std::swap(_EG,F._EG);
      }

      void E(DVType const& X,Array<UInt> const& ID,
             const InteractionParameter& P, GT const& Geo, double& Energy) {
        assert(_E!=nullptr);
        _E(X,ID,_pre,_post,_vec,_neighbor,_status,P,Geo,Energy,
           _distance_sq,_displacement,_pre_2_post_for_e,_efunc);
      }

      void G(DVType const& X,Array<UInt> const ID,
             const InteractionParameter& P, GT const& Geo, DVType& Gradient) {
        assert(_G!=nullptr);
        _G(X,ID,_pre,_post,_vec,_neighbor,_status,P,Geo,Gradient,
           _distance_sq,_displacement,_pre_2_post_for_g,_gfunc);
      }
      void EG(DVType const& X, Array<UInt> const& ID,
              const InteractionParameter& P, GT const& Geo, double& Energy,
              DVType& Gradient) {
        assert(_EG!=nullptr);
        _EG(X,ID,_pre,_post,_vec,_neighbor,_status,P,Geo,Energy,Gradient,
            _distance_sq,_displacement,_pre_2_post_for_eg,_egfunc);
      }

      void ClearStatus() { _status.reset(); }

  };

  template <typename GT,unsigned int DIM>
  const ArrayKernelName InteractionFunction<GT,DIM>::_VForm;

}

#endif

