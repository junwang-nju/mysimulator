
#ifndef _Matrix_Triangle_Base_H_
#define _Matrix_Triangle_Base_H_

#include "matrix-base.h"

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
    DiagonalExisted,
    SymmetryFlag,
    TrianglePart,
    ActualTrianglePart,
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

  template <typename T, template <typename> class VecType>
  class TriangMatrixBase
    : public MatrixBase<T,Triangle,VecType,TriangleNumberItems> {

    public:

      typedef TriangMatrixBase<T,VecType>   Type;

      typedef MatrixBase<T,Triangle,VecType,TriangleNumberItems>  ParentType;

      TriangMatrixBase() : ParentType() {}

      TriangMatrixBase(const Type& TMB) {
        myError("Cannot create from triangle matrix base");
      }

      virtual ~TriangMatrixBase() {}

      Type& operator=(const Type& TMB) {
        assert(this->IsSymmetry()==TMB.IsSymmetry());
        assert(this->IsDiagonalExisted()==TMB.IsDiagonalExisted());
        if(this->IsSymmetry()) {
          bool fg1,fg2,fg3;
          fg1=(this->MatrixActualOrder()==TMB.MatrixActualOrder())&&
              (this->MatrixActualOrder()==DiagonalOrder);
          fg2=(this->MatrixActualOrder()!=DiagonalOrder)&&
              (TMB.MatrixActualOrder()!=DiagonalOrder)&&
              (this->MatrixActualOrder()!=TMB.MatrixActualOrder())&&
              (this->MatrixActualTrianglePart()!=
               TMB.MatrixActualTrianglePart());
          fg3=(this->MatrixActualOrder()==TMB.MatrixActualOrder())&&
              (this->MatrixActualOrder()!=DiagonalOrder)&&
              (this->MatrixActualTrianglePart()==
               TMB.MatrixActualTrianglePart());
          assert(fg1||fg2||fg3);
        } else {
          assert(this->MatrixActualOrder()==TMB.MatrixActualOrder());
          assert(this->MatrixActualTrianglePart()==
                 TMB.MatrixActualTrianglePart());
        }
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(TMB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const TriangMatrixBase<T,iVecType>& TMB) {
        assert(this->IsSymmetry()==TMB.IsSymmetry());
        assert(this->IsDiagonalExisted()==TMB.IsDiagonalExisted());
        if(this->IsSymmetry()) {
          bool fg1,fg2,fg3;
          fg1=(this->MatrixActualOrder()==TMB.MatrixActualOrder())&&
              (this->MatrixActualOrder()==DiagonalOrder);
          fg2=(this->MatrixActualOrder()!=DiagonalOrder)&&
              (TMB.MatrixActualOrder()!=DiagonalOrder)&&
              (this->MatrixActualOrder()!=TMB.MatrixActualOrder())&&
              (this->MatrixActualTrianglePart()!=
               TMB.MatrixActualTrianglePart());
          fg3=(this->MatrixActualOrder()==TMB.MatrixActualOrder())&&
              (this->MatrixActualOrder()!=DiagonalOrder)&&
              (this->MatrixActualTrianglePart()==
               TMB.MatrixActualTrianglePart());
          assert(fg1||fg2||fg3);
        } else {
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
        return this->info()[DiagonalExisted]==WithDiagonal;
      }

      void SetDiagonalState(const bool dflag) {
        this->info()[DiagonalExisted]=(dflag?WithDiagonal:NullDiagonal);
      }

      const unsigned int MatrixTrianglePart() const {
        return this->info()[TrianglePart];
      }

      void SetTrianglePart(const unsigned int ulstate) {
        this->info()[TrianglePart]=ulstate;
      }

      const unsigned int MatrixActualTrianglePart() const {
        return this->info()[ActualTrianglePart];
      }

      void SetActualTrianglePart(const unsigned int ulstate) {
        this->info()[ActualTrianglePart]=ulstate;
      }

    protected:

      void SetGetMethod() {
        assert(this->MatrixOrder()>=0);
        assert(this->MatrixTransposeState()>=0);
        assert(this->info()[SymmetryFlag]>=0);
        assert(this->info()[DiagonalExisted]>=0);
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
          else myError("unknow triangle part flag");
        } else myError("unknown mode of transpose state for matrix");
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

  };

}

#endif

