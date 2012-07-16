
#ifndef _Interaction_Parameter_Interface_H_
#define _Interaction_Parameter_Interface_H_

#include "array/interface.h"
#include "unique/64bit/interface.h"
#include "interaction-func/name.h"

namespace mysimulator {

  template <typename T> class InteractionParameter;
  template <typename T> void Clear(InteractionParameter<T>&);
  template <typename T>
  void Introduce(InteractionParameter<T>*&,const InteractionFuncName&,...);

  template <typename T>
  class InteractionParameter {

    public:

      typedef InteractionParameter<T>   Type;
      typedef typename IsNumeric<T>::Type   NumericCheck;
      friend void Clear<T>(InteractionParameter<T>&);
      friend void Introduce<T>(InteractionParameter<T>*&,
                               const InteractionFuncName&,...);

      InteractionParameter() : _tag(UnknownInteractionFunc), _data() {}
      virtual ~InteractionParameter() { Clear(*this); }

      bool IsValid() const { return _data.IsValid(); }
      Unique64Bit& operator[](unsigned int n) { return _data[n]; }
      const Unique64Bit& operator[](unsigned int n) const { return _data[n]; }

      void Copy(const InteractionParameter<T>& F) { _data.Copy(F._data); }

      virtual void Allocate()=0;
      virtual void Build()=0;

    protected:

      InteractionFuncName _tag;
      Array<Unique64Bit> _data;

    private:

      InteractionParameter(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameter<T>& P) { Clear(P._data); }

  template <typename T>
  void _Copy(InteractionParameter<T>& P,const InteractionParameter<T>& BP) {
    P.Copy(BP);
  }

}

#include "interaction-parameter/core12/interface.h"
#include "interaction-parameter/corelj612/interface.h"
#include "interaction-parameter/coulomb/interface.h"
#include "interaction-parameter/dist-coulomb/interface.h"
#include "interaction-parameter/harmonic/interface.h"
#include "interaction-parameter/lj1012/interface.h"
#include "interaction-parameter/lj1012cut/interface.h"
#include "interaction-parameter/lj612/interface.h"
#include "interaction-parameter/lj612cut/interface.h"
#include "interaction-parameter/angle-harmonic/interface.h"
#include "interaction-parameter/dihedral-periodic/interface.h"
#include <cstdarg>

namespace mysimulator {

  template <typename T>
  void Introduce(InteractionParameter<T>*& P,const InteractionFuncName& FN,
                 ...) {
    if(P!=NULL) { delete P; P=NULL; }
    va_list vl;
    va_start(vl,FN);
    switch(FN) {
      case Harmonic:
      case WallHarmonic:
        P=new InteractionParameterHarmonic<T>;  break;
      case Core12:
      case WallCore12:
        P=new InteractionParameterCore12<T>;  break;
      case CoreLJ612:
        P=new InteractionParameterCoreLJ612<T>; break;
      case Coulomb:
        P=new InteractionParameterCoulomb<T>; break;
      case DistDielCoulomb:
        P=new InteractionParameterDistDielCoulomb<T>; break;
      case LJ1012:
        P=new InteractionParameterLJ1012<T>;  break;
      case LJ1012Cut:
        P=new InteractionParameterLJ1012Cut<T>; break;
      case LJ612:
        P=new InteractionParameterLJ612<T>; break;
      case LJ612Cut:
        P=new InteractionParameterLJ612Cut<T>;  break;
      case AngleHarmonic:
        P=new InteractionParameterAngleHarmonic<T>; break;
      case DihedralPeriodic:
        P=new InteractionParameterDihedralPeriodic<T>;
        P->_data.Allocate(DihedralPeriodicShift);
        Value<unsigned int>(P->_data[DihedralPeriodicNumberUnit])=
          va_arg(vl,unsigned int);
        break;
      case UnknownInteractionFunc:
      default:
        fprintf(stderr,"Unknown Interaction!\n");
    }
    if(P!=NULL)   P->Allocate();
    va_end(vl);
  }

}

#endif

