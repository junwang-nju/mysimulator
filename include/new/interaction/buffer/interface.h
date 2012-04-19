
#ifndef _Interaction_Buffer_Interface_H_
#define _Interaction_Buffer_Interface_H_

#include "array/1d/interface.h"
#include "array/2d/interface.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  struct InteractionBuffer {

    public:

      typedef InteractionBuffer<T>    Type;
      typedef void (*P2PFuncType)(const T*,const Unique64Bit*,T*,bool&);
      typedef void (*GetPreFuncType)(Type*,const int*,T*);

      Array1D<T>      pre;
      Array1D<T>      post;
      Array2D<T>      tmvec;
      Array1D<int>    inf;
      bool            postUpdate;
      P2PFuncType     P2PFunc,P2PDiff,P2PBoth;
      GetPreFuncType  GetPreFunc,GetPreDiff,GetPreBoth;

      InteractionBuffer()
        : pre(), post(), tmvec(), inf(), postUpdate(true), P2PFunc(NULL),
          P2PDiff(NULL), P2PBoth(NULL), GetPreFunc(NULL), GetPreDiff(NULL),
          GetPreBoth(NULL) {}
      ~InteractionBuffer() { clearData(); }

      bool isvalid() const {
        return IsValid(pre)&&IsValid(post)&&IsValid(tmvec)&&
               (P2PFunc!=NULL)&&(P2PDiff!=NULL)&&(P2PBoth!=NULL);
      }
      void clearData() {
        release(inf); release(tmvec); release(post); release(pre);
        postUpdate=true; P2PFunc=NULL; P2PDiff=NULL; P2PBoth=NULL;
        GetPreFunc=NULL; GetPreDiff=NULL; GetPreBoth=NULL;
      }

      void clearFlag() { postUpdate=true; }

    private:

      InteractionBuffer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const InteractionBuffer<T>& B) { return B.isvalid(); }

  template <typename T>
  void release(InteractionBuffer<T>& B) { B.clearData(); }

}

#endif

