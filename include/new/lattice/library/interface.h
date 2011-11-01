
#ifndef _Lattice_Library_Interface_H_
#define _Lattice_Library_Interface_H_

#include "lattice/node/coordinate/create.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"
#include "lattice/mesh/interface.h"
#include "array/1d/io.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeLibrary {
    public:

      typedef typename LatticeNodeCoordinate<LSN,Dim>::Type CoorType;

      struct NodeType {
        public:
          int Depth;
          CoorType Pos;
          NodeType* parent;
          NodeType* child;
          NodeType() : Depth(-1), Pos(), parent(NULL), child(NULL) {}
          ~NodeType() { clearData(); }
          void clearData() {
            Depth=-1;
            Pos.nullify();
            parent=NULL;
            delete_array(child);
          }
        private:
          NodeType(const NodeType&) {}
          NodeType& operator=(const NodeType&) {}

      };

      typedef LatticeLibrary<LSN,Dim>   Type;

      static const unsigned int MaxDepth;
      static const unsigned int NumChildren;

      static NodeType *root;

      LatticeLibrary() {}
      ~LatticeLibrary() { clearData(); }

      static void load() {
        if(IsValid(root)) return;
        unsigned int level;
        Array1D<int> Branch;
        Array1D<bool> Valid;
        allocate(Branch,1U,MaxDepth);
        allocate(Valid,MaxDepth);
        fill(Branch,-1);
        fill(Valid,false);
        NodeType *now,*run;
        LatticeMesh<LSN,Dim> M;
        M.nullify();
        root=new NodeType;
        root->Pos.nullify();
        level=0;
        now=root;
        while(true) {
          if(!(M.occupied(now->Pos))) {
            now->Depth=0;
            run=now;
            while(run->parent!=NULL) {
              if(run->parent->Depth<run->Depth+1)
                run->parent->Depth=run->Depth+1;
              run=run->parent;
            }
            if(level<MaxDepth) {
              M.set_occupied(now->Pos);
              Valid[level]=true;
              now->child=new NodeType[NumChildren];
              for(unsigned int i=0;i<NumChildren;++i) now->child[i].parent=now;
              level++;
              now=now->child;
            }
          }
          Branch[level]++;
          while(Branch[level]>=static_cast<int>(NumChildren)) {
            Branch[level]=-1;
            level--;
            now=now->parent;
            if(!Valid[level]) delete_array(now->child);
            if(level==0) break;
            M.remove_occupied(now->Pos);
            Branch[level]++;
          }
          if(level==0) break;
          now=now->parent->child+Branch[level];
          create<LSN,Dim>(now->parent->Pos,Branch[level],now->Pos);
        }
        release(Valid);
        release(Branch);
      }

      void clearData() { delete_pointer(root); }
      bool isvalid() const { return IsValid(root); }

  };

  template <LatticeShapeName LSN, unsigned int Dim>
  void release(LatticeLibrary<LSN,Dim>& L) { L.clearData(); }

  template <LatticeShapeName LSN, unsigned int Dim>
  bool IsValid(const LatticeLibrary<LSN,Dim>& L) { return L.isvalid(); }

  template <LatticeShapeName LSN, unsigned int Dim>
  const unsigned int LatticeLibrary<LSN,Dim>::MaxDepth=0;

}

#include "lattice/node/neighbor/number.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  const unsigned int LatticeLibrary<LSN,Dim>::NumChildren=
    NumNeighbors<LSN,Dim>();

  template <LatticeShapeName LSN, unsigned int Dim>
  typename LatticeLibrary<LSN,Dim>::NodeType *LatticeLibrary<LSN,Dim>::root=
    NULL;

}

#include "lattice/library/square/2d/specification.h"
#include "lattice/library/square/3d/specification.h"

#endif

