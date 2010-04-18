
#ifndef _Matrix_Triangle_H_
#define _Matrix_Triangle_H_

#include "matrix-base.h"
#include "matrix-format-id.h"
#include "matrix-data-order-id.h"
#include "matrix-transpose-id.h"
#include "matrix-symmetry-id.h"
#include "var-vector.h"
#include "ref-vector.h"

namespace std {

  template <typename T, template<typename> class VecType>
  static T& getCDUSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI>rJ) { rI=J; rJ=I; }
    return Ls[rI][rJ-rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getCDUNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI>rJ) return Other;
    return Ls[rI][rJ-rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getCDLSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI<rJ) { rI=J; rJ=I; }
    return Ls[rI][rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getCDLNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI<rJ) return Other;
    return Ls[rI][rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getCNUSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI>rJ) { rI=J; rJ=I; }
    return Ls[rI][rJ-rI-1];
  }

  template <typename T, template<typename> class VecType>
  static T& getCNUNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI>rJ) return Other;
    return Ls[rI][rJ-rI-1];
  }

  template <typename T, template<typename> class VecType>
  static T& getCNLSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI<rJ) { rI=J; rJ=I; }
    return Ls[rI-1][rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getCNLNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI<rJ) return Other;
    return Ls[rI-1][rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getFDUSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI>rJ) { rI=J; rJ=I; }
    return Ls[rJ][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getFDUNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI>rJ) return Other;
    return Ls[rJ][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getFDLSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI<rJ) { rI=J; rJ=I; }
    return Ls[rJ][rI-rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getFDLNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI<rJ) return Other;
    return Ls[rJ][rI-rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getFNUSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI>rJ) { rI=J; rJ=I; }
    return Ls[rJ-1][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getFNUNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI>rJ) return Other;
    return Ls[rJ-1][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getFNLSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI<rJ) { rI=J; rJ=I; }
    return Ls[rJ][rI-1];
  }

  template <typename T, template<typename> class VecType>
  static T& getFNLNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI<rJ) return Other;
    return Ls[rJ][rI-1];
  }

  template <typename T, template<typename> class VecType>
  static T& getDDUSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI>rJ) { rI=J; rJ=I; }
    return Ls[rJ-rI][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getDDUNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI>rJ) return Other;
    return Ls[rJ-rI][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getDDLSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI<rJ) { rI=J; rJ=I; }
    return Ls[rI-rJ][rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getDDLNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    unsigned int rI=I,rJ=J;
    if(rI<rJ) return Other;
    return Ls[rI-rJ][rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getDNUSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI>rJ) { rI=J; rJ=I; }
    return Ls[rJ-rI-1][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getDNUNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI>rJ) return Other;
    return Ls[rJ-rI-1][rI];
  }

  template <typename T, template<typename> class VecType>
  static T& getDNLSData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI<rJ) { rI=J; rJ=I; }
    return Ls[rI-rJ-1][rJ];
  }

  template <typename T, template<typename> class VecType>
  static T& getDNLNData(VecType<refVector<T> >& Ls, unsigned int I,
                       unsigned int J, T& Other) {
    if(I==J)  return Other;
    unsigned int rI=I,rJ=J;
    if(rI<rJ) return Other;
    return Ls[rI-rJ-1][rJ];
  }

  enum TriangleInfoItems {
    TriangleDimension=NumberCommonItems,
    DiagonalFlag,
    SymmetryFlag,
    TrianglePart,
    ActualTrianglePart,
    DataPattern,
    TriangleNumberItems
  };

  enum DiagonalExistedType {
    UnknownDiagonalState=-1,
    NullDiagonal,
    WithDiagonal
  };

  enum TrianglePartType {
    UnknownTrianglePart=-1,
    UpperPart,
    LowerPart
  };

  enum TriangleDataPatternType {
    UnknownPattern=-1,
    DiagType,
    CUppType,
    FUppType
  };

  template <template <typename> class iVecType>
  struct TriMatTypeOp {
    const char* operator()() const { return "Triangle Matrix"; }
  };

  template <>
  struct TriMatTypeOp<varVector> {
    const char* operator()() const { return "Variable Triangle Matrix"; }
  };

  template <>
  struct TriMatTypeOp<refVector> {
    const char* operator()() const { return "Reference Triangle Matrix"; }
  };

  template <typename T, template <typename> class VecType>
  class TriangMatrix
    : public MatrixBase<T,Triangle,VecType,TriangleNumberItems> {

    public:

      typedef TriangMatrix<T,VecType>   Type;

      typedef MatrixBase<T,Triangle,VecType,TriangleNumberItems>  ParentType;

      static const bool IsTriangleMatrix;

      TriangMatrix() : ParentType() {}

      TriangMatrix(const unsigned int Dim, const int Order=COrder,
                   const int Trans=NoTranspose,
                   const int Tripart=UpperPart,
                   const bool SymFlag=true, const bool DiagFlag=true)
        : ParentType() {
        allocate(Dim,Order,Trans,Tripart,SymFlag,DiagFlag);
      }

      TriangMatrix(const Type& TMB) {
        myError("Cannot create from triangle matrix");
      }

      virtual ~TriangMatrix() {}

      Type& operator=(const Type& TMB) {
        assert(this->IsSymmetry()==TMB.IsSymmetry());
        assert(this->IsDiagonalExisted()==TMB.IsDiagonalExisted());
        if(this->IsSymmetry())
          assert(MatrixDataPattern()==TMB.MatrixDataPattern());
        else {
          assert(this->MatrixActualOrder()==TMB.MatrixActualOrder());
          assert(this->MatrixActualTrianglePart()==
                 TMB.MatrixActualTrianglePart());
        }
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(TMB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const TriangMatrix<T,iVecType>& TMB) {
        assert(this->IsSymmetry()==TMB.IsSymmetry());
        assert(this->IsDiagonalExisted()==TMB.IsDiagonalExisted());
        if(this->IsSymmetry())
          assert(MatrixDataPattern()==TMB.MatrixDataPattern());
        else {
          assert(this->MatrixActualOrder()==TMB.MatrixActualOrder());
          assert(this->MatrixActualTrianglePart()==
                 TMB.MatrixActualTrianglePart());
        }
        static_cast<ParentType*>(this)->operator=(
            static_cast<const MatrixBase<T,Triangle,iVecType,
                                         TriangleNumberItems>&>(TMB));
        return *this;
      }

      Type& operator=(const VectorBase<T>& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }

      Type& operator=(const T& D) {
        static_cast<ParentType*>(this)->operator=(D);
        return *this;
      }

      const unsigned int ActualDimension() const {
        return this->info()[TriangleDimension]; }

      void SetActualDimension(const unsigned int AD) {
        this->info()[TriangleDimension]=AD;
      }

      const bool IsSymmetry() const {
        return this->info()[SymmetryFlag]==WithSymmetry;
      }

      void SetSymmetryFlag(const bool sflag) {
        this->info()[SymmetryFlag]=(sflag?WithSymmetry:NoSymmetry);
      }

      const bool IsDiagonalExisted() const {
        return this->info()[DiagonalFlag]==WithDiagonal;
      }

      void SetDiagonalState(const bool dflag) {
        this->info()[DiagonalFlag]=(dflag?WithDiagonal:NullDiagonal);
      }

      const unsigned int MatrixTrianglePart() const {
        return this->info()[TrianglePart];
      }

      void SetTrianglePart(const int ulstate) {
        this->info()[TrianglePart]=ulstate;
      }

      const unsigned int MatrixActualTrianglePart() const {
        return this->info()[ActualTrianglePart];
      }

      void SetActualTrianglePart(const int ulstate) {
        this->info()[ActualTrianglePart]=ulstate;
      }

      const unsigned int MatrixDataPattern() const {
        return this->info()[DataPattern];
      }

      void SetDataPattern(const int Pattern) {
        this->info()[DataPattern]=Pattern;
      }

      const unsigned int Dimension() const { return this->NumRow(); }

    protected:

      void SetGetMethod() {
        assert(this->MatrixOrder()>=0);
        assert(this->MatrixTransposeState()>=0);
        assert(this->info()[SymmetryFlag]>=0);
        assert(this->info()[DiagonalFlag]>=0);
        assert(this->info()[TrianglePart]>=0);
        if(this->MatrixTransposeState()==NoTranspose) {
          this->SetActualOrder(this->MatrixOrder());
          SetActualTrianglePart(MatrixTrianglePart());
        }
        else if(this->MatrixTransposeState()==WithTranspose) {
          if(this->MatrixOrder()==COrder) this->SetActualOrder(FortranOrder);
          else if(this->MatrixOrder()==FortranOrder)
            this->SetActualOrder(COrder);
          else if(this->MatrixOrder()==DiagonalOrder)
            this->SetActualOrder(DiagonalOrder);
          else myError("matrix order is not proper");
          if(MatrixTrianglePart()==UpperPart)
            SetActualTrianglePart(LowerPart);
          else if(MatrixTrianglePart()==LowerPart)
            SetActualTrianglePart(UpperPart);
          else myError("unknown triangle part flag");
        } else myError("unknown mode of transpose state for matrix");
        if(this->MatrixActualOrder()==DiagonalOrder)
          SetDataPattern(DiagType);
        else if(this->MatrixActualOrder()==COrder) {
          if(this->MatrixActualTrianglePart()==UpperPart)
            SetDataPattern(CUppType);
          else if(this->MatrixActualTrianglePart()==LowerPart)
            SetDataPattern(FUppType);
          else myError("unknown triangle part flag");
        } else if(this->MatrixActualOrder()==FortranOrder) {
          if(this->MatrixActualTrianglePart()==UpperPart)
            SetDataPattern(FUppType);
          else if(this->MatrixActualTrianglePart()==LowerPart)
            SetDataPattern(CUppType);
          else myError("unknown triangle part flag");
        }
        if(this->MatrixActualOrder()==COrder) {
          if(IsDiagonalExisted()) {
            if(MatrixActualTrianglePart()==UpperPart) {
              if(IsSymmetry())  this->AssignGetMethod(getCDUSData<T,VecType>);
              else              this->AssignGetMethod(getCDUNData<T,VecType>);
            } else if(MatrixActualTrianglePart()==LowerPart) {
              if(IsSymmetry())  this->AssignGetMethod(getCDLSData<T,VecType>);
              else              this->AssignGetMethod(getCDLNData<T,VecType>);
            } else myError("unknow triangle part flag");
          } else {
            if(MatrixActualTrianglePart()==UpperPart) {
              if(IsSymmetry())  this->AssignGetMethod(getCNUSData<T,VecType>);
              else              this->AssignGetMethod(getCNUNData<T,VecType>);
            } else if(MatrixActualTrianglePart()==LowerPart) {
              if(IsSymmetry())  this->AssignGetMethod(getCNLSData<T,VecType>);
              else              this->AssignGetMethod(getCNLNData<T,VecType>);
            } else myError("unknow triangle part flag");
          }
        } else if(this->MatrixActualOrder()==FortranOrder) {
          if(IsDiagonalExisted()) {
            if(MatrixActualTrianglePart()==UpperPart) {
              if(IsSymmetry())  this->AssignGetMethod(getFDUSData<T,VecType>);
              else              this->AssignGetMethod(getFDUNData<T,VecType>);
            } else if(MatrixActualTrianglePart()==LowerPart) {
              if(IsSymmetry())  this->AssignGetMethod(getFDLSData<T,VecType>);
              else              this->AssignGetMethod(getFDLNData<T,VecType>);
            } else myError("unknow triangle part flag");
          } else {
            if(MatrixActualTrianglePart()==UpperPart) {
              if(IsSymmetry())  this->AssignGetMethod(getFNUSData<T,VecType>);
              else              this->AssignGetMethod(getFNUNData<T,VecType>);
            } else if(MatrixActualTrianglePart()==LowerPart) {
              if(IsSymmetry())  this->AssignGetMethod(getFNLSData<T,VecType>);
              else              this->AssignGetMethod(getFNLNData<T,VecType>);
            } else myError("unknow triangle part flag");
          }
        } else if(this->MatrixActualOrder()==DiagonalOrder) {
          if(IsDiagonalExisted()) {
            if(MatrixActualTrianglePart()==UpperPart) {
              if(IsSymmetry())  this->AssignGetMethod(getDDUSData<T,VecType>);
              else              this->AssignGetMethod(getDDUNData<T,VecType>);
            } else if(MatrixActualTrianglePart()==LowerPart) {
              if(IsSymmetry())  this->AssignGetMethod(getDDLSData<T,VecType>);
              else              this->AssignGetMethod(getDDLNData<T,VecType>);
            } else myError("unknow triangle part flag");
          } else {
            if(MatrixActualTrianglePart()==UpperPart) {
              if(IsSymmetry())  this->AssignGetMethod(getDNUSData<T,VecType>);
              else              this->AssignGetMethod(getDNUNData<T,VecType>);
            } else if(MatrixActualTrianglePart()==LowerPart) {
              if(IsSymmetry())  this->AssignGetMethod(getDNLSData<T,VecType>);
              else              this->AssignGetMethod(getDNLNData<T,VecType>);
            } else myError("unknow triangle part flag");
          }
        }
      }

      void SetStructure() {
        int n,d;
        if((this->MatrixDataPattern()==CUppType)||
           (this->MatrixDataPattern()==DiagType)) {
          n=this->ActualDimension();
          d=-1;
        } else if(this->MatrixDataPattern()==FUppType) {
          n=1;
          d=1;
        } else myError("improper data pattern for triangle matrix");
        for(unsigned int i=0,m=0;i<this->ActualDimension();++i,m+=n,n+=d)
          this->structure()[i].refer(this->data(),m,n);
      }

      struct AllocateOp {
        template <template <typename> class iVecType>
        void operator()(const unsigned int Dim, const int Order,
                        const int Trans, const int Tripart,
                        const bool SymFlag, const bool DiagFlag,
                        TriangMatrix<T,iVecType>& Self) {
          myError("Not Available");
        }
        void operator()(const unsigned int Dim, const int Order,
                        const int Trans, const int Tripart,
                        const bool SymFlag, const bool DiagFlag,
                        TriangMatrix<T,varVector>& Self) {
          Self.clear();
          Self.SetSize(Dim,Dim);
          Self.SetOrder(Order);
          Self.SetTransposeState(Trans);
          Self.SetTrianglePart(Tripart);
          Self.SetSymmetryFlag(SymFlag);
          Self.SetDiagonalState(DiagFlag);
          Self.SetGetMethod();
          if(Self.IsDiagonalExisted()) Self.SetActualDimension(Dim);
          else                         Self.SetActualDimension(Dim-1);
          int d=Self.ActualDimension();
          int n=(d*(d+1))/2;
          Self.data().allocate(n);
          Self.structure().allocate(d);
          Self.SetStructure();
        }
      };

      struct ReferOp {
        template <template <typename> class iVecType,
                  template <typename> class rVecType>
        void operator()(const TriangMatrix<T,iVecType>& TM,
                        TriangMatrix<T,rVecType>& Self) {
          myError("Not Available");
        }
        template <template <typename> class iVecType>
        void operator()(const TriangMatrix<T,iVecType>& TM,
                        TriangMatrix<T,refVector>& Self) {
          Self.data().refer(TM.data());
          Self.structure().refer(TM.structure());
          Self.info()=TM.info();
          Self.SetOtherElements(TM.OtherElements());
          Self.SetGetMethod();
        }
      };

      AllocateOp runAllocateOp;

      TriMatTypeOp<VecType> runTriMatTypeOp;

      ReferOp runReferOp;

    public:

      void allocate(const unsigned int Dim, const int Order=COrder,
                    const int Trans=NoTranspose, const int Tripart=UpperPart,
                    const bool SymFlag=true, const bool DiagFlag=true) {
        runAllocateOp(Dim,Order,Trans,Tripart,SymFlag,DiagFlag,*this);
      }

      template <template <typename> class iVecType>
      void refer(const TriangMatrix<T,iVecType>& TM) {
        runReferOp(TM,*this);
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

      virtual const char* type() const { return runTriMatTypeOp(); }

  };

  template <typename T, template <typename> class VecType>
  const bool TriangMatrix<T,VecType>::IsTriangleMatrix=true;
}

#endif

