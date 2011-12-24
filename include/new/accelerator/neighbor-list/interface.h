
#ifndef _Accelerator_NeighborList_Interface_H_
#define _Accelerator_NeighborList_Interface_H_

namespace mysimulator {

  template <typename T>
  struct NeighborList {

    public:

      typedef NeighborList<T>   Type;

      T CutRadius;
      T InteractionCutRadius;
      T BufferRadius;
      T UpdateTime;

      NeighborList()
        : CutRadius(0), InteractionCutRadius(0), BufferRadius(0),
          UpdateTime(0) {}
      ~NeighborList() { clearData(); }

      void clearData() {
        CutRadius=0; InteractionCutRadius=0; BufferRadius=0; UpdateTime=0;
      }
      bool isvalid() const { return true; }

    private:

      NeighborList(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(NeighborList<T>& L) { L.clearData(); }

  template <typename T>
  bool IsValid(const NeighborList<T>& L) { return L.isvalid(); }

}

#endif

