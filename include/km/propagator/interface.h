
#ifndef _Propagator_Interface_H_
#define _Propagator_Interface_H_

#include "propagator/name.h"
#include "step-propagator-binder/interface.h"
#include "propagator-time/interface.h"
#include "propagator-output/interface.h"
#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename GT> class Propagator;
  template <typename T,typename GT> void Clear(Propagator<T,GT>&);

  template <typename T,typename GT>
  class Propagator {

    public:

      typedef Propagator<T,GT>    Type;
      friend void Clear<T,GT>(Propagator<T,GT>&);

      Propagator()
        : _tag(UnknownPropagator), _props(), _bind(NULL), _param(),
          _time(NULL), _output(NULL) {}
      virtual ~Propagator() { Clear(*this); }

      virtual bool IsValid() const {
        return (_tag!=UnknownPropagator)&&_props.IsValid()&&(_bind!=NULL)&&
               _param.IsValid();
      }
      const PropagatorName Name() const { return _tag; }

      StepPropagator<T>* Step(unsigned int n) { return _props[n]; }
      Unique64Bit& Parameter(unsigned int n) { return _param[n]; }
      T& Time(unsigned int n) {
        assert(_time!=NULL);
        assert(_time->IsTProperty(n));
        return Value<T>(_time->Parameter(n));
      }
      unsigned int& IntTime(unsigned int n) {
        assert(_time!=NULL);
        assert(_time->IsUIntProperty(n));
        return Value<unsigned int>(_time->Parameter(n));
      }

      const StepPropagator<T>* Step(unsigned int n) const { return _props[n]; }
      const Unique64Bit& Parameter(unsigned int n) const { return _param[n]; }
      const T& Time(unsigned int n) const {
        assert(_time!=NULL);
        assert(_time->IsTProperty(n));
        return Value<T>(_time->Parameter(n));
      }
      const unsigned int& IntTime(unsigned int n) const {
        assert(_time!=NULL);
        assert(_time->IsUIntProperty(n));
        return Value<unsigned int>(_time->Parameter(n));
      }

      void Init() {
        for(unsigned int i=0;i<this->_props.Size();++i)
          this->_props[i]->Init();
      }

      virtual void IntroduceSystem(System<T,GT>& S) {
        assert(S.Location().IsValid());
        for(unsigned int i=0;i<_props.Size();++i)
          _props[i]->IntroduceX(S.Location());
        if(S.Gradient().IsValid())
          for(unsigned int i=0;i<_props.Size();++i)
            _props[i]->IntroduceG(S.Gradient());
        if(S.Velocity().IsValid())
          for(unsigned int i=0;i<_props.Size();++i)
            _props[i]->IntroduceV(S.Velocity());
      }
      virtual void DetachSystem() {
        for(unsigned int i=0;i<_props.Size();++i) _props[i]->Detach();
      }
      template <typename OT>
      void AllocateOutput() {
        if(_output!=NULL) { delete _output; _output=NULL; }
        _output=new OT;
        _output->Allocate();
      }
      void UpdateTime(unsigned int n) { assert(_time!=NULL); _time->Update(n); }
      virtual void Update() {
        assert(_props.IsValid());
        for(unsigned int i=0;i<_props.Size();++i) _props[i]->Update();
      }

      virtual void Allocate(const Array<StepPropagatorName>& PN,...) = 0;
      virtual unsigned int Evolute(System<T,GT>&) = 0;

      virtual const T KineticEnergy() const = 0;
      virtual void UpdateKineticEnergy() = 0;
      virtual void AllocateParameter() = 0;

    protected:

      PropagatorName                _tag;
      Array<StepPropagator<T>*>     _props;
      StepPropagatorBinder<T,GT>*   _bind;
      Array<Unique64Bit>            _param;
      PropagatorTime<T>*            _time;
      PropagatorOutput<T,GT>*       _output;

      void _ClearContent() {
        if(_bind!=NULL) { delete _bind; _bind=NULL; }
        if(_props.IsValid())
          for(unsigned int i=0;i<_props.Size();++i)
            if(_props[i]!=NULL) { delete _props[i]; _props[i]=NULL; }
        _ClearParameter();
        if(_time!=NULL) { delete _time; _time=NULL; }
        if(_output!=NULL) { delete _output; _output=NULL; }
      }
      virtual void _ClearParameter() = 0;

    private:

      Propagator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(Propagator<T,GT>& P) {
    P._tag=UnknownPropagator;
    P._ClearContent();
    Clear(P._props);
    Clear(P._param);
  }

}

#include "propagator/molecular-dynamics/interface.h"
#include "propagator/neighbor-list-molecular-dynamics/interface.h"
#include "propagator/minimizer/steep/interface.h"
#include "propagator/minimizer/conjg/interface.h"
#include "propagator/minimizer/lbfgs/interface.h"
#include "propagator/minimizer-line/name.h"

namespace mysimulator {

  template <typename T,typename GT>
  void Introduce(Propagator<T,GT>*& P, PropagatorName PN, ...) {
    if(P!=NULL) { delete P; P=NULL; }
    va_list vl;
    va_start(vl,PN);
    PropagatorLineMinimizerName LN;
    switch(PN) {
      case MolecularDynamics:
        P=new PropagatorMD<T,GT>;
        break;
      case MolecularDynamicsWithNeighborList:
        P=new PropagatorMDWithNL<T,GT>;
        break;
      case SteepestDescentMinimizer:
        LN=static_cast<PropagatorLineMinimizerName>(va_arg(vl,unsigned int));
        switch(LN) {
          case TrackingLineMinimizer:
            P=new PropagatorSteepestDescentMinimizer<T,GT>; break;
          default:
            fprintf(stderr,"Unknown Line Minimizer Name!\n");
        }
        break;
      case ConjugateGradientMinimizer:
        LN=static_cast<PropagatorLineMinimizerName>(va_arg(vl,unsigned int));
        switch(LN) {
          case TrackingLineMinimizer:
            P=new PropagatorConjugateGradientMinimizer<T,GT>; break;
          default:
            fprintf(stderr,"Unknown Line Minimizer Name!\n");
        }
        break;
      case LBFGSMinimizer:
        LN=static_cast<PropagatorLineMinimizerName>(va_arg(vl,unsigned int));
        switch(LN) {
          case TrackingLineMinimizer:
            P=new PropagatorLBFGSMinimizer<T,GT>; break;
          default:
            fprintf(stderr,"Unknown Line Minimizer Name!\n");
        }
        break;
      default:
        fprintf(stderr,"Unknown Propagator!\n");
    }
    va_end(vl);
  }

}

#endif

