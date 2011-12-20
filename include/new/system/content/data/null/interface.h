
#ifndef _System_Content_Data_Null_Interface_H_
#define _System_Content_Data_Null_Interface_H_

namespace mysimulator {

  struct SysContentDataNull {

    public:

      typedef SysContentDataNull  Type;

      SysContentDataNull() {}
      ~SysContentDataNull() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

    private:

      SysContentDataNull(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(SysContentDataNull& D) { D.clearData(); }
  bool IsValid(const SysContentDataNull& D) { return D.isvalid(); }

}

#endif

