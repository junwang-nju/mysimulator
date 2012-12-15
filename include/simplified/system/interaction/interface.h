
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

#include "system/interaction/function/interface.h"
#include "system/interaction/parameter/interface.h"
#include "system/interaction/id-size.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM=GT::Dimension>
  class SystemInteraction {

    public:

      typedef SystemInteraction<GT,DIM>   Type;
      static const ArrayKernelName _VForm=__system_vec_type<DIM>::NAME;

    private:

      Array<InteractionFunction<GT,DIM>>  _Function;
      Array2D<UInt>                       _ID;
      Array<InteractionParameter>         _Parameter;
      GT                                  _Geo;
      access_ptr<double>                  _Energy;
      Array2D<Double,ArrayKernelName::SSE,_VForm>
                                          _Gradient;

      bool __is_same_frame(const Type& SI) {
        assert((bool)(*this));
        assert((bool)SI);
        if(_Function.size()!=SI._Function.size())   return false;
        for(unsigned int i=0;i<_Function.size();++i)
          if(_Function[i].Name()!=SI._Function[i].Name()) return false;
        if(_Gradient.size()!=SI._Gradient.size()) return false;
        return true;
      }

    public:

      SystemInteraction()
        : _Function(), _ID(), _Parameter(), _Geo(), _Energy(), _Gradient() {}
      SystemInteraction(const Type& SI) : SystemInteraction() {
        imprint(SI);  operator=(SI);
      }
      SystemInteraction(Type&& SI) : SystemInteraction() { swap(SI); }
      ~SystemInteraction() { reset(); }

      operator bool() const {
        return (bool)_Function && (bool)_ID && (bool)_Parameter &&
               (bool)_Geo && (bool)_Energy && (bool)_Gradient &&
               _Function.size() == _ID.size() &&
               _Function.size() == _Parameter.size();
      }
      double Energy() const { assert((bool)_Energy); return *_Energy; }
      const Array2D<Double,ArrayKernelName::SSE,_VForm>& Gradient() const {
        assert((bool)_Gradient); return _Gradient;
      }
      InteractionFunction<GT,DIM>& Function(unsigned int n) {
        assert((bool)_Function);
        return _Function[n];
      }
      InteractionFunction<GT,DIM> const& Function(unsigned int n) const {
        assert((bool)_Function);
        return _Function[n];
      }
      Array<UInt>& ID(unsigned int n) { assert((bool)_ID); return _ID[n]; }
      Array<UInt> const& ID(unsigned int n) const {
        assert((bool)_ID); return _ID[n];
      }
      InteractionParameter& Parameter(unsigned int n) {
        assert((bool)_Parameter);
        return _Parameter[n];
      }
      InteractionParameter const& Parameter(unsigned int n) const {
        assert((bool)_Parameter);
        return _Parameter[n];
      }
      GT& Geometry() { assert((bool)_Geo); return _Geo; }
      GT const& Geometry() const { assert((bool)_Geo); return _Geo; }
      void reset() {
        _Gradient.reset();
        _Energy.reset();
        _Geo.reset();
        _Parameter.reset();
        _ID.reset();
        _Function.reset();
      }

      Type& operator=(const Type& SI) {
        assert((bool)(*this));
        assert((bool)SI);
        assert(__is_same_frame(SI));
        _Function=SI._Function;
        _ID=SI._ID;
        _Parameter=SI._Parameter;
        _Geo=SI._Geo;
        *_Energy=*(SI._Energy);
        _Gradient=SI._Gradient;
        return *this;
      }

      void allocate(Array<InteractionName> & IN) {
        reset();
        _Function.imprint_structure(IN);
        for(unsigned int i=0;i<_Function.size();++i)
          _Function[i].allocate(IN[i]);
        Array<UInt> SZ(IN.size());
        for(unsigned int i=0;i<SZ.size();++i) SZ[i]=__id_size_of(IN[i]);
        _ID.allocate(SZ);
        SZ.reset();
        _Parameter.imprint_structure(IN);
        for(unsigned int i=0;i<_Parameter.size();++i)
          _Parameter[i].allocate(IN[i]);
        _Geo.allocate();
      }
      template <typename T1,ArrayKernelName DK,ArrayKernelName LK>
      void imprint_gradient_energy(Array2D<T1,DK,LK> const& X) {
        _Gradient.imprint_structure(X);
        _Energy.reset(new double,__delete_unit<double>);
      }
      void imprint(const Type& SI) {
        assert((bool)SI);
        Array<InteractionName> IN(SI._Function.size());
        for(unsigned int i=0;i<IN.size();++i)
          IN[i]=SI._Function[i].Name();
        allocate(IN);
        imprint_gradient_energy(SI._Gradient);
      }

      void ClearStatus() {
        assert((bool)_Function);
        for(unsigned int i=0;i<_Function.size();++i) 
          _Function[i].ClearStatus();
      }
      void UpdateEnergy(Array2D<Double,ArrayKernelName::SSE,_VForm> const& X) {
        assert((bool)X);
        assert((bool)(*this));
        *_Energy = 0;
        for(unsigned int i=0;i<_Function.size();++i)
          _Function[i].E(X,_ID[i],_Parameter[i],_Geo,*_Energy);
      }
      void UpdateGradient(
          Array2D<Double,ArrayKernelName::SSE,_VForm> const& X) {
        assert((bool)X);
        assert((bool)(*this));
        _Gradient = 0;
        for(unsigned int i=0;i<_Function.size();++i)
          _Function[i].G(X,_ID[i],_Parameter[i],_Geo,_Gradient);
      }
      void UpdateEnergyGradient(
          Array2D<Double,ArrayKernelName::SSE,_VForm> const& X) {
        assert((bool)X);
        assert((bool)(*this));
        *_Energy = 0;
        _Gradient = 0;
        for(unsigned int i=0;i<_Function.size();++i)
          _Function[i].EG(X,_ID[i],_Parameter[i],_Geo,*_Energy,_Gradient);
      }

      void swap(Type& SI) {
        std::swap(_Function,SI._Function);
        std::swap(_ID,SI._ID);
        std::swap(_Parameter,SI._Parameter);
        std::swap(_Geo,SI._Geo);
        std::swap(_Energy,SI._Energy);
        std::swap(_Gradient,SI._Gradient);
      }

  };

  template <typename GT,unsigned int DIM>
  void __imprint(SystemInteraction<GT,DIM>& SI,
                 SystemInteraction<GT,DIM> const& ISI) {
    SI.imprint(ISI);
  }

}

namespace std {

  template <typename GT,unsigned int DIM>
  void swap(mysimulator::SystemInteraction<GT,DIM>& SIA,
            mysimulator::SystemInteraction<GT,DIM>& SIB) {
    SIA.swap(SIB);
  }

}

#endif

