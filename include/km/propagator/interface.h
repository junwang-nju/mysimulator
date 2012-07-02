
#ifndef _Propagator_Interface_H_
#define _Propagator_Interface_H_

#include "propagator/name.h"
#include "step-propagator-binder/interface.h"
#include "propagator-time/interface.h"
#include "propagator-output/interface.h"
#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  class Propagator {

    public:

      typedef Propagator<T,GT>    Type;
      template <typename T1,typename G1> friend void Clear(Propagator<T1,G1>&);

      Propagator()
        : _tag(UnknownPropagator), _props(), _bind(NULL), _param(),
          _time(NULL), _output(NULL) {}
      virtual ~Propagator() { Clear(*this); }

      bool IsValid() const {
        return (_tag!=UnknownPropagator)&&_props.IsValid()&&(_bind!=NULL)&&
               _param.IsValid()&&(_time!=NULL)&&(_output!=NULL);
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
      void Update() {
        assert(_props.IsValid());
        for(unsigned int i=0;i<_props.Size();++i) _props[i]->Update();
      }

      virtual void Allocate(const Array<StepPropagatorName>& PN,...) = 0;
      virtual void Evolute(System<T,GT>&) = 0;

      virtual const T KineticEnergy() const = 0;
      virtual void UpdateKineticEnergy() = 0;

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

namespace mysimulator {

  template <typename T,typename GT>
  void Introduce(Propagator<T,GT>*& P, PropagatorName PN) {
    if(P!=NULL) { delete P; P=NULL; }
    switch(PN) {
      case MolecularDynamics:
        P=new PropagatorMD<T,GT>;
        break;
      default:
        fprintf(stderr,"Unknown Propagator!\n");
    }
  }

}

#endif

