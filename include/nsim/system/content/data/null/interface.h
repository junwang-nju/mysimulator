
#ifndef _System_Content_Data_Null_Interface_H_
#define _System_Content_Data_Null_Interface_H_

namespace mysimulator {

  template <typename T>
  struct SystemContentDataNull {

    public:

      typedef SystemContentDataNull<T>  Type;

      SystemContentDataNull() {}
      ~SystemContentDataNull() { Clear(); }

      void Clear() {}
      bool IsValid() const { return true; }

      void Allocate() { fprintf(stderr,"Not Necessary!\n"); }
      void Allocate(const Array2D<T>&) { fprintf(stderr,"Not Necessary!\n"); }
      void Refer(const Type&) {}
      void Refer(const Type&,unsigned int,unsigned int) {}

    private:

      SystemContentDataNull(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

