
#ifndef _Dynamics_Algorithm_VelocityVerlet_Data_Interface_H_
#define _Dynamics_Algorithm_VelocityVerlet_Data_Interface_H_

namespace mysimulator {

  template <typename T, template<typename> class VT>
  struct DynamicsVVerletData {

    public:

      typedef DynamicsVVerletData<T,VT>   Type;

      VT<T> NegHTIM;

      DynamicsVVerletData() : NegHTIM() {}
      ~DynamicsVVerletData() { clearData(); }

      void clearData() { release(NegHTIM); }
      bool isvalid() const { return true; }

    private:

      DynamicsVVerletData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, template<typename> class VT>
  void release(DynamicsVVerletData<T,VT>& D) { D.clearData(); }

  template <typename T, template<typename> class VT>
  bool IsValid(const DynamicsVVerletData<T,VT>& D) { return D.isvalid(); }

}

#endif

