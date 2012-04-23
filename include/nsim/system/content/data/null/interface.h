
#ifndef _System_Content_Data_Null_Interface_H_
#define _System_Content_Data_Null_Interface_H_

namespace mysimulator {

  template <typename T>
  struct SystemContentDataNull {

    public:

      typedef SystemContentDataNull<T>  Type;

      SystemContentDataNull() {}
      ~SystemContentDataNull() { Clear(*this); }

      bool IsValid() const { return true; }

      void Allocate() {}
      void Allocate(const Array2D<T>&) {}
      void Refer(Type&) {}
      void Refer(Type&,unsigned int,unsigned int) {}

    private:

      SystemContentDataNull(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentDataNull<T>&) {}

}

#endif

