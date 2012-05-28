
#ifndef _Propagator_MolecularDynamics_Interface_H_
#define _Propagator_MolecularDynamics_Interface_H_

#include "propagator/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  class PropagatorMD : public Propagator<T,GT> {

    public:

      typedef PropagatorMD<T,GT>  Type;
      typedef Propagator<T,GT>    ParentType;
      template <typename T1,typename GT1>
      friend void Clear(PropagatorMD<T1,GT>&);

      PropagatorMD() : ParentType(), _massFlag(UnknownMassProperty),
                       _fricFlag(UnknownFrictionProperty) {}
      virtual ~PropagatorMD() { Clear(*this); }

      virtual void SetTime1(const T& nowT, ...) {
        assert(_time.IsValid());
        assert(_time.Name()==MolecularDynamics);
        this->_time.InitNowTime(nowT);
        va_list vl;
        va_start(vl,nowT);
        T totT=va_arg(vl,T);
        T dT=va_arg(vl,T);
        this->_time.SetTime(totT,dT);
        va_end(vl);
      }
      virtual void SetTime2(const T& nowT, ...) {
        assert(_time.IsValid());
        assert(_time.Name()==MolecularDynamics);
        this->_time.InitNowTime(nowT);
        va_list vl;
        va_start(vl,nowT);
        T dT=va_arg(vl,T);
        unsigned int nT=va_arg(vl,unsigned int);
        this->_time.SetTime(dT,nT);
        va_end(vl);
      }

      virtual void Allocate(const Array<StepPropagatorName>& PN, ...) {
        Clear(*this);
        this->_tag=MolecularDynamics;
        unsigned int fg=_Flag(PN);
        va_list vl;
        va_start(vl,PN);
        if(fg&1) {
        }
        _props.Allocate(PN.Size());
        va_end(vl);
      }

    protected:

      MassPropertyName _massFlag;
      FrictionPropertyName  _fricFlag;

      virtual void _ClearParameter() {
      }

    private:

      unsigned int _Flag(const Array<StepPropagatorName>& PN) {
        unsigned int fg=0;
        for(unsigned int i=0;i<PN.Size();++i)
          switch(PN[i]) {
            case VelVerletConstE:
            case VelVerletBerendsen:
              fg|=1;
              break;
            case VelVerletLangevin:
              fg|=7;
              break;
            case FixPosition:
              break;
            default:
              fprintf(stderr,"Improper StepPropagator\n");
          }
        return fg;
      }

      PropagatorMD(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(PropagatorMD<T,GT>& P) {
    typedef typename PropagatorMD<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(P));
    P._massFlag=UnknownMassProperty;
    P._fricFlag=UnknownFrictionProperty;
  }

}

#endif

