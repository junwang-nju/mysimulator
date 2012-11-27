
#ifndef _System_Interaction_Parameter_Interface_H_
#define _System_Interaction_Parameter_Interface_H_

#include "array/interface.h"
#include "system/interaction/name.h"
#include "system/interaction/parameter/pairwise/harmonic/_allocate.h"
#include "system/interaction/parameter/pairwise/harmonic/_build.h"
#include "system/interaction/parameter/pairwise/lj612/_allocate.h"
#include "system/interaction/parameter/pairwise/lj612/_build.h"

namespace mysimulator {

  class InteractionParameter {

    public:

      typedef InteractionParameter  Type;
      typedef unsigned int size_type;

    private:

      InteractionName   _tag;
      Array<Double>     _FParam;
      Array<Int>        _IParam;

      void (*_allocate)(Array<Double>&,Array<Int>&);
      void (*_build)(Array<Double>&,Array<Int>&);

    public:

      InteractionParameter() : _tag(InteractionName::Unknown), _FParam(),
                               _IParam() {}
      InteractionParameter(const Type& P)
        : _tag(P._tag), _FParam(P._FParam), _IParam(P._IParam) {}
      InteractionParameter(Type&& P) : InteractionParameter() { swap(P); }
      virtual ~InteractionParameter() { reset(); }

      operator bool() const {
        return _tag != InteractionName::Unknown &&
               ( (bool)_FParam || (bool)_IParam );
      }
      InteractionName Name() const { return _tag; }
      double& operator[](size_type i) { return _FParam[i]; }
      double operator[](size_type i) const { return _FParam[i]; }
      int& operator()(size_type i) { return _IParam[i]; }
      int operator()(size_type i) const { return _IParam[i]; }
      void reset() {
        _tag=InteractionName::Unknown;
        _FParam.reset();
        _IParam.reset();
        _allocate=nullptr;
        _build=nullptr;
      }

      Type& operator=(const Type& P) {
        assert((bool)(*this));
        assert((bool)P);
        assert(Name()==P.Name());
        if((bool)_FParam)   _FParam=P._FParam;
        if((bool)_IParam)   _IParam=P._IParam;
        return *this;
      }

      void allocate(InteractionName tag) {
        reset();
        _tag=tag;
        switch(tag) {
          case PairHarmonic:
            _allocate=_allocate_pair_harmonic;
            _build=_build_pair_harmonic;
            break;
          case PairLJ612:
            _allocate=_allocate_pair_lj612;
            _build=_build_pair_lj612;
            break;
          default:
            fprintf(stderr,"No Implemented!\n");
        }
        if(_allocate!=nullptr) _allocate(_FParam,_IParam);
      }
      void swap(Type& P) {
        std::swap(_tag,P._tag);
        std::swap(_FParam,P._FParam);
        std::swap(_IParam,P._IParam);
      }

      void build() {
        assert(_build!=nullptr);
        _build(_FParam,_IParam);
      }

  };

}

namespace std {

  void swap(mysimulator::InteractionParameter& P1,
            mysimulator::InteractionParameter& P2) {
    P1.swap(P2);
  }

}

#endif

