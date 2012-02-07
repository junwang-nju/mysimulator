
#ifndef _Dynamics_Canonical_Langevin_VelocityVerlet_Data_Interface_H_
#define _Dynamics_Canonical_Langevin_VelocityVerlet_Data_Interface_H_

namespace mysimulator {

  template <typename T, template<typename> class VT>
  struct DynamicsCanonicalLangevinVVerletData {

    public:

      typedef DynamicsCanonicalLangevinVVerletData<T,VT>  Type;

      VT<T> Fac1;
      VT<T> Fac2;

      DynamicsCanonicalLangevinVVerletData() : Fac1(), Fac2() {}
      ~DynamicsCanonicalLangevinVVerletData() { clearData(); }

      void clearData() { release(Fac1); release(Fac2); }
      bool isvalid() const { return true; }

    private:

      DynamicsCanonicalLangevinVVerletData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(DynamicsCanonicalLangevinVVerletData<T,VT>& D) {
    D.clearData();
  }

  template <typename T, template<typename> class VT>
  bool IsValid(const DynamicsCanonicalLangevinVVerletData<T,VT>& D) {
    return D.isvalid();
  }

}

#endif

