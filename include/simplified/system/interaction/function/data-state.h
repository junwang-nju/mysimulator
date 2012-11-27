
#ifndef _System_Interaction_Function_Data_State_H_
#define _System_Interaction_Function_Data_State_H_

namespace mysimulator {

  class InteractionFuncDataState {

    public:

      typedef InteractionFuncDataState  Type;

    private:

      bool _E_OK;
      bool _G_OK;
      bool _H_OK;

    public:

      InteractionFuncDataState() : _E_OK(false),_G_OK(false),_H_OK(false) {}
      InteractionFuncDataState(const Type& S)
        : _E_OK(S._E_OK), _G_OK(S._G_OK), _H_OK(S._H_OK) {}
      ~InteractionFuncDataState() { reset(); }

      operator bool() const { return true; }
      bool IsReady4Energy() const { return _E_OK; }
      bool IsReady4Gradient() const { return _G_OK; }
      bool IsReady4Hessian() const { return _H_OK; }
      bool IsReady4EnergyGradient() const { return _E_OK && _G_OK; }
      bool IsReady4EnergyHessian() const { return _E_OK && _H_OK; }
      bool IsReady4GradientHessian() const { return _G_OK && _H_OK; }
      void reset() { _E_OK=false; _G_OK=false; _H_OK=false; }

      Type& operator=(const Type& S) {
        _E_OK=S._E_OK;  _G_OK=S._G_OK;  _H_OK=S._H_OK;
        return *this;
      }

      void SetReady4Energy() { _E_OK=true; }
      void SetReady4Gradient() { _G_OK=true; }
      void SetReady4Hessian() { _H_OK=true; }
      void SetReady4EnergyGradient() { _E_OK=true; _G_OK=true; }
      void SetReady4EnergyHessian() { _E_OK=true; _H_OK=true; }
      void SetReady4GradientHessian() { _G_OK=true; _H_OK=true; }

      void swap(InteractionFuncDataState& S) {
        std::swap(_E_OK,S._E_OK);
        std::swap(_G_OK,S._G_OK);
        std::swap(_H_OK,S._H_OK);
      }

  };

}

namespace std {

  void swap(mysimulator::InteractionFuncDataState& SA,
            mysimulator::InteractionFuncDataState& SB) { SA.swap(SB); }

}

#endif

