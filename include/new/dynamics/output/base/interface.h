
#ifndef _Dynamics_Output_Base_Interface_H_
#define _Dynamics_Output_Base_Interface_H_

namespace mysimulator {

  template <typename OutputStreamType,typename T>
  struct DynOutputBase {

    public:

      typedef DynOutputBase<OutputStreamType,T>   Type;

      OutputStreamType OS;
      T TimeBwOutput;
      unsigned int NumStepsBwOutput;
      bool IsFirstOutput;

      DynOutputBase() : OS(), TimeBwOutput(0), NumStepsBwOutput(0),
                        IsFirstOutput(true) {}
      ~DynOutputBase() { clearData(); }

      void clearData() { release(OS); TimeBwOutput=0; NumStepsBwOutput=0; }
      bool isvalid() const { return IsValid(OS)&&(NumStepsBwOutput>0); }

      virtual void write() = 0;

      void updateNumStepsBwOutput(const T& dt) {
        NumStepsBwOutput=static_cast<unsigned int>(TimeBwOutput/dt+0.5);
      }
      void updateTimeBwOutput(const T& dt) {
        TimeBwOutput=dt*NumStepsBwOutput;
      }

    private:

      DynOutputBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename OST,typename T>
  void release(DynOutputBase<OST,T>& O) { O.clearData(); }

  template <typename OST,typename T>
  bool IsValid(const DynOutputBase<OST,T>& O) { return O.isvalid(); }

}

#endif

