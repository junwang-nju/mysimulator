
#ifndef _Dynamics_Canonical_Langevin_Base_Data_Interface_H_
#define _Dynamics_Canonical_Langevin_Base_Data_Interface_H_

namespace mysimulator {

  template <typename T,template<typename> class VT, typename RNGType>
  struct DynamicsCanonicalLangevinBaseData {

    public:

      DynamicsCanonicalLangevinBaseData<T,VT>   Type;

      VT<T> Friction;
      VT<T> RandSize;
      VT<T> RandV;
      RNGType rng;

      DynamicsCanonicalLangevinBaseData()
        : Friction(), RandSize(), RandV(), rng() {}
      ~DynamicsCanonicalLangevinBaseData() { clearData(); }

      void clearData() {
        release(Friction); release(RandSize); release(RandV); release(rng);
      }
      bool isvalid() const { return true; }

    private:

      DynamicsCanonicalLangevinBaseData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename>class VT,typename RT>
  void release(DynamicsCanonicalLangevinBaseData<T,VT,RT>& D) { D.clearData(); }

  template <typename T,template<typename>class VT,typename RT>
  bool IsValid(const DynamicsCanonicalLangevinBaseData<T,VT,RT>& D) {
    return D.isvalid();
  }

}

#endif

