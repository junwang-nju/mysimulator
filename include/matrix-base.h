
#ifndef _Matrix_Base_H_
#define _Matrix_Base_H_

#include "data-pack.h"
#include "matrix-common-info-id.h"

namespace std {
  /*
  enum SquareInfoItems {
    SquareDimension=NumberCommonItems,
    SquareNumberItems
  };
  */
  template <typename T, unsigned int MType, template<typename> class VecType,
            unsigned int NInf>
  class MatrixBase : public DataPack<T,VecType,VecType,NInf> {

    public:

      typedef MatrixBase<T,MType,VecType,NInf>   Type;

      typedef DataPack<T,VecType,VecType,NInf> ParentType;

      typedef T& (*GetElemFuncType)(VecType<refVector<T> >&,
                                    unsigned int,unsigned int,T&);

    protected:

      static const unsigned int MatType;

      T OtherElems;

      GetElemFuncType getElem;

    public:

      MatrixBase() : ParentType(), OtherElems(), getElem(NULL) {}

      MatrixBase(const Type&) { myError("Cannot create from Matrix base"); }

      virtual ~MatrixBase() { clear(); }

      Type& operator=(const Type& MB) {
        unsigned int m=(NumRow()<MB.NumRow()?NumRow():MB.NumRow());
        unsigned int n=(NumCol()<MB.NumCol()?NumCol():MB.NumCol());
        for(unsigned int i=0;i<m;++i)
        for(unsigned int j=0;j<n;++j) operator()(i,j)=MB(i,j);
        return *this;
      }

      template <unsigned int iMType, template<typename> class iVecType,
                unsigned int iNInf>
      Type& operator=(const MatrixBase<T,iMType,iVecType,iNInf>& MB) {
        unsigned int m=(NumRow()<MB.NumRow()?NumRow():MB.NumRow());
        unsigned int n=(NumCol()<MB.NumCol()?NumCol():MB.NumCol());
        for(unsigned int i=0;i<m;++i)
        for(unsigned int j=0;j<n;++j) operator()(i,j)=MB(i,j);
        return *this;
      }

      Type& operator=(const VectorBase<T>& V) { this->data()=V; return *this; }

      Type& operator=(const T& D) { this->data()=D; return *this; }

      template <unsigned int iMType, template<typename> class iVecType,
                unsigned int iNInf>
      void assign(const MatrixBase<T,iMType,iVecType,iNInf>& MB,
                  const unsigned int nrow,    const unsigned int ncol,
                  const unsigned int mbroff,  const unsigned int mbcoff,
                  const unsigned int mbrstep, const unsigned int mbcstep,
                  const unsigned int roff,    const unsigned int coff,
                  const unsigned int rstep,   const unsigned int cstep) {
        assert(roff+nrow*rstep<=NumRow());
        assert(coff+ncol*cstep<=NumCol());
        assert(mbroff+nrow*mbrstep<=MB.NumRow());
        assert(mbcoff+ncol*mbcstep<=MB.NumCol());
        for(unsigned int i=0,r=roff,rm=mbroff;i<nrow;++i,r+=rstep,rm+=mbrstep)
        for(unsigned int j=0,c=coff,cm=mbcoff;j<ncol;++j,c+=cstep,cm+=mbcstep)
          operator()(r,c)=MB(rm,cm);
        return *this;
      }

      void clear() {
        getElem=NULL;
        static_cast<ParentType*>(this)->clear();
      }

      const unsigned int NumRow() const { return this->info()[NumberRows]; }

      const unsigned int NumCol() const {
        return this->info()[NumberColumns];
      }

      const int& MatrixOrder() const { return this->info()[ExpectOrder]; }

      const int& MatrixTransposeState() const {
        return this->info()[TransposeState];
      }

      const int& MatrixActualOrder() const {
        return this->info()[ActualOrder];
      }

      const T& OtherElements() const { return OtherElems; }

      const GetElemFuncType& GetElementMethod() const { return getElem; }

    protected:

      void SetSize(const unsigned int NR, const unsigned int NC) {
        this->info()[NumberRows]=NR;
        this->info()[NumberColumns]=NC;
      }

      void SetOrder(const int Ord) { this->info()[ExpectOrder]=Ord; }

      void SetTransposeState(const int Trans) {
        this->info()[TransposeState]=Trans;
      }

      void SetActualOrder(const int AOrd) { this->info()[ActualOrder]=AOrd; }

      void AssignGetMethod(const GetElemFuncType& iGMethod) {
        getElem=iGMethod;
      }

      void SetOtherElements(const T& OE) { OtherElems=OE; }

    public:

      T& operator()(const unsigned int I, const unsigned int J) {
        return getElem(this->structure(),I,J,OtherElems);
      }

      const T& operator()(const unsigned int I, const unsigned int J) const {
        return getElem(const_cast<VecType<refVector<T> >&>(this->structure()),
                       I,J,const_cast<T&>(OtherElems));
      }

  };

  template <typename T, unsigned int MType, template<typename> class VecType,
            unsigned int NInf>
  const unsigned int MatrixBase<T,MType,VecType,NInf>::MatType=MType;

  template <typename T, unsigned int MType, template<typename> class VecType,
            unsigned int NInf>
  ostream& operator<<(ostream& os, const MatrixBase<T,MType,VecType,NInf>& M) {
    unsigned int m=M.NumRow(), n=M.NumCol();
    os<<M(0,0);
    for(unsigned int j=1;j<n;++j) os<<"\t"<<M(0,j);
    for(unsigned int i=1;i<m;++i) {
      os<<endl;
      os<<M(i,0);
      for(unsigned int j=1;j<n;++j) os<<"\t"<<M(i,j);
    }
    return os;
  }

}

#endif

