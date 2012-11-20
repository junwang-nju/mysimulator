
#ifndef _System_Interaction_Parameter_Interface_H_
#define _System_Interaction_Parameter_Interface_H_

#include "array/interface.h"
#include "system/interaction/name.h"

namespace mysimulator {

  class InteractionParameter {

    public:

      typedef InteractionParameter  Type;
      typedef unsigned int size_type;

    protected:

      InteractionName   _tag;
      Array<Double>     _FParam;
      Array<Int>        _IParam;

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
      }

      Type& operator=(const Type& P) {
        assert((bool)(*this));
        assert((bool)P);
        assert(Name()==P.Name());
        if((bool)_FParam)   _FParam=P._FParam;
        if((bool)_IParam)   _IParam=P._IParam;
        return *this;
      }

      void swap(Type& P) {
        std::swap(_tag,P._tag);
        std::swap(_FParam,P._FParam);
        std::swap(_IParam,P._IParam);
      }

      virtual void allocate() = 0;
      virtual void build() = 0;

  };

}

namespace std {

  void swap(mysimulator::InteractionParameter& P1,
            mysimulator::InteractionParameter& P2) {
    P1.swap(P2);
  }

}

#include "system/interaction/parameter/pairwise/harmonic/interface.h"
#include "system/interaction/parameter/pairwise/lj612/interface.h"

namespace mysimulator {

  void Introduce(InteractionParameter*& P, const InteractionName FN) {
    if(P!=NULL) { delete P; P=NULL; }
    switch(FN) {
      case InteractionName::PairHarmonic: P=new PairHarmonicParameter;  break;
      case InteractionName::PairLJ612: P=new PairLJ612Parameter; break;
      case InteractionName::Unknown:
      default:
        fprintf(stderr,"Unknown Interaction!\n");
    }
    if(P!=NULL) P->allocate();
  }

}

#endif

