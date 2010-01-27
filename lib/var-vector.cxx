
#include "var-vector.h"

namespace std {

  template <typename T>
  void varVector<T>::clear() {
    safe_delete(this->data());
    static_cast<ParentType*>(this)->clear();
  }

  template <typename T>
  void varVector<T>::allocate(const unsigned int N) {
    static_cast<ParentType*>(this)->RefList().clear();
    if(this->size()!=N) {
      safe_delete(this->data());
      this->data()=new T[N];
      this->SetSize(N);
      this->SetHeadTail();
    }
  }

  template <typename T>
  const char* varVector<T>::type() const { return "Variable Vector"; }

}

