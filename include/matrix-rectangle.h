
#ifndef _Matrix_Rectangle_H_
#define _Matrix_Rectangle_H_

#include "matrix-base.h"
#include "matrix-format-id.h"
#include "matrix-data-order-id.h"
#include "matrix-transpose-id.h"
#include "var-vector.h"
#include "ref-vector.h"

namespace std {

  template <typename T, template<typename> class VecType>
  static T& getCData(VecType<refVector<T> >& Ls, unsigned int I,
                     unsigned int J, T& Other) {
    return Ls[I][J];
  }

  template <typename T, template<typename> class VecType>
  static T& getFortranData(VecType<refVector<T> >& Ls, unsigned int I,
                           unsigned int J, T& Other) {
    return Ls[J][I];
  }

  enum RectangleInfoItems {
    RectangleNumberItems=NumberCommonItems
  };

  template <template <typename> class iVecType>
  struct TypeOp {
    const char* operator()() const { return "Rectangle Matrix"; }
  };

  template <>
  struct TypeOp<varVector> {
    const char* operator()() const { return "Variable Rectangle Matrix"; }
  };

  template <>
  struct TypeOp<refVector> {
    const char* operator()() const { return "Reference Rectangle Matrix"; }
  };

  template <typename T, template<typename> class VecType>
  class RectMatrix
    : public MatrixBase<T,Rectangle,VecType,RectangleNumberItems> {

    public:

      typedef RectMatrix<T,VecType>   Type;

      typedef MatrixBase<T,Rectangle,VecType,RectangleNumberItems>  ParentType;

      RectMatrix() : ParentType() {}

      RectMatrix(const unsigned int M, const unsigned int N,
                 const int Order=COrder, const int Trans=NoTranspose)
        : ParentType() {
        allocate(M,N,Order,Trans);
      }

      RectMatrix(const Type&) {
        myError("Cannot create from rectangle matrix");
      }

      virtual ~RectMatrix() {}

      Type& operator=(const Type& RMB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(RMB));
        return *this;
      }

      template <unsigned int iMType, template<typename> class iVecType,
                unsigned int iNInf>
      Type& operator=(const MatrixBase<T,iMType,iVecType,iNInf>& V) {
        static_cast<ParentType*>(this)->operator=(V);
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

    protected:

      void SetGetMethod() {
        assert(this->MatrixOrder()>=0);
        assert(this->MatrixTransposeState()>=0);
        if(this->MatrixTransposeState()==NoTranspose)
          this->SetActualOrder(this->MatrixOrder());
        else if(this->MatrixTransposeState()==WithTranspose) {
          if(this->MatrixOrder()==COrder) this->SetActualOrder(FortranOrder);
          else if(this->MatrixOrder()==FortranOrder)
            this->SetActualOrder(COrder);
          else myError("matrix order is not proper");
        } else myError("unknown mode of transpose state for matrix");
        if(this->MatrixActualOrder()==COrder)
          this->AssignGetMethod(getCData<T,VecType>);
        else if(this->MatrixActualOrder()==FortranOrder)
          this->AssignGetMethod(getFortranData<T,VecType>);
        else myError("improper actual order for matrix rectangle more");
      }

      struct AllocateOp {
        template <template <typename> class iVecType>
        void operator()(const unsigned int M, const unsigned int N,
                        const int Order, const int Trans,
                        RectMatrix<T,iVecType>& RM) {
          myError("Not Available");
        }
        void operator()(const unsigned int M, const unsigned int N,
                        const int Order, const int Trans,
                        RectMatrix<T,varVector>& RM) {
          RM.clear();
          RM.SetSize(M,N);
          RM.SetOrder(Order);
          RM.SetTransposeState(Trans);
          RM.SetGetMethod();
          RM.data().allocate(M*N);
          if(RM.MatrixActualOrder()==COrder) {
            RM.structure().allocate(M);
            for(unsigned int i=0,n=0;i<M;++i,n+=N)
              RM.structure()[i].refer(RM.data(),n,N);
          } else if(RM.MatrixActualOrder()==FortranOrder) {
            RM.structure().allocate(N);
            for(unsigned int i=0,n=0;i<N;++i,n+=M)
              RM.structure()[i].refer(RM.data(),n,M);
          } else myError("Improper order for rectangle matrix");
        }
      };

      struct ReferOp {
        template <template <typename> class iVecType,
                  template <typename> class rVecType>
        void operator()(const RectMatrix<T,iVecType>& RM,
                        RectMatrix<T,rVecType>& Self) {
          myError("Not Available");
        }
        template <template <typename> class iVecType>
        void operator()(const RectMatrix<T,iVecType>& RM,
                        RectMatrix<T,refVector>& Self) {
          Self.data().refer(RM.data());
          Self.structure().refer(RM.structure());
          Self.info()=RM.info();
          Self.SetGetMethod();
        }
        template <template <typename> class iVecType,
                  template <typename> class rVecType>
        void operator()(const RectMatrix<T,iVecType>& RM,
                        const unsigned int off, const unsigned int size,
                        RectMatrix<T,rVecType>& Self) {
          myError("Not Available");
        }
        template <template <typename> class iVecType>
        void operator()(const RectMatrix<T,iVecType>& RM,
                        const unsigned int off, const unsigned int size,
                        RectMatrix<T,refVector>& Self) {
          unsigned int nl=RM.structure()[0].size();
          Self.data().refer(RM.data(),off*nl,size*nl);
          Self.structure().refer(RM.structure(),off,size);
          Self.info()=RM.info();
          if(Self.MatrixActualOrder()==COrder)
            Self.info()[NumberRows]=size;
          else if(Self.MatrixActualOrder()==FortranOrder)
            Self.info()[NumberColumns]=size;
          else myError("matrix order is not proper");
          Self.SetGetMethod();
        }
      };

      AllocateOp runAllocateOp;

      TypeOp<VecType> runTypeOp;

      ReferOp runReferOp;

    public:

      void allocate(const unsigned int M, const unsigned int N,
                    const int Order=COrder, const int Trans=NoTranspose) {
        runAllocateOp(M,N,Order,Trans,*this);
      }

      template <template <typename> class iVecType>
      void refer(const RectMatrix<T,iVecType>& RM) {
        runReferOp(RM,*this);
      }

      template <template <typename> class iVecType>
      void refer(const RectMatrix<T,iVecType>& RM, const unsigned int off,
                 const unsigned int size) {
        runReferOp(RM,off,size,*this);
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

      virtual const char* type() const { return runTypeOp(); }

  };

}

#endif

