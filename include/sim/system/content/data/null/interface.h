
#ifndef _System_Content_Data_Null_Interface_H_
#define _System_Content_Data_Null_Interface_H_

namespace mysimulator {

  struct SystemContentDataNull {

    public:

      typedef SystemContentDataNull   Type;

      SystemContentDataNull() {}
      ~SystemContentDataNull() {}

      void clearData() {}
      bool isvalid() const { return true; }

    private:

      SystemContentDataNull(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(SystemContentDataNull&) {}
  bool IsValid(const SystemContentDataNull&) { return true; }

}

#endif

