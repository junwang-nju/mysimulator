
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

      PropagatorOutput() : _OutInterval(0), _OutNumberStep(0) {}
      virtual ~PropagatorOutput() { Clear(*this); }

      bool IsValid() const { return _OutNumberStep!=0; }

      void SetTime(const T& ot,const T& dt) {
        _OutNumberStep=static_cast<unsigned int>(ot/dt);
        if(_OutNumberStep==0) _OutNumberStep=1;
        _OutInterval=_OutNumberStep*dt;
      }
      void SetTime(unsigned int n,const T& dt) {
        _OutNumberStep=n;
        _OutInterval=_OutNumberStep*dt;
      }

      const T& OutputInterval() const { return _OutInterval; }
      const unsigned int& OutputNumberStep() const { return _OutNumberStep; }

      virtual void Write(const T&,System<T,GT>&,Propagator<T,GT,GR>*) = 0;

    protected:

      T _OutInterval;
      unsigned int _OutNumberStep;

    private:

      PropagatorOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT,typename GR>
  void Clear(PropagatorOutput<T,GT,GR>& P) {
    P._OutInterval=0;
    P._OutNumberStep=0;
  }

}

#endif

