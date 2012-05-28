
#ifndef _Propagator_Regular_Interface_H_
#define _Propagator_Regular_Interface_H_

#include "propagator/interface.h"

namespace mysimulator {

  template <typename T,typename GT,
            typename GRNG=BoxMuller<MersenneTwisterStandard> >
  class PropagatorRegular : public Propagator<T,GT,GRNG> {

    public:

      typedef PropagatorRegular<T,GT,GRNG>    Type;
      typedef Propagator<T,GT,GRNG>   ParentType;

      PropagatorRegular() : ParentType() {}
      virtual ~PropagatorRegular() { Clear(*this); }

      virtual void IntroduceSystem(System<T,GT>& S) {
        for(unsigned int i=0;i<this->_props.Size();++i)
        for(unsigned int j=0;j<this->_props[i].Size();++j) {
          this->_props[i][j]->IntroduceX(S.Location());
          this->_props[i][j]->IntroduceG(S.Gradient());
          this->_props[i][j]->IntroduceV(S.Velocity());
        }
      }

      virtual void Evolute(System<T,GT>& S) {
        this->_out->Write(this->_time.NowTime(),S,this);
        for(unsigned int i=0;i<this->_out->NumberOutput();++i) {
          for(unsigned int k=0;k<this->_out->OutputNumberStep();++k)
            this->_bind[0]->Evolute(S.Location(),S.Gradient(),
                                    S.InteractionGroup(0),this->_props[0]);
          this->_time.IncNowTime(this->_out->OutputInterval(),
                                 this->_out->OutputNumberStep());
          this->_out->Write(this->_time.NowTime(),S,this);
        }
        if(this->_time.NowStep()<this->_time.TotalStep()) {
          for(unsigned int i=this->_time.NowTime();
                           i<this->_time.TotalStep();++i)
            this->_bind[0]->Evolute(S.Location(),S.Gradient(),
                                    S.InteractionGroup(0),this->_props[0]);
          this->_time.SetNowTime(this->_time.TotalPeriod(),
                                 this->_time.TotalStep());
          this->_out->Write(this->_time.NowTime(),S,this);
        }
      }

    private:

      PropagatorRegular(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT,typename GRNG>
  void Clear(PropagatorRegular<T,GT,GRNG>& P) {
    typedef typename PropagatorRegular<T,GT,GRNG>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

