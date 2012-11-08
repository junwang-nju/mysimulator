
#ifndef _System_Interaction_Parameter_Interface_H_
#define _System_Interaction_Parameter_Interface_H_

#include "array/interface.h"
#include "system/interaction/name.h"

namespace mysimulator {

  template <typename FT=double>
  class InteractionParameter {

    public:

      static_assert(__float_point_flag<FT>::FG,
                    "Floating-Point Data are expected!\n");

    private:

      InteractionName       _tag;
      Array<Intrinsic<FT>>  _FParam;
      Array<Int>            _IParam;

    public:

      typedef InteractionParameter<FT>   Type;
      typedef unsigned int size_type;

      InteractionParameter() : _tag(InteractionName::UnknownInteraction),
                               _FParam(), _IParam() {}
      InteractionParameter(const Type& P)
        : _tag(P._tag), _FParam(P._FParam), _IParam(P._IParam) {}
      InteractionParameter(Type&& P) : InteractionParameter() { swap(P); }
      virtual ~InteractionParameter() { reset(); }

      operator bool() const {
        return _tag!=InteractionName::UnknownInteraction &&
               ( (bool)_FParam || (bool)_IParam );
      }
      InteractionName Name() const { return _tag; }
      FT& operator[](size_type i) { return _FParam[i]; }
      FT const& operator[](size_type i) const { return _FParam[i]; }
      int& operator()(size_type i) { return _IParam[i]; }
      int operator()(size_type i) const { return _IParam[i]; }

      Type& operator=(const Type& P) {
        assert((bool)(*this));
        assert((bool)P);
        assert(Name()==P.Name());
        if((bool)_FParam) _FParam=P._FParam;
        if((bool)_IParam) _IParam=P._IParam;
        return *this;
      }

      void reset() {
        _tag=InteractionName::UnknownInteraction;
        _FParam.reset();
        _IParam.reset();
      }

      void swap(Type&& P) {
        swap(_tag,P._tag);
        swap(_FParam,P._FParam);
        swap(_IParam,P._IParam);
      }

      virtual void allocate() = 0;
      virtual void build() = 0;

  };

}

namespace std {

  template <typename T>
  void swap(mysimulator::InteractionParameter<T>& P1,
            mysimulator::InteractionParameter<T>& P2) {
    P1.swap(P2);
  }

}

#include "system/interaction/parameter/pairwise/harmonic/interface.h"
#include "system/interaction/parameter/pairwise/lj612/interface.h"
#include <cstdarg>

namespace mysimulator {

  template <typename T>
  void Introduce(InteractionParameter<T>*& P,const InteractionName& FN) {
    if(P!=NULL) { delete P; P=NULL; }
    switch(FN) {
      case InteractionName::PairHarmonic:
        P=new PairHarmonicParameter<T>;
        break;
      case InteractionName::PairLJ612:
        P=new PairLJ612Parameter<T>;
        break;
      case InteractionName::UnknownInteraction:
      default:
        fprintf(stderr,"Unknown Interaction!\n");
    }
    if(P!=NULL) P->allocate();
  }

}

#endif

