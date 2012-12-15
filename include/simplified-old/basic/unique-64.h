
#ifndef _Basic_Unique_64Bit_H_
#define _Basic_Unique_64Bit_H_

namespace mysimulator {

  union Unique {

    public:

      typedef Unique  Type;

    private:

      double d;
      float f;
      long long ll;
      unsigned long long ull;
      int i;
      unsigned int u;
      long l;
      unsigned long ul;
      short s;
      unsigned short us;
      char c;
      unsigned char uc;
      void* ptr;

    public:

      Unique() : ull(0) {}
      Unique(const unsigned long long& iull) : ull(iull) {}
      Unique(const double& d) : Unique(*reinterpret_cast<const double*>(&d)) {}
      Unique(const Unique& U) : Unique(U.ull) {}
      ~Unique() { reset(); }

      operator double() const { return d; }
      operator float() const { return f; }
      operator unsigned long long() const { return ull; }
      operator long long() const { return ll; }
      operator unsigned int() const { return u; }
      operator int() const { return i; }
      operator unsigned long() const { return ul; }
      operator long() const { return l; }
      operator unsigned short() const { return us; }
      operator short() const { return s; }
      operator unsigned char() const { return uc; }
      operator char() const { return c; }
      operator void*() const { return ptr; }
      template <typename T>
      operator const T*() const { return (const T*)ptr; }

      Type& operator=(const Type& U) { ull=U.ull; return *this; }

      void reset() { ull=0; }

  };

}

#endif

