
#ifndef _Matrix_Triangle_H_
#define _Matrix_Triangle_H_

#include "matrix-rectangle.h"
#include "util.h"

namespace std {
  enum TriangleMatrixFlag {
    UnknownPart=-1,
    UpperPart,
    LowerPart,
    UnknownSym=-1,
    NoSymmetry,
    Symmetric
  };
  template <typename T>
  class triangMatrix : public MatrixBase<T> {
    protected:
      int HalfPart;
      int SymFlag;
      T OtherObj;
    public:
      typedef T   DataType;
      typedef triangMatrix<T>   Type;
      typedef MatrixBase<T>     ParentType;
      triangMatrix()
        : ParentType(), HalfPart(UnknownPart), SymFlag(NoSymmetry) {}
      triangMatrix(const unsigned int N, int Ord=COrder, int Trans=Original,
                   int SF=NoSymmetry, int Hf=UpperPart) {
        allocate(N,Ord,Trans,SF,Hf);
        if(SymFlag==NoSymmetry) Nullify(OtherObj);
      }
      virtual ~triangMatrix() { HalfPart=UnknownPart; SymFlag=UnknownSym; }
      Type& operator=(const Type& TM) {
        if(SymFlag!=TM.SymFlag)
          myError("Cannot copy from triangle matrix with different symmetry");
        int oSymFlag=SymFlag;
        SetSymmetry(Symmetric);
        TM.SetSymmetry(Symmetric);
        unsigned int n=dimension();
        for(unsigned int i=0;i<n;++i)
        for(unsigned int j=i;j<n;++j)
          this->operator()(i,j)=TM(i,j);
        SetSymmetry(oSymFlag);
        TM.SetSymmetry(oSymFlag);
        if(SymFlag==NoSymmetry) OtherObj=TM.OtherObj;
        return *this;
      }
      Type& operator=(const rectMatrix<T>& RM) {
        myError("Cannot copy from rectangle matrix");
        return *this;
      }
      template <typename inputT>
      Type& operator=(const inputT& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }
      const unsigned int& dimension() const;
      void SetSymmetry(const int SF);
      void clear();
      void allocate(unsigned int N, int Ord=COrder, int Trans=Original,
                    int SF=NoSymmetry, int Hf=UpperPart);
      virtual const char* type();
  };
}

#endif

