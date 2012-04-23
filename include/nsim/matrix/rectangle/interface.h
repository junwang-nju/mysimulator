
#ifndef _Matrix_Rectangle_Interface_H_
#define _Matrix_Rectangle_Interface_H_

#include "matrix/base/interface.h"
#include "matrix/rectangle/_get.h"

namespace mysimulator {

  template <typename T>
  struct MatrixRectangle : public MatrixBase<T> {

    public:

      typedef MatrixRectangle<T>  Type;
      typedef MatrixBase<T>   ParentType;
      typedef T& (*GetFuncType)(Array2D<T>&,unsigned int,unsigned int);

      GetFuncType GetFunc;

      MatrixRectangle() : ParentType(), GetFunc(NULL) {}
      ~MatrixRectangle() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&(GetFunc!=NULL);
      }

      void Allocate(unsigned int nr,unsigned int nc,
                    MatrixStorageName MSN=MatrixStorageRegulariC) {
        static_cast<ParentType*>(this)->Allocate(nr,nc);
        this->NumRows=nr;
        this->NumColumns=nc;
        this->StorageName=MSN;
        switch(MSN) {
          case MatrixStorageRegulariC:  GetFunc=_GetRegularC; break;
          case MatrixStorageRegulariFortran: GetFunc=_GetRegularFortran; break;
          default:
            fprintf(stderr,"Improper Storage Method!\n");
        }
      }
      void Allocate(const Array1D<unsigned int>&) {
        fprintf(stderr,"Prohibited for Rectangle Matrix!\n");
      }

      T& operator()(unsigned int m,unsigned int n) {
        return GetFunc(*this,m,n);
      }
      const T& operator()(unsigned int m,unsigned int n) const {
        return GetFunc(const_cast<Type&>(*this),m,n);
      }

  };

  template <typename T>
  void Clear(MatrixRectangle<T>& M) {
    Clear(static_cast<typename MatrixRectangle<T>::ParentType&>(M));
    M.GetFunc=NULL;
  }

}

#endif

