
#ifndef _Chain_Node_Interface_H_
#define _Chain_Node_Interface_H_

#include "object/interface.h"

namespace mysimulator {

  template <typename T>
  struct ChainNode {

    public:

      typedef ChainNode<T>   Type;

      Type* parent;
      Type* child;
      Object<T> content;

      ChainNode() : parent(NULL), child(NULL), content() {}
      ~ChainNode() { clearData(); }

      void clearData() { parent=NULL; child=NULL; release(content); }
      bool isvalid() const { return IsValid(content); }

    private:

      ChainNode(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const ChainNode<T>& N) { return N.isvalid(); }

  template <typename T>
  void release(ChainNode<T>& N) { N.clearData(); }

}

#endif

