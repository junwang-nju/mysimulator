
#ifndef _Propagator_Output_Interface_H_
#define _Propagator_Output_Interface_H_

namespace mysimulator {

  template <typename T,typename GT> class System;
  template <typename T,typename GT,typename GR> class Propagator;

  template <typename T,typename GT,typename GR>
  class PropagatorOutput {

    public:

      typedef PropagatorOutput<T,GT,GR>  Type;
      template <typename T1,typename GT1,typename GR1>
      friend void Clear(PropagatorOutput<T1,GT1,GR1>&);

      PropagatorOutput() : _ostep(0), _onstep(0), _nostep(0) {}
      virtual ~PropagatorOutput() { Clear(*this); }

      bool IsValid() const { return _onstep!=0; }

      void SetTime(const T& ot,const T& dt, unsigned int tn) {
        _onstep=static_cast<unsigned int>(ot/dt+0.5);
        if(_onstep==0) _onstep=1;
        _ostep=_onstep*dt;
        _nostep=tn/_onstep;
      }
      void SetTime(unsigned int n,const T& dt, unsigned int tn) {
        _onstep=n;
        _ostep=_onstep*dt;
        _nostep=tn/_onstep;
      }

      const T& OutputInterval() const { return _ostep; }
      const unsigned int& OutputNumberStep() const { return _onstep; }
      const unsigned int& NumberOutput() const { return _nostep; }

      virtual void Write(const T&,System<T,GT>&,Propagator<T,GT,GR>*) = 0;

    protected:

      T _ostep;
      unsigned int _onstep;
      unsigned int _nostep;

    private:

      PropagatorOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT,typename GR>
  void Clear(PropagatorOutput<T,GT,GR>& P) {
    P._ostep=0;
    P._onstep=0;
    P._nostep=0;
  }

}

#endif

