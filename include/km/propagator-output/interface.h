
#ifndef _Propagator_Output_Interface_H_
#define _Propagator_Output_Interface_H_

namespace mysimulator {

  template <typename T,typename GT> class System;
  template <typename T,typename GT> class Propagator;

  template <typename T,typename GT,typename GR>
  class PropagatorOutput {

    public:

      typedef PropagatorOutput<T,GT>  Type;

      PropagatorOutput() {}
      virtual ~PropagatorOutput() { Clear(*this); }

      bool IsValid() const { return true; }

      virtual void Write(const T&,System<T,GT>&,Propagator<T,GT>&) = 0;

    private:

      PropagatorOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

