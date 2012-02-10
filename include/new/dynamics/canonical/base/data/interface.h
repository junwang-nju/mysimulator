
#ifndef _Dynamics_Canonical_Base_Data_Interface_H_
#define _Dynamics_Canonical_Base_Data_Interface_H_

namespace mysimulator {

  template <typename T>
  struct DynamicsCanonicalBaseData {

    public:

      typedef DynamicsCanonicalBaseData<T>    Type;

      T Temperature;

      DynamicsCanonicalBaseData() : Temperature(0) {}
      ~DynamicsCanonicalBaseData() { clearData(); }

      void clearData() { Temperature=0; }
      bool isvalid() const { return true; }

    private:

      DynamicsCanonicalBaseData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(DynamicsCanonicalBaseData<T>& D) { D.clearData(); }

  template <typename T>
  bool IsValid(const DynamicsCanonicalBaseData<T>& D) { return D.isvalid(); }

}

#endif

