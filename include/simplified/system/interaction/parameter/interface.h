
#ifndef _System_Interaction_Parameter_Interface_H_
#define _System_Interaction_Parameter_Interface_H_

#include "array/interface.h"
#include "system/interaction/name.h"

namespace mysimulator {

  class InteractionParameter {

    public:

      typedef InteractionParameter  Type;
      typedef unsigned int size_type;

    private:

      InteractionName   _tag;
      Array<Double>     _FParam;
      Array<Int>        _IParam;
      Array<Type>       _PParam;

      void (*_allocate)(Array<Double>&,Array<Int>&,Array<Type>&);
      void (*_build)(Array<Double>&,Array<Int>&,Array<Type>&);

    public:

      InteractionParameter() : _tag(InteractionName::Unknown), _FParam(),
                               _IParam(), _PParam() {}
      InteractionParameter(const Type& P)
        : _tag(P._tag), _FParam(P._FParam), _IParam(P._IParam),
          _PParam(P._PParam) {}
      InteractionParameter(Type&& P) : InteractionParameter() { swap(P); }
      ~InteractionParameter() { reset(); }

      operator bool() const {
        return _tag != InteractionName::Unknown &&
               ( (bool)_FParam || (bool)_IParam || (bool)_PParam );
      }
      InteractionName Name() const { return _tag; }
      double& operator[](size_type i) { return _FParam[i]; }
      double operator[](size_type i) const { return _FParam[i]; }
      int& operator()(size_type i) { return _IParam[i]; }
      int operator()(size_type i) const { return _IParam[i]; }
      Type& child(size_type i) { return _PParam[i]; }
      Type const& child(size_type i) const { return _PParam[i]; }
      void reset() {
        _tag=InteractionName::Unknown;
        _FParam.reset();
        _IParam.reset();
        _PParam.reset();
        _allocate=nullptr;
        _build=nullptr;
      }

      Type& operator=(const Type& P) {
        assert((bool)(*this));
        assert((bool)P);
        assert(Name()==P.Name());
        if((bool)_FParam)   _FParam=P._FParam;
        if((bool)_IParam)   _IParam=P._IParam;
        if((bool)_PParam)   _PParam=P._PParam;
        return *this;
      }

      void allocate(InteractionName);
      void swap(Type& P) {
        std::swap(_tag,P._tag);
        std::swap(_FParam,P._FParam);
        std::swap(_IParam,P._IParam);
        std::swap(_PParam,P._PParam);
      }

      void build() {
        assert(_build!=nullptr);
        _build(_FParam,_IParam,_PParam);
      }

  };

}

#include "system/interaction/parameter/pairwise/harmonic/_allocate.h"
#include "system/interaction/parameter/pairwise/harmonic/_build.h"
#include "system/interaction/parameter/pairwise/lj612/_allocate.h"
#include "system/interaction/parameter/pairwise/lj612/_build.h"
#include "system/interaction/parameter/pairwise/core12/_allocate.h"
#include "system/interaction/parameter/pairwise/core12/_build.h"
#include "system/interaction/parameter/pairwise/lj1012/_allocate.h"
#include "system/interaction/parameter/pairwise/lj1012/_build.h"
#include "system/interaction/parameter/pairwise/lj612cut/_allocate.h"
#include "system/interaction/parameter/pairwise/lj612cut/_build.h"
#include "system/interaction/parameter/pairwise/corelj612/_allocate.h"
#include "system/interaction/parameter/pairwise/corelj612/_build.h"
#include "system/interaction/parameter/pairwise/step-continuous/_allocate.h"
#include "system/interaction/parameter/pairwise/step-continuous/_build.h"
#include "system/interaction/parameter/angle/harmonic/_allocate.h"
#include "system/interaction/parameter/angle/harmonic/_build.h"
#include "system/interaction/parameter/dihedral/periodic/_allocate.h"
#include "system/interaction/parameter/dihedral/periodic/_build.h"
#include "system/interaction/parameter/dihedral/dual-periodic/_allocate.h"
#include "system/interaction/parameter/dihedral/dual-periodic/_build.h"
#include "system/interaction/parameter/dihedral/dual-periodic-common-phase/_allocate.h"
#include "system/interaction/parameter/dihedral/dual-periodic-common-phase/_build.h"

namespace mysimulator {

  void InteractionParameter::allocate(InteractionName tag) {
    reset();
    _tag=tag;
    switch(tag) {
      case InteractionName::PairHarmonic:
        _allocate=_allocate_param_pair_harmonic;
        _build=_build_pair_harmonic;
        break;
      case InteractionName::PairLJ612:
        _allocate=_allocate_param_pair_lj612;
        _build=_build_pair_lj612;
        break;
      case InteractionName::PairCore12:
        _allocate=_allocate_param_pair_core12;
        _build=_build_pair_core12;
        break;
      case InteractionName::PairLJ1012:
        _allocate=_allocate_param_pair_lj1012;
        _build=_build_pair_lj1012;
        break;
      case InteractionName::PairLJ612Cut:
        _allocate=_allocate_param_pair_lj612cut;
        _build=_build_pair_lj612cut;
        break;
      case InteractionName::PairCoreLJ612:
        _allocate=_allocate_param_pair_corelj612;
        _build=_build_pair_corelj612;
        break;
      case InteractionName::PairStepContinuous:
        _allocate=_allocate_param_pair_step_continuous;
        _build=_build_pair_step_continuous;
        break;
      case InteractionName::AngleHarmonic:
        _allocate=_allocate_param_angle_harmonic;
        _build=_build_angle_harmonic;
        break;
      case InteractionName::DihedralPeriodic:
        _allocate=_allocate_param_dihedral_periodic;
        _build=_build_dihedral_periodic;
        break;
      case InteractionName::DihedralDualPeriodic:
        _allocate=_allocate_param_dihedral_dual_periodic;
        _build=_build_dihedral_dual_periodic;
        break;
      case InteractionName::DihedralDualPeriodicCommonPhase:
        _allocate=_allocate_param_dihedral_dual_periodic_common_phase;
        _build=_build_dihedral_dual_periodic_common_phase;
        break;
      default:
        fprintf(stderr,"No Implemented!\n");
    }
    if(_allocate!=nullptr) _allocate(_FParam,_IParam,_PParam);
  }

}

namespace std {

  void swap(mysimulator::InteractionParameter& P1,
            mysimulator::InteractionParameter& P2) {
    P1.swap(P2);
  }

}

#endif

