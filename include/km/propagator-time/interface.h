
#ifndef _Propagator_Time_Interface_H_
#define _Propagator_Time_Interface_H_

namespace mysimulator {

  template <typename T>
  class PropagatorTime {

    public:

      typedef PropagatorTime<T> Type;
      template <typename T1> friend void Clear(PropagatorTime<T1>&);

      PropagatorTime() : _step(0), _now(0), _nnow(0), _alltime(0), _nstep(0) {}
      ~PropagatorTime() { Clear(*this); }

      bool IsValid() const { return _step>0; }

      const T& TimeStep() const { return _step; }
      const T& NowTime() const { return _now; }
      const unsigned int& NowStep() const { return _nnow; }
      const T& TotalPeriod() const { return _alltime; }
      const unsigned int& TotalStep() const { return _nstep; }

      void InitNowTime(const T& nt=0) { _now=nt; _nnow=0; }
      void SetNowTime(const T& nt,unsigned int nn) { _now=nt; _nnow=nn; }
      void SetTime(const T& dt, const T& tt) {
        _step=dt;
        _nstep=static_cast<unsigned int>(tt/dt+0.5);
        _alltime=_step*_nstep;
      }
      void SetTime(const T& dt, unsigned int n) {
        _step=dt;
        _nstep=n;
        _alltime=_step*_nstep;
      }
      void SetTime(unsigned int n,const T& tt) {
        _step=tt/n;
        _nstep=n;
        _alltime=_step*_nstep;
      }
      void IncNowTime(const T& dt, unsigned int dn) {
        _now+=dt;
        _nnow+=dn;
      }

    protected:

      T _step;
      T _now;
      unsigned int _nnow;
      T _alltime;
      unsigned int _nstep;

    private:

      PropagatorTime(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(PropagatorTime<T>& P) {
    P._step=0;
    P._now=0;
    P._nnow=0;
    P._alltime=0;
    P._nstep=0;
  }

}

#endif

