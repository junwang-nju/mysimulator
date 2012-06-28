
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
      template <typename T1,typename GT1> friend Clear(Propagator<T1,GT1>&);

      Propagator()
        : _tag(UnknownPropagator), _props(), _bind(NULL), _param(),
          _time(NULL), _output(NULL) {}
      virtual ~Propagator() { Clear(*this); }

      bool IsValid() const {
        return (_tag!=UnknownPropagator)&&_props.IsValid()&&(_bind!=NULL)&&
               _param.IsValid()&&(_time!=NULL)&&(_output!=NULL);
      }

      StepPropagator<T>* Step(unsigned int n) { return _props[n]; }
      Unique64Bit& Parameter(unsigned int n) { return _param[n]; }
      PropagatorTime<T>*& Time() { return _time; }
      PropagatorOutput<T,GT>*& Output() { return _output; }

      const StepPropagator<T>* Step(unsigned int n) const { return _props[n]; }
      const Unique64Bit& Parameter(unsigned int n) const { return _param[n]; }
      const PropagatorTime<T>* const& Time() const { return _time; }
      const PropagatorOutput<T,GT>* const& Output() const{ return _output; }

      virtual void Allocate(const Array<StepPropagatorName>& PN,...) = 0;
      virtual void IntroduceSystem(System<T,GT>&) = 0;
      virtual void Evolute(System<T,GT>&) = 0;

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

#endif

