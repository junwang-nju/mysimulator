
#ifndef _Dynamics_Canonical_Berendsen_Base_Data_Interface_H_
#define _Dynamics_Canonical_Berendsen_Base_Data_Interface_H_

namespace mysimulator {

  template <typename T,template<typename>class VT>
  struct DynamicsCanonicalBerendsenBaseData {

    public:

      typedef DynamicsCanonicalBerendsenBaseData<T,VT>  Type;

      T RelaxTime;
      VT<T> VelocitySQ;

      DynamicsCanonicalBerendsenBaseData() : RelaxTime(0), VelocitySQ() {}
      ~DynamicsCanonicalBerendsenBaseData() { clearData(); }

      void clearData() { release(VelocitySQ); RelaxTime=0; }
      bool isvalid() const { return true; }

    private:

      DynamicsCanonicalBerendsenBaseData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename>class VT>
  void release(DynamicsCanonicalBerendsenBaseData<T,VT>& D) { D.clearData(); }

  template <typename T,template<typename>class VT>
  void IsValid(const DynamicsCanonicalBerendsenBaseData<T,VT>& D) {
    return D.isvalid();
  }

  template <typename T>
  struct DynamicsCanonicalBerendsenBaseData4EnergyOut {

    public:

      typedef DynamicsCanonicalBerendsenBaseData4EnergyOut<T>  Type;

      T RelaxTime;

      DynamicsCanonicalBerendsenBaseData4EnergyOut() : RelaxTime(0) {}
      ~DynamicsCanonicalBerendsenBaseData4EnergyOut() { clearData(); }

      void clearData() { RelaxTime=0; }
      bool isvalid() const { return true; }

    private:

      DynamicsCanonicalBerendsenBaseData4EnergyOut(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(DynamicsCanonicalBerendsenBaseData4EnergyOut<T>& D) {
    D.clearData();
  }

  template <typename T>
  bool IsValid(const DynamicsCanonicalBerendsenBaseData4EnergyOut<T>& D) {
    return D.isvalid();
  }

}

#endif

